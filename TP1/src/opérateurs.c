#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int a = 16;
    int b = 3;

    printf("a = %d\n", a);
    printf("b = %d\n", b);

    printf("Addition: %d\n", a + b);
    printf("Soustraction: %d\n", a - b);
    printf("Multiplication: %d\n", a * b);
    printf("Division: %d\n", a / b);
    printf("Modulo: %d\n", a % b);

    bool est_egal = (a == b);
    bool est_superieur = (a > b);

    printf("a == b : %d\n", est_egal);
    printf("a > b : %d\n", est_superieur);

    return 0;
}


