#include "fichier.h"
#include "liste.h"
#include "operator.h"

#include <stdio.h>

static void exercice_1(void) {
    int num1, num2;
    char op;

    printf("Entrez num1 : ");
    scanf("%d", &num1);
    printf("Entrez num2 : ");
    scanf("%d", &num2);
    printf("Entrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
    scanf(" %c", &op);

    switch (op) {
        case '+':
            printf("Resultat : %d\n", somme(num1, num2));
            break;
        case '-':
            printf("Resultat : %d\n", difference(num1, num2));
            break;
        case '*':
            printf("Resultat : %d\n", produit(num1, num2));
            break;
        case '/':
            printf("Resultat : %d\n", quotient(num1, num2));
            break;
        case '%':
            printf("Resultat : %d\n", modulo(num1, num2));
            break;
        case '&':
            printf("Resultat : %d\n", et_binaire(num1, num2));
            break;
        case '|':
            printf("Resultat : %d\n", ou_binaire(num1, num2));
            break;
        case '~':
            printf("Resultat : %d\n", negation(num1));
            break;
        default:
            printf("Operateur inconnu.\n");
            break;
    }
}

static void exercice_2(void) {
    int choix;
    char nom_fichier[128];
    char message[256];

    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n2. Ecrire dans un fichier\nVotre choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("Entrez le nom du fichier a lire : ");
        scanf("%127s", nom_fichier);
        lire_fichier(nom_fichier);
    } else if (choix == 2) {
        printf("Entrez le nom du fichier : ");
        scanf("%127s", nom_fichier);
        printf("Entrez le message : ");
        scanf(" %255[^\n]", message);
        ecrire_dans_fichier(nom_fichier, message);
        printf("Le message a ete ecrit dans le fichier %s.\n", nom_fichier);
    } else {
        printf("Choix invalide.\n");
    }
}

static void exercice_7(void) {
    struct liste_couleurs ma_liste;
    init_liste(&ma_liste);

    struct couleur couleurs[10] = {
        {0xFF, 0x00, 0x00, 0xFF},
        {0x00, 0xFF, 0x00, 0xFF},
        {0x00, 0x00, 0xFF, 0xFF},
        {0xFF, 0xFF, 0x00, 0xFF},
        {0xFF, 0x00, 0xFF, 0xFF},
        {0x00, 0xFF, 0xFF, 0xFF},
        {0x80, 0x80, 0x80, 0xFF},
        {0x12, 0x34, 0x56, 0xFF},
        {0xAA, 0xBB, 0xCC, 0xFF},
        {0x11, 0x22, 0x33, 0x80}
    };

    for (int i = 0; i < 10; i++) {
        insertion(&couleurs[i], &ma_liste);
    }

    printf("Liste des couleurs :\n");
    parcours(&ma_liste);
}

int main(void) {
    int choix;

    printf("Choisissez un exercice (1, 2, 7) : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            exercice_1();
            break;
        case 2:
            exercice_2();
            break;
        case 7:
            exercice_7();
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }

    return 0;
}

