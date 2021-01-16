#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

typedef struct maillonAD
{
    int idAdherent;
    int jour;
    int mois;
    int annees;
    char civ[4];
    char prenomNom[20];
    struct maillonAD *s;
}MaillonAD,*ListeAD;



typedef struct maillonReserv
{
    int idResa;
    int idAdherent;
    int idJeu;
    int jour;
    int mois;
    int annees;
    struct maillonReserv *next;
}MaillonReserv, *ListeReserv;


typedef enum {faux,vrai} Booleen;

void global (void);
int test1 (Jeux *tabJeux[]);
int remplirTab(Jeux *tabJeux[],int taillePhyJeux);
void afficherJeux( Jeux *tabJeux[], int tailleLogJeux);
Jeux LireJeux (FILE *flot);
int choixMenu (Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r);
void sousMenu(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r);
void affichageMenu(void);
void triTabJeux(Jeux *tabJeux[], int tailleLogJeux);
Jeux* copyJeu(Jeux *Jeu);


// LISTE
Liste listenouv(void);
Booleen vide(Liste l);
Liste testEmprunt (Liste l);
Liste insertionEnTete(Liste l,Maillon f);
void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux,ListeAD AD);
int rechercheID (Liste l, Jeux *tabJeux[],int *rang,int tailleLogJeux);


//LISTE ADHERENT
ListeAD ChargementAdherent (ListeAD l);
ListeAD insertionEnTeteAD(ListeAD l,MaillonAD f);
ListeAD listenouvAD(void);


//LISTE RESERVATION
int rechercheRangAvecLeNomJeux (char nomJeux[], Jeux *tabJeux[],int *trouve,int tailleLogJeux);
void affichageReservation (ListeReserv r,Jeux *tabJeux[], int tailleLogJeux);
int rechPuisAffichage (ListeReserv r,char nomJeux[], int idJeux,int trouve);


// Chargement Réservations
ListeReserv testReservation (ListeReserv r);
ListeReserv insertionEnTeteReserv (ListeReserv r, MaillonReserv res);
ListeReserv insertionCroissanteReserv(ListeReserv r, MaillonReserv mRES);
ListeReserv listenouvReserv ( void );
Booleen videReserv(ListeReserv r);


//test
void afficherListeADtempo(ListeAD AD);
void afficherListeReservtempo(ListeReserv r);
int reservoupas(ListeReserv r,char nomJeux[], int idJeux);
int globalNouvEnreg(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD, ListeReserv r);
ListeAD insertionCroissanteAD(ListeAD l,MaillonAD f);
int nouvelIDAD(ListeAD AD);
Liste insertionCroissante(Liste l, Maillon f);
void afficherListeTemp(Liste l);
int rechercheIDAD(char prenomNomExistant[], ListeAD AD);
int creationAdherent(ListeAD AD);

void nouvelEmprunt(Liste e, int IDjeu, int IDAD);
int nouvelIDEmp(Liste e);
void nouvelleReservation(ListeReserv r, int IDjeu,int IDAD);
int nouvelIDRes(ListeReserv r);