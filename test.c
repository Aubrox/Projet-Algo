#include "test.h"
void global (void)
{   
    Jeux *tabJeux[50];      /* Chargement tableau des Jeux*/
    int tailleLogJeux;
    tailleLogJeux=test1(tabJeux);
    /*----------------------------------------------------------------------------*/
    Liste l;                        // Chargement Tableau des emprunts
    l=testEmprunt(l);
    /*----------------------------------------------------------------------------*/
    ListeAD AD;
    AD=ChargementAdherent(AD);     //Chargement tableau des adherents
    /*----------------------------------------------------------------------------*/           
                                    //Chargement Tableau des reservations
    ListeReserv r;
    r=testReservation(r);
    /*----------------------------------------------------------------------------*/
    choixMenu(tabJeux,tailleLogJeux,l,AD,r);            //Puis le choix 
}
int test1 (Jeux *tabJeux[])
{    
    int tailleLogJeux;
    tailleLogJeux=remplirTab(tabJeux,50);
    triTabJeux(tabJeux,tailleLogJeux);
    afficherJeux(tabJeux,tailleLogJeux);
    return tailleLogJeux;
}


int choixMenu (Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r)
{
	int choix;
    int a;
	affichageMenu();
	printf("\n \t Selectionner un bouton du menu :");
	scanf("%i", &choix);
	while(choix<1 || choix >7)
	{
		affichageMenu();
		printf("Erreur lors du choix du menu, veuillez reessayer :");
		scanf("%d",&choix);
	}
	switch (choix)
	{
	case 1:
        system("cls");
        afficherJeux(tabJeux,tailleLogJeux);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
	case 2:
        system("cls");
        afficherListe(l,tabJeux,tailleLogJeux,AD);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 3:
        system("cls");
        affichageReservation(r,tabJeux,tailleLogJeux);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 4:
        // JADEN
        break;
    case 5:
        system("cls");
        retourJeux(AD,r,l,tabJeux,tailleLogJeux);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 6:
        /*system("cls");
        affichageNbReservation (r,tabJeux, tailleLogJeux);*/
	default:
		break;
	}
	return choix;
}
void sousMenu(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r)
{
    int choix2;
    printf("\nSelectionner un bouton du menu :");
    printf("\n\n1. Retour au menu\t\t2. Quiter\n");
    scanf("%d", &choix2);
    while(choix2<1 || choix2 >3)
    {
        affichageMenu();
        printf("Erreur lors du choix du menu, veuillez reessayer :");
        scanf("%d",&choix2);
    }
    switch (choix2)
    {
    case 1:
        choixMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 2:
        break;
    default:
        break;
    }
}

void affichageMenu(void)
{
	system("cls");
	printf("\n \n \n ");
	printf("\t 1. Affichage de la liste des jeux \n");
	printf("\t 2. Affichage de la liste des emprunts en cours \n");
	printf("\t 3. Affichage de la reservation pour un jeu donne \n");
	printf("\t 4. Saisie et enregistrement d'un nouvel emprunt/reservation \n");
	printf("\t 5. Retour d'un jeu \n");
	printf("\t 6. Annulation d'une reservation \n");
	printf("\t 7. Quitter l'application \n");
}

int remplirTab(Jeux *tabJeux[],int taillePhyJeux)
{    
    Jeux m;
    int tailleLogJeux=0;
    FILE *flot;
    flot=fopen("ficjeux.txt","r");
    if(flot== NULL)
    {
        printf("Erreur de chargement du ficjeux.txt\n");
        return -1;
    }
    m = LireJeux(flot);
    while(!feof(flot))
    {    
        if (tailleLogJeux==taillePhyJeux)
        {
        printf("Manque de place dans le tableau de Jeux\n");
        return -2;
        }
        tabJeux[tailleLogJeux] =(Jeux*) malloc(sizeof(Jeux));
        if (tabJeux[tailleLogJeux]==NULL)
        {
            printf("Problème d'allocation du tableau jeux\n");
            fclose(flot);
            return -3;
        }
        *tabJeux[tailleLogJeux]=m;
        tailleLogJeux=tailleLogJeux+1;
        m = LireJeux(flot);
    }
    fclose(flot);
    return tailleLogJeux;
}


Jeux LireJeux (FILE *flot)
{
    Jeux a;
    fscanf(flot,"%d",&a.id);
    fscanf(flot,"%s",a.type);
    fscanf(flot,"%d%*c",&a.nbExemplaire);
    fgets(a.nom,29,flot);
    a.nom[strlen(a.nom)-1] = '\0';
    return a;

}

