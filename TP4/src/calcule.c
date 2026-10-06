#include "operator.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <operateur> <num1> <num2>\n", argv[0]);
        return 1;
    }

    char operateur = argv[1][0];
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);

    switch (operateur) {
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
            return 1;
    }

    return 0;
}
