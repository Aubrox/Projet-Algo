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


// Fonctions bonus

void afficherListeTemp(Liste l);
void afficherListeADtempo(ListeAD AD);
void afficherListeReservtempo(ListeReserv r);



// -------------------------------------- Menu et sous menu ------------------------------------------

int choixMenu (Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r);
void sousMenu(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r);
void affichageMenu(void);

// ------------------------------------------------ Chargement et tri du fichier jeu en mémoire ----------------------------------------------------------

int test1 (Jeux *tabJeux[]);
int remplirTab(Jeux *tabJeux[],int taillePhyJeux);
Jeux LireJeux (FILE *flot);
void triTabJeux(Jeux *tabJeux[], int tailleLogJeux);
Jeux* copyJeu(Jeux *Jeu);

//------------------------------------------- Création de la liste d'emprunt ---------------------------------------------

Liste listenouv(void);
Booleen vide(Liste l);
Liste testEmprunt (Liste l);
Liste insertionEnTete(Liste l,Maillon f);
Liste insertionCroissante(Liste l, Maillon f);

//------------------------------------------- Création de la liste d'adhérents ---------------------------------------------

ListeAD ChargementAdherent (ListeAD l);
ListeAD insertionEnTeteAD(ListeAD l,MaillonAD f);
ListeAD listenouvAD(void);
ListeAD insertionCroissanteAD(ListeAD l,MaillonAD f);

//------------------------------- Création de la liste de réservation ---------------------------------------

ListeReserv testReservation (ListeReserv r);
ListeReserv insertionEnTeteReserv (ListeReserv r, MaillonReserv res);
ListeReserv insertionCroissanteReserv(ListeReserv r, MaillonReserv mRES);
ListeReserv listenouvReserv ( void );

// ------------------------------- Fonction 1 : affichage des jeux disponibles ---------------------------------------------------

void afficherJeux( Jeux *tabJeux[], int tailleLogJeux);

// ------------------------------- Fonction 2 : affichage de la liste d'emprunts en cours ---------------------------------

void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux,ListeAD AD);
void affichageIdentiteAD(ListeAD AD, int idAD);

//---------------------------- Fonction 3 : affichage des résèrvations d'un jeu ------------------------------------

int rechercheRangAvecLeNomJeux (char nomJeux[], Jeux *tabJeux[],int *trouve,int tailleLogJeux);
void affichageReservation (ListeReserv r,Jeux *tabJeux[], int tailleLogJeux);
int rechPuisAffichage (ListeReserv r,char nomJeux[], int idJeux,int trouve);
int reservoupas(ListeReserv r,char nomJeux[], int idJeux);
Booleen videReserv(ListeReserv r);

//--------------------- Fonction 4 : Saisie et enregistrement d'un nouvel emprunt/reservation -----------------------------

int globalNouvEnreg(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD, ListeReserv r);
int nouvelIDAD(ListeAD AD);
int rechercheIDAD(char prenomNomExistant[], ListeAD AD);
int creationAdherent(ListeAD AD);
void nouvelEmprunt(Liste e, int IDjeu, int IDAD);
int nouvelIDEmp(Liste e);
void nouvelleReservation(ListeReserv r, int IDjeu,int IDAD);
int nouvelIDRes(ListeReserv r);

//--------------------------- Fonction 5 : retour d'un jeu ------------------------------

void retourJeux (ListeAD AD,ListeReserv R,Liste l,Jeux *tabJeux[],int tailleLogJeux);
void retourIDv2(char nomPrenom[],ListeAD AD,int *i,int *idBack);
int rechercheIDv4 (char nomJeux[], Jeux *tabJeux[],int tailleLogJeux);
int affectationReserv(ListeReserv r,int id,int *a);
ListeReserv supprimer(ListeReserv l, int x,int idJeux);
ListeReserv supprimerEnTete(ListeReserv l);
Liste ajoutEmprunt(Liste l,int idADnew,int idJeux,int idBackAD);
Liste supprimerEnTeteEmp(Liste l);
Liste supprimerEmp(Liste l,int idBackAD,int idJeux);
Booleen videAD(ListeAD AD);
int verificationJeux(Liste l,int idJeux);

//--------------------- Fonction 6 : annulation d'une réservation ---------------------

void affichageNbReservation (Jeux *tabJeux[], int tailleLogJeux,ListeAD AD,Liste l,ListeReserv r);
int nbReserv(ListeReserv r, int saisieID);
int rechercheIdAdherent(char nomPrenom[],ListeAD AD,int *trouve,int saisieID);
void afficherReservation(Jeux *tabJeux [], int j);
void rechJeuCorrespondant(Jeux *tabJeux[], ListeReserv r, int saisieID, int tailleLogJeux);
ListeReserv supprimerEnTeteRes(ListeReserv r);
ListeReserv supprimerReservation(ListeReserv r, int saisieID, int jeuSupp);
int findJeu (ListeReserv r, char nomJeu[20], Jeux *tabJeux[], int tailleLogJeux, Liste l, ListeAD AD, int saisieID);
ListeReserv supprimerReservationv2(ListeReserv r, int jeuSupp);

//----------------------- Fonction de sauvegarde ------------------------------

void sauvegardeEmprunts (Liste l);
void sauvegarderJeux(Jeux *tabJeux[], int tailleLogJeux);
void sauvegardeReserv(ListeReserv r);
void sauvegardeAD(ListeAD AD);