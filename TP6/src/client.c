/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "bmp.h"
#include "client.h"

static void ajouter_couleur(char *buffer, size_t buffer_size, const char *hex_color)
{
    size_t longueur = strlen(buffer);
    size_t restant = buffer_size - longueur;

    if (restant > 1)
    {
        if (longueur > 1 && buffer[longueur - 1] != '[')
        {
            strncat(buffer, ",", restant);
            longueur = strlen(buffer);
            restant = buffer_size - longueur;
        }

        strncat(buffer, "\"", restant);
        strncat(buffer, hex_color, buffer_size - strlen(buffer) - 1);
        strncat(buffer, "\"", buffer_size - strlen(buffer) - 1);
    }
}

static void construire_json_couleurs(const char *pathname, int nombre_couleurs, char *buffer, size_t buffer_size)
{
    couleur_compteur *cc = analyse_bmp_image((char *)pathname);
    int limite = 0;
    int i = 0;

    if (buffer == NULL || buffer_size == 0)
    {
        return;
    }

    buffer[0] = '\0';

    if (cc == NULL || cc->size <= 0)
    {
        snprintf(buffer, buffer_size, "{\"code\":\"couleurs\",\"nombre\":0,\"valeurs\":[]}");
        return;
    }

    if (nombre_couleurs <= 0 || nombre_couleurs > cc->size)
    {
        limite = cc->size;
    }
    else
    {
        limite = nombre_couleurs;
    }

    snprintf(buffer, buffer_size, "{\"code\":\"couleurs\",\"nombre\":%d,\"valeurs\":[", limite);

    for (i = 0; i < limite; i++)
    {
        char couleur_hex[8];
        if (cc->compte_bit == BITS24)
        {
            snprintf(couleur_hex, sizeof(couleur_hex), "#%02x%02x%02x",
                     cc->cc.cc24[cc->size - 1 - i].c.rouge,
                     cc->cc.cc24[cc->size - 1 - i].c.vert,
                     cc->cc.cc24[cc->size - 1 - i].c.bleu);
        }
        else
        {
            snprintf(couleur_hex, sizeof(couleur_hex), "#%02x%02x%02x",
                     cc->cc.cc32[cc->size - 1 - i].c.rouge,
                     cc->cc.cc32[cc->size - 1 - i].c.vert,
                     cc->cc.cc32[cc->size - 1 - i].c.bleu);
        }
        ajouter_couleur(buffer, buffer_size, couleur_hex);
    }

    strncat(buffer, "]}", buffer_size - strlen(buffer) - 1);
}

int envoie_recois_message(int socketfd)
{
    char data[1024];
    char message[1024];

    memset(data, 0, sizeof(data));
    memset(message, 0, sizeof(message));

    printf("Votre message (max 1000 caracteres): ");
    if (fgets(message, sizeof(message), stdin) == NULL)
    {
        return -1;
    }

    message[strcspn(message, "\n")] = '\0';
    strncpy(data, "message: ", sizeof(data) - 1);
    data[sizeof(data) - 1] = '\0';
    strncat(data, message, sizeof(data) - strlen(data) - 1);

    if (write(socketfd, data, strlen(data)) < 0)
    {
        perror("erreur ecriture");
        return -1;
    }

    memset(data, 0, sizeof(data));
    if (read(socketfd, data, sizeof(data)) < 0)
    {
        perror("erreur lecture");
        return -1;
    }

    printf("Message recu: %s\n", data);
    return 0;
}

int envoie_couleurs(int socketfd, const char *pathname, int nombre_couleurs)
{
    char data[4096];
    memset(data, 0, sizeof(data));

    construire_json_couleurs(pathname, nombre_couleurs, data, sizeof(data));

    if (write(socketfd, data, strlen(data)) < 0)
    {
        perror("erreur ecriture");
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int socketfd;
    struct sockaddr_in server_addr;
    int nombre_couleurs = 10;

    if (argc < 2)
    {
        printf("usage: ./client chemin_bmp_image [nombre_couleurs]\n");
        return EXIT_FAILURE;
    }

    if (argc >= 3)
    {
        nombre_couleurs = atoi(argv[2]);
        if (nombre_couleurs <= 0)
        {
            nombre_couleurs = 10;
        }
    }

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connection serveur");
        exit(EXIT_FAILURE);
    }

    envoie_couleurs(socketfd, argv[1], nombre_couleurs);
    close(socketfd);
    return 0;
}
