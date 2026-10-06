#include <stdio.h>

int longueur(char *chaine) {
    int i = 0;
    while (chaine[i] != '\0') {
        i++;
    }
    return i;
}

void copier(char *destination, char *source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

void concatener(char *destination, char *source) {
    int i = 0;
    while (destination[i] != '\0') {
        i++;
    }

    int j = 0;
    while (source[j] != '\0') {
        destination[i] = source[j];
        i++;
        j++;
    }
    destination[i] = '\0';
}

int main(void) {
    char texte1[] = "Hello";
    char texte2[] = " World!";
    char copie[50];
    char resultat[50];

    printf("Longueur de '%s' : %d\n", texte1, longueur(texte1));

    copier(copie, texte1);
    printf("Copie : %s\n", copie);

    copier(resultat, texte1);
    concatener(resultat, texte2);
    printf("Concatene : %s\n", resultat);

    return 0;
}