void triTabJeux(Jeux *tabJeux[], int tailleLogJeux)
{
    int i, j;
    Jeux *tmp;
    for(i=0;i<tailleLogJeux;i++)
    {
        for(j=i+1 ; j<tailleLogJeux ; j++)
        {
            if((strcmp(tabJeux[j]->type, tabJeux[i]->type))<0)
            {
                tmp=copyJeu(tabJeux[i]);
                tabJeux[i]=tabJeux[j];
                tabJeux[j]=tmp;
            }
        }
    }
}

Jeux* copyJeu(Jeux *Jeu)
{
    Jeux *copie;
    copie=(Jeux*) malloc(sizeof(Jeux));
    copie->id=Jeu->id;
    strcpy(copie->nom,Jeu->nom);
    copie->nbExemplaire=Jeu->nbExemplaire;
    strcpy(copie->type,Jeu->type);
    return copie;
}

void afficherJeux( Jeux *tabJeux[], int tailleLogJeux)
{    
    printf("idJeux\ttypeJeux\tNombres d'exmplaires\tnomJeux\n");
    for (int i = 0; i < tailleLogJeux; ++i)
    {
        printf("  %d\t%s\t\t\t%d\t\t%s\n",tabJeux[i]->id,tabJeux[i]->type,tabJeux[i]->nbExemplaire,tabJeux[i]->nom);
    }
}


// Début des fonctions sur les listes 

Liste listenouv(void)
{
    return NULL;
}
Booleen vide(Liste l)
{
    if(l==NULL)
        return vrai;
    return faux;
}
Liste testEmprunt (Liste l)
{   
    Maillon f;
    FILE* flux;
    flux=fopen("Emprunts.txt","r");
    if(flux == NULL)
    {
        printf("Problème d'ouverture du fichier d'emprunt");
        exit(1);
    }
    l=listenouv();
    while(!feof(flux))
    {
        fscanf(flux,"%d%d%d%d%d%d%*c",&f.idEmprunt,&f.idAdherent,&f.idJeu,&f.jour,&f.mois,&f.annees);
        l=insertionEnTete(l,f);
    }
    fclose(flux);
    return l;
}

Liste insertionEnTete(Liste l,Maillon f)
{   
    Liste m;
    m = (Maillon*)malloc(sizeof(Maillon));
    if (m==NULL)
    {
        printf("Pb malloc\n");
        exit(1);
    }
    m->idEmprunt = f.idEmprunt;
    m->idAdherent = f.idAdherent;
    m->idJeu = f.idJeu;
    m->jour = f.jour;
    m->mois = f.mois;
    m->annees = f.annees;
    m->suiv = l;
    return m;
}

void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux,ListeAD AD)
{   
    int i=0;
    int trouve;
    int rang;
    printf("Nom du jeu\tId de l'emprunteur\tDate de l'emprunteur\n");
    trouve=rechercheID(l,tabJeux,&rang,tailleLogJeux);
    while (!vide(l))
    {   
        if (trouve==1)
        {    
            printf("%s\t",tabJeux[rang]->nom);
            printf("%d %02d/%02d/%d%s%s\t",AD->idAdherent,AD->jour,AD->mois,AD->annees,AD->civ,AD->prenomNom);
            printf("%d/%d/%d\t\n", l->jour,l->mois,l->annees);
        }
        else
        {
            printf("Pas de nom correspondant\t");
            printf("%d %02d/%02d/%d%s%s\t",AD->idAdherent,AD->jour,AD->mois,AD->annees,AD->civ,AD->prenomNom);
            printf("%d/%d/%d\t\n", l->jour,l->mois,l->annees); 
        }           
        i++;
        printf("\n");
        l = l->suiv;
        AD = AD->s;
        trouve=rechercheID(l,tabJeux,&rang,tailleLogJeux);
    }
    printf("%d\n", i);
}
int rechercheID (Liste l, Jeux *tabJeux[],int *rang,int tailleLogJeux)
{
    for (int i = 0; i < tailleLogJeux; ++i)
    {
        if(l->idJeu==tabJeux[i]->id)
        { 
        *rang=i;
        return 1;
        }
    }
    return 0;
}


/*---------------------------------------------------------------------------------*/
//Ici on s'occupe de Adherent
ListeAD listenouvAD(void)
{
    ListeAD l;
    l=NULL;
    return l;
}

