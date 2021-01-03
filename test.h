#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nom [20];
    char type [20];
    int nbExemplaire;
}Jeux;

void globalJeu(void);
int remplirTab(Jeux *tabJeux[],int taillePhyJeux);
void afficherJeux( Jeux *tabJeux[], int tailleLogJeux);
Jeux LireJeux (FILE *flot);
int choixMenu(void);
void affichageMenu(void);
void triTabJeux(Jeux *tabJeux[], int tailleLogJeux);
Jeux* copyJeu(Jeux *Jeu);
