#include "liste.h"

#include <stdio.h>
#include <stdlib.h>

void init_liste(struct liste_couleurs *liste) {
    liste->tete = NULL;
}

void insertion(struct couleur *couleur, struct liste_couleurs *liste) {
    struct noeud_couleur *nouveau = malloc(sizeof(struct noeud_couleur));
    if (nouveau == NULL) {
        printf("Erreur allocation memoire\n");
        return;
    }

    nouveau->valeur = *couleur;
    nouveau->suivant = liste->tete;
    liste->tete = nouveau;
}

void parcours(struct liste_couleurs *liste) {
    struct noeud_couleur *actuel = liste->tete;
    while (actuel != NULL) {
        printf("R=%u G=%u B=%u A=%u\n",
               actuel->valeur.r,
               actuel->valeur.g,
               actuel->valeur.b,
               actuel->valeur.a);
        actuel = actuel->suivant;
    }
}
