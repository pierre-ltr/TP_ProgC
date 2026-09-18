#include <stdio.h>

void afficherBinaire(int nombre) {
    int bits[32];
    int index = 0;

    if (nombre == 0) {
        printf("0\n");
        return;
    }

    while (nombre > 0) {
        bits[index++] = nombre % 2;
        nombre /= 2;
    }

    for (int i = index - 1; i >= 0; i--) {
        printf("%d", bits[i]);
    }
    printf("\n");
}

int main(void) {
    int valeurs[] = {0, 4096, 65536, 65535, 1024};

    for (int i = 0; i < 5; i++) {
        printf("%d -> ", valeurs[i]);
        afficherBinaire(valeurs[i]);
    }

    return 0;
}
