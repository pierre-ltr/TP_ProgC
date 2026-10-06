#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    int tableau[100];
    int plusGrand = 0;
    int plusPetit = 1000;

    for (int i = 0; i < 100; i++) {
        tableau[i] = rand() % 1000 + 1;

        if (tableau[i] > plusGrand) {
            plusGrand = tableau[i];
        }

        if (tableau[i] < plusPetit) {
            plusPetit = tableau[i];
        }
    }

    printf("Le numero le plus grand est : %d\n", plusGrand);
    printf("Le numero le plus petit est : %d\n", plusPetit);

    return 0;
}
