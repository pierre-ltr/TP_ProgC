#include <stdio.h>

int main(void) {
    char noms[5][30] = {
        "Dupont", "Martin", "Bernard", "Moreau", "Petit"
    };
    char prenoms[5][30] = {
        "Marie", "Pierre", "Julie", "Sophie", "Luc"
    };
    char adresses[5][50] = {
        "10 rue de Paris", "22 avenue de Lyon", "5 boulevard de Marseille", "18 rue du Midi", "7 avenue des Champs"
    };
    float notesC[5] = {15.5f, 14.0f, 16.0f, 12.5f, 13.0f};
    float notesSys[5] = {13.0f, 15.5f, 12.0f, 14.5f, 16.5f};

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d\n", i + 1);
        printf("Nom : %s\n", noms[i]);
        printf("Prenom : %s\n", prenoms[i]);
        printf("Adresse : %s\n", adresses[i]);
        printf("Note C : %.1f\n", notesC[i]);
        printf("Note Systeme : %.1f\n\n", notesSys[i]);
    }

    return 0;
}
