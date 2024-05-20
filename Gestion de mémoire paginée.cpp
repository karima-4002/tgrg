#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure repr�sentant une page
typedef struct {
    int Nr_page;
    int Nr_Cadre;
} Page;

// Structure repr�sentant la m�moire pagin�e
typedef struct {
    int T_page;       // Taille de la page
    int T_RAM;        // Taille de la RAM
    int T_physique;   // Taille de la m�moire physique
    int nbr_Cadre;    // Nombre de cadres
    int nbr_page;     // Nombre de pages
    Page pg; // Table des pages
} MemoirePaginee;

// Fonction pour initialiser la m�moire pagin�e
void initialiserMemoirePaginee(MemoirePaginee *m, int T_page, int T_RAM, int T_physique, int nbr_Cadre, int nbr_page) {
    m->T_page = T_page;
    m->T_RAM = T_RAM;
    m->T_physique = T_physique;
    m->nbr_Cadre = nbr_Cadre;
    m->nbr_page = nbr_page;
    m->tablePages = (Page *)malloc(m->nbr_page * sizeof(Page));
}

// Fonction pour lib�rer la m�moire allou�e
void libererMemoire(MemoirePaginee *m) {
    free(m->tablePages);
}

char *hexadecimal_vers_binaire(const char *hexadecimal) {
    // V�rification de la longueur de la cha�ne hexad�cimale
    if (strlen(hexadecimal) != 8) {
        printf("Erreur: La cha�ne hexad�cimale doit avoir une longueur de 8 caract�res.\n");
        return NULL;
    }

    // Conversion de la cha�ne hexad�cimale en d�cimal
    int decimal = strtol(hexadecimal, NULL, 16);

    // Allocation de m�moire pour stocker l'adresse IP en format binaire
    char *binaire = (char *)malloc(33 * sizeof(char)); // 32 caract�res pour l'adresse IP binaire + 1 pour le caract�re nul
    if (binaire == NULL) {
        printf("Erreur d'allocation m�moire.\n");
        return NULL;
    }

    // Conversion du d�cimal en binaire
    for (int i = 31; i >= 0; --i) {
        binaire[i] = (decimal & 1) + '0';
        decimal >>= 1;
    }
    binaire[32] = '\0'; // Ajout du caract�re nul � la fin de la cha�ne

    return binaire;
}

// Calculer le logarithme en base 2 de la taille de la page en octets
double calculer_log2_taille_page_en_octets(unsigned long n) {
    return log2((double)n);
}

int main() {
    // D�claration de la m�moire pagin�e
    MemoirePaginee memoire;

    // Demander � l'utilisateur les param�tres de la m�moire pagin�e
    printf("Entrer la taille de la page (en octets) : ");
    scanf("%d", &memoire.T_page);
    printf("Entrer la taille de la m�moire physique (en octets) : ");
    scanf("%d", &memoire.T_physique);
    printf("Entrer la taille de la m�moire virtuelle (en octets) : ");
    scanf("%d", &memoire.T_RAM);
    printf("Entrer le nombre de cadres : ");
    scanf("%d", &memoire.nbr_Cadre);
    printf("Entrer le nombre de pages : ");
    scanf("%d", &memoire.nbr_page);

    // Initialisation de la m�moire pagin�e
    initialiserMemoirePaginee(&memoire, memoire.T_page, memoire.T_RAM, memoire.T_physique, memoire.nbr_Cadre, memoire.nbr_page);

    // Affichage des informations sur la m�moire pagin�e
    printf("Taille de la page: %d octets\n", memoire.T_page);
    printf("Taille de la RAM: %d octets\n", memoire.T_RAM);
    printf("Taille de la m�moire physique: %d octets\n", memoire.T_physique);
    printf("Nombre de cadres: %d\n", memoire.nbr_Cadre);
    printf("Nombre de pages: %d\n", memoire.nbr_page);

    // Conversion d'une adresse IP hexad�cimale en binaire
    const char *adresse_ip_hexadecimal = "C0A80101";
    char *adresse_ip_binaire = hexadecimal_vers_binaire(adresse_ip_hexadecimal);
    if (adresse_ip_binaire != NULL) {
        printf("Adresse IP binaire: %s\n", adresse_ip_binaire);
        free(adresse_ip_binaire); // Lib�ration de la m�moire allou�e dynamiquement
    }

    // Calcul du logarithme en base 2 de la taille de la page en octets
    unsigned long taille_page_en_octets = memoire.T_page;
    double log2_taille_page = calculer_log2_taille_page_en_octets(taille_page_en_octets);
    printf("Log2 de la taille de page en octets : %.2f\n", log2_taille_page);

    // Lib�ration de la m�moire allou�e
    libererMemoire(&memoire);

    return 0;
}


