/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <math.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "serveur.h"

const char *svg_file_path = "pie_chart.svg";
int socketfd;

static void ouvrir_svg_si_possible(void)
{
    char commande[256];
    FILE *test = popen("command -v firefox >/dev/null 2>&1", "r");
    int status = 0;

    if (test == NULL)
    {
        printf("SVG généré dans %s. Firefox indisponible sur cette machine.\n", svg_file_path);
        return;
    }

    status = pclose(test);
    if (status == 0)
    {
        snprintf(commande, sizeof(commande), "firefox %s >/dev/null 2>&1 &", svg_file_path);
        system(commande);
        printf("SVG ouvert dans le navigateur Firefox.\n");
    }
    else
    {
        printf("SVG généré dans %s. Firefox non installé.\n", svg_file_path);
    }
}

static double radians(double degres)
{
    return degres * M_PI / 180.0;
}

static int generer_svg(const char *couleurs[], int nombre_couleurs)
{
    FILE *svg_file = fopen(svg_file_path, "w");
    double centre_x = 200.0;
    double centre_y = 200.0;
    double rayon = 150.0;
    double angle_debut = -90.0;
    int i = 0;

    if (svg_file == NULL)
    {
        perror("Erreur ouverture SVG");
        return 1;
    }

    fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

    for (i = 0; i < nombre_couleurs; i++)
    {
        double angle_fin = angle_debut + 360.0 / nombre_couleurs;
        double x1 = centre_x + rayon * cos(radians(angle_debut));
        double y1 = centre_y + rayon * sin(radians(angle_debut));
        double x2 = centre_x + rayon * cos(radians(angle_fin));
        double y2 = centre_y + rayon * sin(radians(angle_fin));

        fprintf(svg_file,
                "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
                centre_x, centre_y, rayon, rayon, x2, y2, centre_x, centre_y, couleurs[i]);
        fprintf(svg_file,
                "  <path d=\"M%.2f,%.2f L%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
                centre_x, centre_y, x1, y1, rayon, rayon, x2, y2, centre_x, centre_y, couleurs[i]);

        angle_debut = angle_fin;
    }

    fprintf(svg_file, "</svg>\n");
    fclose(svg_file);

    ouvrir_svg_si_possible();
    return 0;
}

static int extraire_couleurs_plain(const char *data, char couleurs[][8], int *nombre_couleurs)
{
    const char *debut = strchr(data, ':');
    const char *ptr;
    int count = 0;

    if (debut == NULL)
    {
        return -1;
    }

    ptr = debut + 1;
    while (*ptr != '\0' && count < 30)
    {
        char couleur[8];
        int pos = 0;

        while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r' || *ptr == ',' || *ptr == '\t')
        {
            ptr++;
        }

        if (*ptr == '\0')
        {
            break;
        }

        while (*ptr != '\0' && *ptr != ',' && *ptr != ' ' && *ptr != '\n' && *ptr != '\r' && *ptr != '\t')
        {
            if (pos < 7)
            {
                couleur[pos++] = *ptr;
            }
            ptr++;
        }
        couleur[pos] = '\0';

        if (pos > 0)
        {
            snprintf(couleurs[count], sizeof(couleurs[count]), "%s", couleur);
            count++;
        }
    }

    *nombre_couleurs = count;
    return 0;
}

static int extraire_couleurs_json(const char *data, char couleurs[][8], int *nombre_couleurs)
{
    const char *values = strstr(data, "\"valeurs\"");
    const char *ptr;
    int count = 0;

    if (values == NULL)
    {
        return -1;
    }

    ptr = strchr(values, '[');
    if (ptr == NULL)
    {
        return -1;
    }

    ptr++;
    while (*ptr != '\0' && *ptr != ']' && count < 30)
    {
        const char *start = strchr(ptr, '"');
        const char *end;
        char value[8];
        int pos = 0;

        if (start == NULL)
        {
            break;
        }

        start++;
        end = strchr(start, '"');
        if (end == NULL)
        {
            break;
        }

        while (start + pos < end && pos < 7)
        {
            value[pos] = start[pos];
            pos++;
        }
        value[pos] = '\0';
        snprintf(couleurs[count], sizeof(couleurs[count]), "%s", value);
        count++;
        ptr = end + 1;
    }

    *nombre_couleurs = count;
    return 0;
}

static int traitement_couleurs(const char *data)
{
    char couleurs[30][8];
    int nombre_couleurs = 0;
    const char *couleurs_tableau[30];
    int i = 0;

    if (strncmp(data, "{\"code\":\"couleurs\"", 18) == 0)
    {
        if (extraire_couleurs_json(data, couleurs, &nombre_couleurs) != 0)
        {
            return -1;
        }
    }
    else if (strstr(data, "couleurs") != NULL)
    {
        if (extraire_couleurs_plain(data, couleurs, &nombre_couleurs) != 0)
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

    for (i = 0; i < nombre_couleurs; i++)
    {
        couleurs_tableau[i] = couleurs[i];
    }

    return generer_svg(couleurs_tableau, nombre_couleurs);
}

int renvoie_message(int client_socket_fd, const char *data)
{
    int data_size = write(client_socket_fd, data, strlen(data));

    if (data_size < 0)
    {
        perror("erreur ecriture");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int recois_envoie_message(int client_socket_fd, const char *data)
{
    char message[1024];

    printf("Message recu: %s\n", data);
    if (strncmp(data, "message:", 8) == 0)
    {
        snprintf(message, sizeof(message), "%s", data);
        return renvoie_message(client_socket_fd, message);
    }

    return traitement_couleurs(data);
}

void gestionnaire_ctrl_c(int signal)
{
    (void)signal;
    printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");
    if (socketfd != -1)
    {
        close(socketfd);
    }
    exit(0);
}

int main(void)
{
    int bind_status;
    struct sockaddr_in server_addr;
    int option = 1;
    struct sockaddr_in client_addr;
    char data[4096];
    unsigned int client_addr_len = sizeof(client_addr);
    int client_socket_fd;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Unable to open a socket");
        return -1;
    }

    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_status < 0)
    {
        perror("bind");
        return EXIT_FAILURE;
    }

    signal(SIGINT, gestionnaire_ctrl_c);
    listen(socketfd, 10);
    printf("Serveur en attente de connexions...\n");

    while (1)
    {
        client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket_fd < 0)
        {
            perror("accept");
            continue;
        }

        memset(data, 0, sizeof(data));
        if (read(client_socket_fd, (void *)data, sizeof(data)) < 0)
        {
            perror("erreur lecture");
            close(client_socket_fd);
            continue;
        }

        recois_envoie_message(client_socket_fd, data);
        close(client_socket_fd);
    }

    return 0;
}
