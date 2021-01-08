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
                                   // Chargement Tableau des reservations
    ListeReserv r;
    r=testReservation(r);
    /*----------------------------------------------------------------------------*/
    choixMenu(tabJeux,tailleLogJeux,l,AD,r);            //Puis le choix 
}


// -------------------------------------- Menu et sous menu ------------------------------------------


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
		printf("\n\tErreur lors du choix du menu, veuillez reessayer :");
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
        /*afficherListeADtempo(AD);*/
        afficherListe(l,tabJeux,tailleLogJeux,AD);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 3:
        system("cls");
        // afficherListeReservtempo(r);
        affichageReservation(r,tabJeux,tailleLogJeux);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 7:
        break;
	default:
		break;
	}
	return choix;
}

void sousMenu(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD,ListeReserv r)
{
    int choix2;
    printf("\nSelectionner un bouton du menu :");
    printf("\n\n1. Retour au menu\t\t2. Quitter\n");
    scanf("%d", &choix2);
    while(choix2<1 || choix2 >2)
    {
        affichageMenu();
        printf("\n\tErreur lors du choix du menu, veuillez reessayer :");
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


// ------------------------------------------------ Chargement et tri du fichier jeu en mémoire ----------------------------------------------------------


int test1 (Jeux *tabJeux[])
{    
    int tailleLogJeux;
    tailleLogJeux=remplirTab(tabJeux,50);
    triTabJeux(tabJeux,tailleLogJeux);
    return tailleLogJeux;
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
            if((strcmp(tabJeux[j]->type, tabJeux[i]->type))==0)
            {
                if((strcmp(tabJeux[j]->nom, tabJeux[i]->nom))<0)
                {
                    tmp=copyJeu(tabJeux[i]);
                    tabJeux[i]=tabJeux[j];
                    tabJeux[j]=tmp;
                }
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


//------------------------------------------- Création de la liste d'emprunt ---------------------------------------------


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
    fscanf(flux,"%d%d%d%d%d%d%*c",&f.idEmprunt,&f.idAdherent,&f.idJeu,&f.jour,&f.mois,&f.annees);
    while(!feof(flux))
    {
        l=insertionEnTete(l,f);
        fscanf(flux,"%d%d%d%d%d%d%*c",&f.idEmprunt,&f.idAdherent,&f.idJeu,&f.jour,&f.mois,&f.annees);
    }
    fclose(flux);
    return l;
}

Liste listenouv(void)
{
    return NULL;
}

Liste insertionEnTete(Liste l,Maillon f)
{   
    Maillon *m;
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


//------------------------------------------- Création de la liste d'adhérents ---------------------------------------------


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
    fscanf(flex,"%d %d %d %d %s", &f.idAdherent, &f.jour, &f.mois, &f.annees, f.civ);
    fgets(f.prenomNom,40,flex);
    f.prenomNom[strlen(f.prenomNom)-1] = '\0';
    while(!feof(flex))
    {
        l=insertionEnTeteAD(l,f);
        fscanf(flex,"%d %d %d %d %s", &f.idAdherent, &f.jour, &f.mois, &f.annees, f.civ);
        fgets(f.prenomNom,40,flex);
        f.prenomNom[strlen(f.prenomNom)-1] = '\0';
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



//------------------------------- Création de la liste de réservation ---------------------------------------



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
    return r;
}

ListeReserv listenouvReserv(void)
{
    ListeReserv l;
    l=NULL;
    return l;
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


// ------------------------------- Fonction 1 : affichage des jeux disponibles ---------------------------------------------------



void afficherJeux( Jeux *tabJeux[], int tailleLogJeux)
{    
    printf("\nidJeux\tNombre d'exemplaire(s)\t\tNombres d'exmplaires\t\tNom du Jeux\n\n");
    for (int i = 0; i < tailleLogJeux; ++i)
    {
        printf("%d\t%d\t\t\t\t%s\t\t\t%s\n",tabJeux[i]->id,tabJeux[i]->nbExemplaire,tabJeux[i]->nom,tabJeux[i]->type);
    }
}



// ------------------------------- Fonction 2 : affichage de la liste d'emprunts en cours ---------------------------------



void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux,ListeAD AD)
{
    int trouve;
    int rang;
    printf("Nom du jeu\tId de l'emprunteur\tDate de l'emprunteur\n");
    while (!vide(l))
    {   
        trouve=rechercheID(l,tabJeux,&rang,tailleLogJeux);
        if (trouve==1)
        {    
            printf("%s\t",tabJeux[rang]->nom);
            printf("%d %02d/%02d/%d %s%s\t",AD->idAdherent,AD->jour,AD->mois,AD->annees,AD->civ,AD->prenomNom);
            printf("%d/%d/%d\t\n", l->jour,l->mois,l->annees);
        }
        else
        {
            printf("Pas de nom correspondant\t");
            printf("%d %02d/%02d/%d %s%s\t",AD->idAdherent,AD->jour,AD->mois,AD->annees,AD->civ,AD->prenomNom);
            printf("%d/%d/%d\t\n", l->jour,l->mois,l->annees); 
        }
        printf("\n");
        l = l->suiv;
        AD = AD->s;
    }
}


int rechercheID (Liste l, Jeux *tabJeux[],int *rang,int tailleLogJeux)
{
    for (int i = 0; i < tailleLogJeux; i++)
    {
        if(l->idJeu==tabJeux[i]->id)
        { 
            *rang=i;
            return 1;
        }
    }
    return 0;
}

void afficherListeADtempo(ListeAD AD)
{
    while (AD!=NULL)
    {   
        printf("%d %02d/%02d/%d %s%s\t\n",AD->idAdherent,AD->jour,AD->mois,AD->annees,AD->civ,AD->prenomNom);
        AD = AD->s;
    }
}

Booleen vide(Liste l)
{
    if(l==NULL)
        return vrai;
    return faux;
}


//---------------------------- Fonction 3 : affichage des réservtions d'un jeu ------------------------------------



void afficherListeReservtempo(ListeReserv r)
{
    while (r!=NULL)
    {   
        printf("%02d\t%04d\t%d\t%02d/%02d/%d\n\n",r->idResa,r->idAdherent,r->idJeu,r->jour,r->mois,r->annees);
        r = r->next;
    }
}

void affichageReservation (ListeReserv r,Jeux *tabJeux[], int tailleLogJeux)
{   
    char nomJeux[20];
    int trouve;
    int i;
    int id;
    int c;
    printf("Quelle est le jeux que vous souhaitez afficher ?\n");
    c = getchar();
    fgets(nomJeux,20,stdin);
    nomJeux[strlen(nomJeux)-1] = '\0';
    i=rechercheRangAvecLeNomJeux(nomJeux,tabJeux,&trouve,tailleLogJeux);
    if (trouve==1)
    {
        id=tabJeux[i]->id;
        rechPuisAffichage(r,nomJeux,id,trouve);
    }
    else
    {   
        printf("\n");
        printf("Le jeu %s n'est pas reference dans les jeux dont dispose la ludotheque !\n\n",nomJeux);
    }
}

int rechercheRangAvecLeNomJeux (char nomJeux[], Jeux *tabJeux[],int *trouve,int tailleLogJeux)
{   
    int i=0;
    while(i<tailleLogJeux)
    {
        if (strcmp(nomJeux,tabJeux[i]->nom)==0)
        {
            *trouve=1;
            return i;
        }
    i++;
    }
    *trouve=0;
    return i;
}

int rechPuisAffichage (ListeReserv r,char nomJeux[], int idJeux,int erreur)
{   
    int i=0;
    int a;
    a=reservoupas(r,nomJeux,idJeux);
    printf("\n");
    if (a!=0)
    {
        printf("idReservation\tidAdhérent\tidJeux\tJJ/MM/AAAA \n\n");
        while (!videReserv(r))
        {   
            if(idJeux==r->idJeu)
            {   
                printf("%d\t%d\t\t%d\t%d/%d/%d\n\n",r->idResa,r->idAdherent,r->idJeu,r->jour,r->mois,r->annees);
                i++;
            }
            r = r->next;
        }
        printf("Il y a un total de %d réservation(s) pour le jeu ""%s""\n",i,nomJeux);
    }
    else
        printf("%s n'est réservé par personne !\n\n",nomJeux);        
}

int reservoupas(ListeReserv r,char nomJeux[], int idJeux)
{
    int a=0;
    while(idJeux!=r->idJeu)
    {
        a++;
        r = r->next;
    }
}

Booleen videReserv(ListeReserv r)
{

    if(r==NULL)
        return vrai;
    return faux;
}