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

typedef struct maillon
{	
	int idEmprunt;
    int idAdherent;
    int idJeu;
    int jour;
    int mois;
    int annees;
    struct maillon *suiv;
}Maillon, *Liste;

typedef enum {faux,vrai} Booleen;

void test1(void);
int remplirTab(Jeux *tabJeux[],int taillePhyJeux);
void afficherJeux( Jeux *tabJeux[], int tailleLogJeux);
Jeux LireJeux (FILE *flot);
int choixMenu (void);
void affichageMenu(void);
void triTabJeux(Jeux *tabJeux[], int tailleLogJeux);
Jeux* copyJeu(Jeux *Jeu);


// LISTE
Liste listenouv(void);
Booleen vide(Liste l);
void testEmprunt ();
Liste insertionEnTete(Liste l,Maillon f);
void afficherListe(Liste l);
//Liste insertionEnTete(Liste l, int x);
//Liste inserer(Liste l, int x);


