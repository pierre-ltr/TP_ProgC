#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    int tableau[100];
    for (int i = 0; i < 100; i++) {
        tableau[i] = rand() % 100;
    }

    printf("Tableau :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    int recherche;
    printf("Entrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &recherche);

    int trouve = 0;
    for (int i = 0; i < 100; i++) {
        if (tableau[i] == recherche) {
            trouve = 1;
            break;
        }
    }

    if (trouve) {
        printf("Resultat : entier present\n");
    } else {
        printf("Resultat : entier absent\n");
    }

    return 0;
}
