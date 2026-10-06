#include "repertoire.h"

#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

static int est_repertoire(const char *chemin)
{
    struct stat statut;

    if (stat(chemin, &statut) != 0)
    {
        return 0;
    }

    return S_ISDIR(statut.st_mode);
}

void lire_dossier(const char *nom_repertoire)
{
    DIR *repertoire = opendir(nom_repertoire);
    struct dirent *entree;

    if (repertoire == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entree = readdir(repertoire)) != NULL)
    {
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
        {
            continue;
        }

        printf("%s\n", entree->d_name);
    }

    closedir(repertoire);
}

void lire_dossier_recursif(const char *nom_repertoire)
{
    DIR *repertoire = opendir(nom_repertoire);
    struct dirent *entree;
    char chemin[PATH_MAX];

    if (repertoire == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entree = readdir(repertoire)) != NULL)
    {
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(chemin, sizeof(chemin), "%s/%s", nom_repertoire, entree->d_name);
        printf("%s\n", chemin);

        if (est_repertoire(chemin))
        {
            lire_dossier_recursif(chemin);
        }
    }

    closedir(repertoire);
}

void lire_dossier_iteratif(const char *nom_repertoire)
{
    char dossiers[1024][PATH_MAX];
    int nombre_dossiers = 0;

    snprintf(dossiers[nombre_dossiers++], PATH_MAX, "%s", nom_repertoire);

    while (nombre_dossiers > 0)
    {
        char chemin_courant[PATH_MAX];
        DIR *repertoire;
        struct dirent *entree;

        snprintf(chemin_courant, sizeof(chemin_courant), "%s", dossiers[--nombre_dossiers]);
        repertoire = opendir(chemin_courant);

        if (repertoire == NULL)
        {
            perror("opendir");
            continue;
        }

        while ((entree = readdir(repertoire)) != NULL)
        {
            char sous_chemin[PATH_MAX];

            if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0)
            {
                continue;
            }

            snprintf(sous_chemin, sizeof(sous_chemin), "%s/%s", chemin_courant, entree->d_name);
            printf("%s\n", sous_chemin);

            if (est_repertoire(sous_chemin))
            {
                snprintf(dossiers[nombre_dossiers++], PATH_MAX, "%s", sous_chemin);
            }
        }

        closedir(repertoire);
    }
}
