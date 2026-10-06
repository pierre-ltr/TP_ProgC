#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    int entiers[10];
    float reels[10];

    for (int i = 0; i < 10; i++) {
        entiers[i] = rand() % 100;
        reels[i] = (float)(rand() % 1000) / 10.0f;
    }

    printf("Tableau d'entiers avant :");
    for (int i = 0; i < 10; i++) {
        printf(" %d", entiers[i]);
    }
    printf("\n");

    printf("Tableau de reels avant :");
    for (int i = 0; i < 10; i++) {
        printf(" %.2f", reels[i]);
    }
    printf("\n");

    int *pEntiers = entiers;
    float *pReels = reels;

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            *(pEntiers + i) *= 3;
            *(pReels + i) *= 3.0f;
        }
    }

    printf("Tableau d'entiers apres :");
    for (int i = 0; i < 10; i++) {
        printf(" %d", entiers[i]);
    }
    printf("\n");

    printf("Tableau de reels apres :");
    for (int i = 0; i < 10; i++) {
        printf(" %.2f", reels[i]);
    }
    printf("\n");

    return 0;
}
