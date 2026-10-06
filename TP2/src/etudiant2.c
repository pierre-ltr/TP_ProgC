#include <stdio.h>
#include <string.h>

struct Etudiant {
    char nom[30];
    char prenom[30];
    char adresse[50];
    float noteC;
    float noteSys;
};

int main(void) {
    struct Etudiant etudiants[5] = {
        {"Dupont", "Marie", "20, Boulevard Niels Bohr, Lyon", 16.5f, 12.1f},
        {"Martin", "Pierre", "22, Boulevard Niels Bohr, Lyon", 14.0f, 14.1f},
        {"Bernard", "Julie", "25, Rue de la Paix, Paris", 18.0f, 15.5f},
        {"Moreau", "Sophie", "12, Avenue des Fetes, Lille", 13.5f, 17.0f},
        {"Petit", "Luc", "8, Rue du Port, Nantes", 15.0f, 14.5f}
    };

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prenom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note 1 : %.1f\n", etudiants[i].noteC);
        printf("Note 2 : %.1f\n\n", etudiants[i].noteSys);
    }

    return 0;
}
