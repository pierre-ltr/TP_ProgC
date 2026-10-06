#include <stdio.h>

void afficherOctets(const char *nom, void *ptr, size_t taille) {
    unsigned char *octets = (unsigned char *)ptr;

    printf("Octets de %s :\n", nom);
    for (size_t i = 0; i < taille; i++) {
        printf("%02x ", octets[i]);
    }
    printf("\n\n");
}

int main(void) {
    short s = 0x1234;
    int i = 0x01020304;
    long int li = 0x0102030405060708L;
    float f = 3.14159f;
    double d = 3.14159;
    long double ld = 3.14159L;

    afficherOctets("short", &s, sizeof(short));
    afficherOctets("int", &i, sizeof(int));
    afficherOctets("long int", &li, sizeof(long int));
    afficherOctets("float", &f, sizeof(float));
    afficherOctets("double", &d, sizeof(double));
    afficherOctets("long double", &ld, sizeof(long double));

    return 0;
}
