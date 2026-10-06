#include "fichier.h"

#include <stdio.h>

void lire_fichier(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier");
        return;
    }

    char ligne[256];
    printf("Contenu du fichier %s :\n", nom_fichier);
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }
    printf("\n");

    fclose(fichier);
}

void ecrire_dans_fichier(const char *nom_fichier, const char *message) {
    FILE *fichier = fopen(nom_fichier, "a");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier");
        return;
    }

    fprintf(fichier, "%s\n", message);
    fclose(fichier);
}