ListeAD ChargementAdherent (ListeAD l)
{   
    MaillonAD f;
    FILE* flex;
    flex=fopen("Adherent.txt","r");
    if(flex == NULL)
    {
        printf("Problème d'ouverture du fichier d'emprunt");
        exit(1);
    }
    l=listenouvAD();
    while(!feof(flex))
    {
        fscanf(flex,"%d %d %d %d %s%*c", &f.idAdherent, &f.jour, &f.mois, &f.annees, f.civ);
        fgets(f.prenomNom,40,flex);
        f.prenomNom[strlen(f.prenomNom)-1] = '\0';
        l=insertionEnTeteAD(l,f);
    }
    fclose(flex);
    return l;
}

ListeAD insertionEnTeteAD(ListeAD l,MaillonAD f)
{   
    MaillonAD *m;
    m = (MaillonAD*)malloc(sizeof(MaillonAD));
    if (m==NULL)
    {
        printf("Pb malloc\n");
        exit(1);
    }
    m->idAdherent = f.idAdherent;
    strcpy(m->civ,f.civ);
    strcpy(m->prenomNom,f.prenomNom);
    m->jour = f.jour;
    m->mois = f.mois;
    m->annees = f.annees;
    m->s = l;
    return m;
}


//-------------------------------Code Réservation---------------------------------------//


ListeReserv listenouvReserv(void)
{
    ListeReserv l;
    l=NULL;
    return l;
}

ListeReserv testReservation (ListeReserv r)
{   
    MaillonReserv res;
    FILE* flux;
    flux=fopen("Reservation.txt","r");
    if(flux == NULL)
    {
        printf("Problème d'ouverture du fichier réservation");
        exit(1);
    }
    r=listenouvReserv();
    fscanf(flux,"%d%d%d%d%d%d%*c",&res.idResa,&res.idAdherent,&res.idJeu,&res.jour,&res.mois,&res.annees);
    while(!feof(flux))
    {
        r=insertionEnTeteReserv(r,res);
        fscanf(flux,"%d%d%d%d%d%d%*c",&res.idResa,&res.idAdherent,&res.idJeu,&res.jour,&res.mois,&res.annees);
    }
    fclose(flux);
    printf("%d",res.idAdherent);
    return r;
}

ListeReserv insertionEnTeteReserv(ListeReserv r,MaillonReserv res)
{   
    MaillonReserv *m;
    m = (MaillonReserv*)malloc(sizeof(MaillonReserv));
    if (m==NULL)
    {
        printf("Pb malloc\n");
        exit(1);
    }
    m->idResa = res.idResa;
    m->idAdherent = res.idAdherent;
    m->idJeu = res.idJeu;
    m->jour = res.jour;
    m->mois = res.mois;
    m->annees = res.annees;
    m->next = r;
    return m;
}
void affichageReservation (ListeReserv r,Jeux *tabJeux[], int tailleLogJeux)
{   
    char nomJeux[20];
    int erreur;
    int i;
    int id;
    int c;
    printf("Quelle est le jeux que vous souhaitez afficher ?\n");
    c=getchar();
    fgets(nomJeux,20,stdin);
    nomJeux[strlen(nomJeux)-1] = '\0';
    i=rechercheRangAvecLeNomJeux(nomJeux,tabJeux,&erreur,tailleLogJeux);
    if (erreur==0)
    {
        id=tabJeux[i]->id;
        rechPuisAffichage(r,tailleLogJeux,nomJeux,id,erreur);
    }
    else
    {   
        printf("\n");
        printf("Le jeux %s n'est pas reference dans les jeux dont dispose la ludotheque !\n\n",nomJeux);
    }
}

int rechercheRangAvecLeNomJeux (char nomJeux[], Jeux *tabJeux[],int *erreur,int tailleLogJeux)
{   
    int i=0;
    while(i<tailleLogJeux)
    {
    if (strcmp(nomJeux,tabJeux[i]->nom)==0)
        {
        *erreur=0;
        return i;
        }
    i++;
    }
    *erreur=1;
    return i;
}

int rechPuisAffichage (ListeReserv r,int tailleLogJeux,char nomJeux[], int idJeux,int erreur)
{   
    int i=0;
    printf("\n");
    while (!videReserv(r))
    {   
        if(idJeux==r->idJeu)
        {   
            printf("idResa\tidAdherent\tidJeux\tJJ/MM/AAAA \n\n");
            printf("%d\t%d\t\t%d\t%d/%d/%d\n\n",r->idResa,r->idAdherent,r->idJeu,r->jour,r->mois,r->annees); 
            i++;
        }
            r = r->next;
    }
    if (i==0)
    {
    printf("%s n'est pas reserver par personne !\n\n",nomJeux);
    }
    else
    printf("Vous avez un total %d reservation pour le jeu %s\n",i,nomJeux);   
}
Booleen videReserv(ListeReserv r)
{

    if(r==NULL)
        return vrai;
    return faux;
}

