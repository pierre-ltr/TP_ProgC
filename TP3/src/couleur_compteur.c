#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct CouleurCompte {
    struct Couleur couleur;
    int compteur;
};

int couleurExiste(const struct Couleur *c, const struct CouleurCompte *tab, int taille) {
    for (int i = 0; i < taille; i++) {
        if (tab[i].couleur.r == c->r && tab[i].couleur.g == c->g &&
            tab[i].couleur.b == c->b && tab[i].couleur.a == c->a) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    srand((unsigned int)time(NULL));

    struct Couleur palette[100];
    struct CouleurCompte distincts[100];
    int distinctCount = 0;

    for (int i = 0; i < 100; i++) {
        palette[i].r = (unsigned char)(rand() % 256);
        palette[i].g = (unsigned char)(rand() % 256);
        palette[i].b = (unsigned char)(rand() % 256);
        palette[i].a = (unsigned char)(rand() % 256);
    }

    for (int i = 0; i < 100; i++) {
        int index = couleurExiste(&palette[i], distincts, distinctCount);

        if (index == -1) {
            distincts[distinctCount].couleur = palette[i];
            distincts[distinctCount].compteur = 1;
            distinctCount++;
        } else {
            distincts[index].compteur++;
        }
    }

    for (int i = 0; i < distinctCount; i++) {
        printf("%02x %02x %02x %02x : %d\n",
               distincts[i].couleur.r,
               distincts[i].couleur.g,
               distincts[i].couleur.b,
               distincts[i].couleur.a,
               distincts[i].compteur);
    }

    return 0;
}
