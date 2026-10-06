#ifndef LISTE_H
#define LISTE_H

struct couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct noeud_couleur {
    struct couleur valeur;
    struct noeud_couleur *suivant;
};

struct liste_couleurs {
    struct noeud_couleur *tete;
};

void init_liste(struct liste_couleurs *liste);
void insertion(struct couleur *couleur, struct liste_couleurs *liste);
void parcours(struct liste_couleurs *liste);

#endif
