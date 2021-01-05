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

void global (void);
int test1 (Jeux *tabJeux[]);
int remplirTab(Jeux *tabJeux[],int taillePhyJeux);
void afficherJeux( Jeux *tabJeux[], int tailleLogJeux);
Jeux LireJeux (FILE *flot);
int choixMenu (Jeux *tabJeux[],int tailleLogJeux,Liste l);
void affichageMenu(void);
void triTabJeux(Jeux *tabJeux[], int tailleLogJeux);
Jeux* copyJeu(Jeux *Jeu);


// LISTE
Liste listenouv(void);
Booleen vide(Liste l);
Liste testEmprunt (Liste l);
Liste insertionEnTete(Liste l,Maillon f);
void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux);
int rechercheID (Liste l, Jeux *tabJeux[],int *rang,int tailleLogJeux);
//Liste insertionEnTete(Liste l, int x);
//Liste inserer(Liste l, int x);


