#include "fichier.h"

#include <stdio.h>
#include <string.h>

struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note1;
    float note2;
};

int main(void) {
    struct Etudiant etudiants[5];

    for (int i = 0; i < 5; i++) {
        printf("Entrez les details de l'etudiant %d :\n", i + 1);
        printf("Nom : ");
        scanf("%49s", etudiants[i].nom);
        printf("Prenom : ");
        scanf("%49s", etudiants[i].prenom);
        printf("Adresse : ");
        scanf(" %99[^\n]", etudiants[i].adresse);
        printf("Note 1 : ");
        scanf("%f", &etudiants[i].note1);
        printf("Note 2 : ");
        scanf("%f", &etudiants[i].note2);

        char ligne[256];
        snprintf(ligne, sizeof(ligne), "%s %s %s %.1f %.1f",
                 etudiants[i].nom,
                 etudiants[i].prenom,
                 etudiants[i].adresse,
                 etudiants[i].note1,
                 etudiants[i].note2);

        ecrire_dans_fichier("etudiant.txt", ligne);
    }

    printf("Les details des etudiants ont ete enregistres dans le fichier etudiant.txt.\n");
    return 0;
}
