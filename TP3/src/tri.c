#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    int tableau[100];

    printf("Tableau non trie :\n");
    for (int i = 0; i < 100; i++) {
        tableau[i] = rand() % 201 - 100;
        printf("%d ", tableau[i]);
    }
    printf("\n\n");

    for (int i = 0; i < 100; i++) {
        for (int j = i + 1; j < 100; j++) {
            if (tableau[j] < tableau[i]) {
                int temp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = temp;
            }
        }
    }

    printf("Tableau trie par ordre croissant :\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    return 0;
}
