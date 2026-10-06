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

#include "client.h"

int envoie_recois_message(int socketfd)
{
    char data[1024];
    char message[1024];

    memset(data, 0, sizeof(data));
    memset(message, 0, sizeof(message));

    printf("Votre message (max 1000 caractères): ");
    if (fgets(message, sizeof(message), stdin) == NULL)
    {
        return -1;
    }

    message[strcspn(message, "\n")] = '\0';

    if (strlen(message) >= sizeof(data) - 9)
    {
        message[sizeof(data) - 10] = '\0';
    }

    snprintf(data, sizeof(data), "message: %s", message);

    int write_status = write(socketfd, data, strlen(data));
    if (write_status < 0)
    {
        perror("Erreur d'écriture");
        return -1;
    }

    memset(data, 0, sizeof(data));

    int read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
        perror("Erreur de lecture");
        return -1;
    }

    printf("Message reçu: %s\n", data);
    return 0;
}

int envoie_operateur_numeros(int socketfd, char operateur, int nombre1, int nombre2)
{
    char data[1024];
    char message[1024];

    memset(data, 0, sizeof(data));
    memset(message, 0, sizeof(message));

    snprintf(message, sizeof(message), "calcule : %c %d %d", operateur, nombre1, nombre2);

    int write_status = write(socketfd, message, strlen(message));
    if (write_status < 0)
    {
        perror("Erreur d'écriture");
        return -1;
    }

    memset(data, 0, sizeof(data));

    int read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
        perror("Erreur de lecture");
        return -1;
    }

    printf("Résultat reçu: %s\n", data);
    return 0;
}

int main(void)
{
    int socketfd;
    struct sockaddr_in server_addr;

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

    while (1)
    {
        int choix;
        char operateur;
        int nombre1, nombre2;

        printf("\nChoix : 1) message  2) calcul  3) quitter\n");
        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1)
        {
            break;
        }
        getchar();

        if (choix == 1)
        {
            envoie_recois_message(socketfd);
        }
        else if (choix == 2)
        {
            printf("Opérateur (+, -, *, /) : ");
            scanf(" %c", &operateur);
            printf("Premier nombre : ");
            scanf("%d", &nombre1);
            printf("Deuxième nombre : ");
            scanf("%d", &nombre2);
            getchar();
            envoie_operateur_numeros(socketfd, operateur, nombre1, nombre2);
        }
        else
        {
            break;
        }
    }

    close(socketfd);
    return 0;
}
