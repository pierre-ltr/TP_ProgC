#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rechercheDichotomique(int tableau[], int taille, int valeur) {
    int gauche = 0;
    int droite = taille - 1;

    while (gauche <= droite) {
        int milieu = gauche + (droite - gauche) / 2;

        if (tableau[milieu] == valeur) {
            return 1;
        }

        if (tableau[milieu] < valeur) {
            gauche = milieu + 1;
        } else {
            droite = milieu - 1;
        }
    }

    return 0;
}

int main(void) {
    srand((unsigned int)time(NULL));

    int tableau[100];
    tableau[0] = rand() % 10;
    for (int i = 1; i < 100; i++) {
        tableau[i] = tableau[i - 1] + 1 + rand() % 5;
    }

    printf("Tableau trie :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    int recherche;
    printf("Entrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &recherche);

    if (rechercheDichotomique(tableau, 100, recherche)) {
        printf("Resultat : entier present\n");
    } else {
        printf("Resultat : entier absent\n");
    }

    return 0;
}
