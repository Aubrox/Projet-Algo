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

typedef struct maillonAD
{
    int idAdherent;
    int jour;
    int mois;
    int annees;
    char civ[20];
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
void affichageMenu(void);
void triTabJeux(Jeux *tabJeux[], int tailleLogJeux);
Jeux* copyJeu(Jeux *Jeu);
void sousMenu(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r);

// LISTE
Liste listenouv(void);
Booleen vide(Liste l);
Liste testEmprunt (Liste l);
Liste insertionEnTete(Liste l,Maillon f);
void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux,ListeAD AD);
int rechercheID (Liste l, Jeux *tabJeux[],int *rang,int tailleLogJeux);
//Liste insertionEnTete(Liste l, int x);
//Liste inserer(Liste l, int x);


//LISTE ADHERENT



ListeAD ChargementAdherent (ListeAD l);
ListeAD insertionEnTeteAD(ListeAD l,MaillonAD f);
ListeAD listenouvAD(void);

//LISTE RESERVATION
int rechercheRangAvecLeNomJeux (char nomJeux[], Jeux *tabJeux[],int *erreur,int tailleLogJeux);
void affichageReservation (ListeReserv r,Jeux *tabJeux[], int tailleLogJeux);
int rechPuisAffichage (ListeReserv r,int tailleLogJeux,char nomJeux[], int idJeux,int erreur);

// Chargement Réservations
ListeReserv testReservation (ListeReserv r);
ListeReserv insertionEnTeteReserv (ListeReserv r, MaillonReserv res);
ListeReserv listenouvReserv ( void );
Booleen videReserv(ListeReserv r);
void afficherListeADtempo(ListeAD AD);

/*
//retour d'un jeux
void retourJeux (ListeAD AD,ListeReserv R,Liste l,Jeux *tabJeux[],int tailleLogJeux);
Booleen videAD(ListeAD AD);
int comparaison (char Nom[],char Prenom[],ListeAD AD);
void retourIDv2(char nomPrenom[],ListeAD AD,int *i,int *idBack);
void decalerADroite(char jeuxBack[]);
//suite retour jeux
//int rechercheIDv3 (ListeReserv r, int idBackAD);
int rechercheIDv4 (char nomJeux[], Jeux *tabJeux[],int tailleLogJeux);
int affectationReserv(ListeReserv r,int id,int *a);
ListeReserv supprimer(ListeReserv l, int x);
ListeReserv supprimerEnTete(ListeReserv l);
Liste ajoutEmprunt(Liste l,int idADnew,int idJeux); */


//Annulation Reservation 
void affichageNbReservation (Jeux *tabJeux[], int tailleLogJeux,ListeAD AD, Liste l,ListeReserv r);
int rechercheIdAdherent(char nomPrenom[],ListeAD AD,int *trouve,int saisieID);
void afficherReservation(Jeux *tabJeux [], int j);
void rechJeuCorrespondant(Jeux *tabJeux[], ListeReserv r, int saisieID, char nomPrenom[20], int tailleLogJeux);
int nbReserv(ListeReserv r, int saisieID);
ListeReserv supprimerEnTete(ListeReserv r);
ListeReserv supprimerReservation(ListeReserv r, int saisieID);
ListeReserv supprimerReservationv2(ListeReserv r, int jeuSupp);
int findJeu (ListeReserv r, char nomJeu[20], Jeux *tabJeux[], int tailleLogJeux);