/*-----------------------------------------------------------------------------------------------------*/
//5. Retour d'un jeu

void retourJeux (ListeAD AD,ListeReserv r,Liste l,Jeux *tabJeux[],int tailleLogJeux)
{   
    int c;
    int idBackAD;
    int i;
    int idJeux;
    int idADnew;
    int a;
    char jeuxBack[20],nomPrenom[20];
    printf("Quelle est le jeu que vous voulez rendre ?\n");
    c=getchar();
    fgets(jeuxBack,20,stdin);
    jeuxBack[strlen(jeuxBack)-1] = '\0';
    printf("Donnez votre prenom et votre nom (le nom en MAJUSCULE):\n");   
    fgets(nomPrenom,20,stdin);
    nomPrenom[strlen(nomPrenom)-1] = '\0';
    retourIDv2(nomPrenom,AD,&i,&idBackAD);
    if(i>1)
    {
        printf("Desole,nous avons %d personne au meme nom et prenom que vous,veuillez renseignez votre idAdherent\n",i);
        scanf("%d",&idBackAD);
        printf("Vous avez ete identifier au %04d\n",idBackAD);
    }
    if (i==0)
    {
        printf("%s ne correspond pas a un adherent de la ludotheque\n",nomPrenom);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
    }
    if(i==1)
    {
        printf("Vous avez ete identifier au %04d\n",idBackAD);
    }
    idJeux=rechercheIDv4(jeuxBack,tabJeux,tailleLogJeux);
    idADnew=affectationReserv(r,idJeux,&a);
    printf("\n");
    printf("a : %d\n",a);
    if (a==1)
    {   
        r=supprimer(r,idADnew,idJeux);
        l=ajoutEmprunt(l,idADnew,idJeux,idBackAD);
    }
    if(a==0)
    {
        l=supprimerEmp(l,idBackAD,idJeux);
        //ajout +1 dans nbexmplaire avec la fonction de JAJA!
    }
    printf("Vous avez bien rendu le jeux %s, merci\n",jeuxBack);
}
void afficherListeReservtempo(ListeReserv r)
{
    while (r!=NULL)
    {   
        printf("%02d\t%04d\t%d\t%02d/%02d/%d\n",r->idResa,r->idAdherent,r->idJeu,r->jour,r->mois,r->annees);
        r = r->next;
    }
}
void afficherListeTemp(Liste l)
{
    while (l!=NULL)
    {   
        printf("%04d %04d %03d\t",l->idEmprunt,l->idAdherent,l->idJeu);
        printf("%02d/%02d/%d\t\n", l->jour,l->mois,l->annees);
        l = l->suiv;
    }
}
void retourIDv2(char nomPrenom[],ListeAD AD,int *i,int *idBack)
{   
    *i=0;
    while(!videAD(AD))
    {
    if(strcmp(nomPrenom,AD->prenomNom)==0)
        {
        *idBack=AD->idAdherent;
        *i=*i+1;
        }
    AD=AD->s;
    }
}
Booleen videAD(ListeAD AD)
{
    if(AD==NULL)
        return vrai;
    return faux;
}

int rechercheIDv4 (char nomJeux[], Jeux *tabJeux[],int tailleLogJeux)
{
    for (int i = 0; i < tailleLogJeux; ++i)
    {
        if(strcmp(nomJeux,tabJeux[i]->nom)==0)
        {   
            return tabJeux[i]->id;
        }
    }
    return 0;
}
int affectationReserv(ListeReserv r,int id,int *a)
{
    while(!videReserv(r))
    {
        if(r->idJeu==id)
        {
            *a=1;
            return r->idAdherent;
        }
    r=r->next;
    }
    *a=0;
    return 0;
}
ListeReserv supprimer(ListeReserv r, int x, int idJeux)
{   
    if (r==NULL)
    {
        printf("x n'existe pas dans l.\n");
        return r;
    }
    if (x == r->idAdherent)
        if(r->idJeu == idJeux)
            return supprimerEnTete(r);             
    r->next = supprimer(r->next, x,idJeux);
    return r;
}
ListeReserv supprimerEnTete(ListeReserv r)
{
  MaillonReserv *o;
  if (r==NULL)
  {
      printf("op interdite\n");
      exit (1);
  }
  o=r;
  r=r->next;
  free(o);
  return r;
}


