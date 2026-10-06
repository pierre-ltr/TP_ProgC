#include <stdio.h>
#include <string.h>

int compter_occurrences(const char *ligne, const char *phrase) {
    int count = 0;
    int phrase_len = (int)strlen(phrase);

    if (phrase_len == 0) {
        return 0;
    }

    for (int i = 0; ligne[i] != '\0'; i++) {
        if (strncmp(&ligne[i], phrase, phrase_len) == 0) {
            count++;
            i += phrase_len - 1;
        }
    }

    return count;
}

int main(void) {
    char nom_fichier[128];
    char phrase[256];
    char ligne[512];

    printf("Entrez le nom du fichier : ");
    scanf("%127s", nom_fichier);
    printf("Entrez la phrase a rechercher : ");
    scanf(" %255[^\n]", phrase);

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    int numero_ligne = 0;
    printf("Resultats de la recherche :\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        numero_ligne++;
        int nombre = compter_occurrences(ligne, phrase);
        if (nombre > 0) {
            printf("Ligne %d, %d fois\n", numero_ligne, nombre);
        }
    }

    fclose(fichier);
    return 0;
}
