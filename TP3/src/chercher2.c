#include <stdio.h>

int longueurChaine(const char *chaine) {
    int longueur = 0;
    while (chaine[longueur] != '\0') {
        longueur++;
    }
    return longueur;
}

int comparerChaine(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

int rechercherPhrase(const char *phrase, char *phrases[], int taille) {
    for (int i = 0; i < taille; i++) {
        if (comparerChaine(phrase, phrases[i])) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    char *phrases[10] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };

    char phraseRecherchee[100];
    printf("Entrez une phrase : ");
    fgets(phraseRecherchee, sizeof(phraseRecherchee), stdin);

    int longueur = longueurChaine(phraseRecherchee);
    if (longueur > 0 && phraseRecherchee[longueur - 1] == '\n') {
        phraseRecherchee[longueur - 1] = '\0';
    }

    if (rechercherPhrase(phraseRecherchee, phrases, 10)) {
        printf("Phrase trouvee\n");
    } else {
        printf("Phrase non trouvee\n");
    }

    return 0;
}