Liste ajoutEmprunt(Liste l,int idADnew,int idJeux,int idBackAD)
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);
    while(!vide(l))
    {
        if(l->idAdherent==idBackAD && l->idJeu==idJeux)
        {   
            l->idAdherent=idADnew;
            l->jour=instant.tm_mday;
            l->mois=instant.tm_mon+1;
            l->annees=instant.tm_year+1900;
        }
    l=l->suiv;
    }
    return l;
}
Liste supprimerEmp(Liste l,int idBackAD,int idJeux)
{
    if (l==NULL)
    {
        return l;
    }
    if (idBackAD == l->idAdherent && idJeux == l->idJeu)
        return supprimerEnTeteEmp(l);   
    l->suiv = supprimerEmp(l->suiv, idBackAD, idJeux);
    return l;
}

Liste supprimerEnTeteEmp(Liste l)
{
    Maillon *m;
    if (l==NULL)
    {
        printf("opération interdite.\n");
        exit(1);
    }
    m = l;
    l = l->suiv;
    free(m);
    return l;
}

//----------------------------Annulation Reservation ------------------------------------------//
// Demander le prenom Nom de la personne, rechercher son ID Adherent via son nom puis rechercher la/les reservation(s) en cours en affichant les jeux reserver puis lui demander si il souhaite réellement l'annuler//
/*
void affichageNbReservation (Jeux *tabJeux[], int tailleLogJeux,ListeAD AD,Liste l,ListeReserv r)
{
    int i, idAdherent, erreur, nbReservation;
    char nomPrenom[20], nomJeu[20];
    char c, choix;
    int saisieID;
    printf("Saississez votre prenom et votre nom en majuscule : \n");
    c=getchar();
    fgets(nomPrenom,20,stdin);
    nomPrenom[strlen(nomPrenom)-1] = '\0';
    rechercheIdAdherent(nomPrenom, AD, &erreur, &saisieID);
    printf("Votre ID est %d \n", saisieID);
    printf("%s", nomPrenom);
    /*if(erreur=1)
    {
        printf("%s ne correspond pas a un adherent de la ludotheque\n",nomPrenom);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r); 
    }
    if(erreur=2)
    {
        printf("Il existe deux personne possédant le même prenom et nom que vous, veuillez renseignez votre ID adhérent s'il vous plait :\n");
        scanf("%d", saisieID);
    }
        printf("Voici vos reservations en cours :\n");
        //showReserv(tabJeux, AD);
        //nbReservation=nbReserv(AD, idAdherent);
        if(nbReservation=1)
        {
            printf("Voulez vous vraiment supprimer cette réservation ?(o/n)");
            scanf("%c", choix);
            if(choix='o')
                supprimerReservation();
            else 
                choixMenu(tabJeux, tailleLogJeux, l,AD,r);
            
        }
        if(nbReservation>1)
        {
            printf("Saississez le jeu dont vous voulez supprimer la réservation ");
            scanf("%s", nomJeu);
            supprimerReservation();
        }
        
    }*/
/*
int nbReserv(ListeAD AD, int idAdherent)
{
    int nbReservation=0;
    if(AD->s==NULL)
        return nbReservation;
 
    if (idAdherent==AD->idAdherent)
        nbReservation++;
    return showReserv(AD->s, idAdherent);
}
*/

/*Booleen videAD(ListeAD AD)
{
    if(AD==NULL)
        return vrai;
    return faux;
}
*/
void rechercheIdAdherent(char nomPrenom[],ListeAD AD,int *erreur,int *saisieID)
{   
    *erreur=0;
    while(AD!=NULL)
    {
        if(strcmp(nomPrenom,AD->prenomNom)==0)
            {
            *saisieID=AD->idAdherent;
            *erreur=*erreur+1;
            }
        AD=AD->s;
    }
}



/*
void showReserv(Jeux *tabJeux [], ListeAD AD,)
{

}

void rechJeuCorrespondant(Jeux *tabJeux[], ListeAD AD, *saisieID)
{
    if(strcmp(&saisieID))



}



// NOTE POUR LE PROCHAIN MEC QUI VIENT : Il manque a faire : rechJeuCorrespondant qui consiste a : via l'ID adherent, afficher le nom du jeu correspondant ( faire le pont entre LISTE AD et tabJeux)
// Supprimer la réservation correspondante à l'ID 
// Mettre toute les fct dans le .h 
<<<<<<< HEAD
// Je (Bastien) continue ce travail mais je galère un peu je me mets des notes a moi même allez merci 
*/
// Je (Bastien) continue ce travail mais je galère un peu je me mets des notes a moi même allez merci */
