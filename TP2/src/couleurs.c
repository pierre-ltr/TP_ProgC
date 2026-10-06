#include <stdio.h>

struct Couleur {
    unsigned char rouge;
    unsigned char vert;
    unsigned char bleu;
    unsigned char alpha;
};

int main(void) {
    struct Couleur couleurs[10] = {
        {0xef, 0x78, 0x12, 0xff},
        {0x2c, 0xc8, 0x64, 0xff},
        {0x00, 0x00, 0x00, 0xff},
        {0xff, 0xff, 0xff, 0xff},
        {0x11, 0x22, 0x33, 0xff},
        {0x44, 0x55, 0x66, 0xff},
        {0x77, 0x88, 0x99, 0xff},
        {0xaa, 0xbb, 0xcc, 0xff},
        {0xdd, 0xee, 0xff, 0xff},
        {0x12, 0x34, 0x56, 0x80}
    };

    for (int i = 0; i < 10; i++) {
        printf("Couleur %d :\n", i + 1);
        printf("Rouge : %u\n", couleurs[i].rouge);
        printf("Vert : %u\n", couleurs[i].vert);
        printf("Bleu : %u\n", couleurs[i].bleu);
        printf("Alpha : %u\n\n", couleurs[i].alpha);
    }

    return 0;
}
