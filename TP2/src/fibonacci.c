#include <stdio.h>

int main(void) {
    int n = 10;
    int a = 0;
    int b = 1;

    printf("Suite de Fibonacci jusqu'a U%d : ", n);
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf("0");
        } else if (i == 1) {
            printf(", 1");
        } else {
            int c = a + b;
            printf(", %d", c);
            a = b;
            b = c;
        }
    }
    printf("\n");
    return 0;
}
