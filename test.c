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
	while(choix<1 || choix >8)
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
        afficherListe(l,tabJeux,tailleLogJeux,AD);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 3:
        system("cls");
        affichageReservation(r,tabJeux,tailleLogJeux);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 4:
        system("cls");
        globalNouvEnreg(tabJeux,tailleLogJeux,l,AD,r);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 5:
        system("cls");
        retourJeux (AD,r,l,tabJeux,tailleLogJeux);
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 6:
        system("cls");

        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
        break;
    case 7:
        break;
    case 8:
        system("cls");
        afficherJeux(tabJeux,tailleLogJeux);
        afficherListeTemp(l);
        printf("\n");
        afficherListeADtempo(AD);
        printf("\n");
        afficherListeReservtempo(r);
        printf("\n");
        sousMenu(tabJeux,tailleLogJeux,l,AD,r);
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
    printf("\n\n1 Retour au menu\t\t2 Quitter\n");
    scanf("%d", &choix2);
    while(choix2!=1 && choix2!=2)
    {
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
    printf("\t (8. Afichage des listes) \n");
}


//------------------------------------------------------- Fonctions d'affichage bonus ---------------------------------------------

void afficherListeTemp(Liste l)
{
    printf("Idemp IDad IDjeu dateEmp\n");
    while (l!=NULL)
    {   
        printf("%04d %04d %03d\t",l->idEmprunt,l->idAdherent,l->idJeu);
        printf("%02d/%02d/%d\t\n", l->jour,l->mois,l->annees);
        l = l->suiv;
    }
}

void afficherListeADtempo(ListeAD AD)
{
    printf("IDAD civ Nom        date\n");
    while (AD!=NULL)
    {   
        printf("%04d %s %s %02d/%02d/%d\t\n",AD->idAdherent,AD->civ,AD->prenomNom, AD->jour,AD->mois,AD->annees);
        AD = AD->s;
    }
}

void afficherListeReservtempo(ListeReserv r)
{
    printf("IDres IDAD IDjeu date\n");
    while (r!=NULL)
    {   
        printf("%02d\t%04d\t%d\t%02d/%02d/%d\n",r->idResa,r->idAdherent,r->idJeu,r->jour,r->mois,r->annees);
        r = r->next;
    }
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
    while(!feof(flux))
    {
        fscanf(flux,"%d%d%d%d%d%d%*c",&f.idEmprunt,&f.idAdherent,&f.idJeu,&f.jour,&f.mois,&f.annees);
        l=insertionCroissante(l,f);
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
    Maillon * m;
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

Liste insertionCroissante(Liste l, Maillon f)
{
    if(l==NULL)
        return insertionEnTete(l,f);
    if(f.annees<l->annees)
        return insertionEnTete(l,f);
    if(f.annees==l->annees)
    {
        if(f.mois<l->mois)
            return insertionEnTete(l,f);
        if(f.mois==l->mois)
        {
            if(f.jour<l->jour)
                return insertionEnTete(l,f);
        }
    }
    l->suiv=insertionCroissante(l->suiv,f);
    return l;
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
    while(!feof(flex))
    {
        fscanf(flex,"%d %d %d %d %s%*c", &f.idAdherent, &f.jour, &f.mois, &f.annees, f.civ);
        fgets(f.prenomNom,40,flex);
        f.prenomNom[strlen(f.prenomNom)-1] = '\0';
        l=insertionCroissanteAD(l,f);
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

ListeAD insertionCroissanteAD(ListeAD l,MaillonAD f)
{
    if(l==NULL)
        return insertionEnTeteAD(l,f);
    if(f.idAdherent<l->idAdherent)
        return insertionEnTeteAD(l,f);
    l->s=insertionCroissanteAD(l->s,f);
    return l;
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
    while(!feof(flux))
    {
        fscanf(flux,"%d%d%d%d%d%d%*c",&res.idResa,&res.idAdherent,&res.idJeu,&res.jour,&res.mois,&res.annees);
        r=insertionCroissanteReserv(r,res);
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

ListeReserv insertionCroissanteReserv(ListeReserv r, MaillonReserv mRES)
{
    if(r==NULL)
        return insertionEnTeteReserv(r,mRES);
    if(mRES.annees<r->annees)
        return insertionEnTeteReserv(r,mRES);
    if(mRES.annees==r->annees)
    {
        if(mRES.mois<r->mois)
            return insertionEnTeteReserv(r,mRES);
        if(mRES.mois==r->mois)
        {
            if(mRES.jour<r->jour)
                return insertionEnTeteReserv(r,mRES);
        }
    }
    r->next=insertionCroissanteReserv(r->next,mRES);
    return r;
}

// ------------------------------- Fonction 1 : affichage des jeux disponibles ---------------------------------------------------



void afficherJeux( Jeux *tabJeux[], int tailleLogJeux)
{    
    printf("idJeux\ttypeJeux\tNombres d'exmplaires\tnomJeux\n");
    for (int i = 0; i < tailleLogJeux; ++i)
    {
        printf("%d\t%s\t%d\t\t\t%s\n",tabJeux[i]->id,tabJeux[i]->type,tabJeux[i]->nbExemplaire,tabJeux[i]->nom);
    }
}


// ------------------------------- Fonction 2 : affichage de la liste d'emprunts en cours ---------------------------------



void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux,ListeAD AD)
{
    int trouve;
    int rang;
    printf("Nom du jeu\t\tId de l'emprunteur\tDate de l'emprunt\n\n");
    while (!vide(l))
    {   
        trouve=rechercheID(l,tabJeux,&rang,tailleLogJeux);
        if (trouve==1)
        {    
            printf("%s\t\t",tabJeux[rang]->nom);
            printf("%04d\t%s %s\t",AD->idAdherent,AD->civ,AD->prenomNom);
            printf("%02d/%02d/%d\t\n", l->jour,l->mois,l->annees);
        }
        else
        {
            printf("Pas de nom correspondant\t");
            printf("%d %02d/%02d/%d %s %s\t",AD->idAdherent,AD->jour,AD->mois,AD->annees,AD->civ,AD->prenomNom);
            printf("%d/%d/%d\t\n", l->jour,l->mois,l->annees); 
        }
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


Booleen vide(Liste l)
{
    if(l==NULL)
        return vrai;
    return faux;
}


//---------------------------- Fonction 3 : affichage des résèrvations d'un jeu ------------------------------------



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


//--------------------- Fonction 4 : Saisie et enregistrement d'un nouvel emprunt/reservation -----------------------------


int globalNouvEnreg(Jeux *tabJeux[],int tailleLogJeux,Liste l,ListeAD AD, ListeReserv r)
{
    int existe, trouve=0, i;
    int dispo, choix;
    int IDAD, IDjeu;
    char c;
    char prenomNomExistant[20], nomJeux[20];

    printf("Etes-vous deja adherent a notre ludotheque ?\n");
    printf("\n\n1 Oui\t\t2 Non\n");
    scanf("%d", &existe);
    while(existe<1 || existe >2)
    {
        printf("\n\tErreur lors du choix, veuillez reessayer :");
        scanf("%d",&existe);
    }
    if(existe==2)
    {
        IDAD=creationAdherent(AD);
        printf("Vous etes desormais adherent a notre ludotheque\n");
    }
    else
    {
        printf("Veuillez saisir votre prenom et votre nom\n");
        c=getchar();
        fgets(prenomNomExistant,40,stdin);
        prenomNomExistant[strlen(prenomNomExistant)-1] = '\0';
        IDAD=rechercheIDAD(prenomNomExistant,AD);
        printf("%d\n", IDAD);
        if (IDAD==0)
        {
            printf("Aucun adhérent correspondant a ce nom\n");
            return 1;
        }
    }
    printf("Quel jeu souhaitez vous emprunter parmis la liste suivante ?\n");
    afficherJeux(tabJeux,tailleLogJeux);
    fgets(nomJeux,20,stdin);
    nomJeux[strlen(nomJeux)-1] = '\0';
    for (i = 0; i < tailleLogJeux; i++)
    {
        if (strcmp(tabJeux[i]->nom,nomJeux)==0)
        {
            trouve=1;
            IDjeu=tabJeux[i]->id;
            dispo=tabJeux[i]->nbExemplaire;
            if (tabJeux[i]->nbExemplaire!=0)
            {
                tabJeux[i]->nbExemplaire=tabJeux[i]->nbExemplaire-1;
            }
        }
    }
    while(trouve==0)
    {
        printf("Ce jeu ne fait pas partie de la liste, veuillez resaisir :\n");
        fgets(nomJeux,20,stdin);
        nomJeux[strlen(nomJeux)-1] = '\0';
        for (i = 0; i < tailleLogJeux; i++)
        {
            if (strcmp(tabJeux[i]->nom,nomJeux)==0)
            {
                trouve=1;
                IDjeu=tabJeux[i]->id;
                dispo=tabJeux[i]->nbExemplaire;
                if (tabJeux[i]->nbExemplaire!=0)
                {
                    tabJeux[i]->nbExemplaire=tabJeux[i]->nbExemplaire-1;
                }
            }
        }
    }
    if (dispo==0)
    {
        printf("Jeu actuellement indisponible, souhaitez-vous le reserver ?\n");
        printf("\n\n1 Oui\t\t2 Non\n");
        scanf("%d", &choix);
        while(choix!=1 && choix!=2)
        {
            printf("\n\tErreur lors du choix, veuillez reessayer :");
            scanf("%d",&choix);
        }
        if (choix==1)
        {
            nouvelleReservation(r, IDjeu, IDAD);
            afficherListeReservtempo(r);
            printf("Reservation enregistree !\n");
        }
    }
    else
    {
        nouvelEmprunt(l, IDjeu, IDAD);
        afficherListeTemp(l);
        printf("Emprunt enregistre !\n");
    }
}

int nouvelIDAD(ListeAD AD)
{
    int nouvIDAD;
    while(AD!=NULL)
        {
            nouvIDAD=AD->idAdherent;
            AD=AD->s;
        }
    nouvIDAD=nouvIDAD+1;
    return nouvIDAD;
}

int creationAdherent(ListeAD AD)
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);

    int nouvIDAD;
    char c;
    MaillonAD mAD;
    printf("Veuillez saisir votre prenom et votre nom (exemple : Prenom NOM)\n");
    c=getchar();
    fgets(mAD.prenomNom,40,stdin);
    mAD.prenomNom[strlen(mAD.prenomNom)-1] = '\0';
    printf("Veuillez saisir votre civilite (Mr ou Mme)\n");
    scanf("%s",mAD.civ);
    while(strcmp(mAD.civ,"Mr")!=0 && strcmp(mAD.civ,"Mme")!=0)
    {
        printf("Veuillez resaisir\n");
        scanf("%s",mAD.civ);
    }
    c=getchar();
    mAD.jour=instant.tm_mday;
    mAD.mois=instant.tm_mon+1;
    mAD.annees=instant.tm_year+1900;
    nouvIDAD=nouvelIDAD(AD);
    mAD.idAdherent=nouvIDAD;
    AD=insertionCroissanteAD(AD,mAD);
    return nouvIDAD;
}

int rechercheIDAD(char prenomNomExistant[], ListeAD AD)
{
    int IDAD=0;
    while(AD!=NULL)
    {
        if(strcmp(prenomNomExistant,AD->prenomNom)==0)
            IDAD=AD->idAdherent;
        AD=AD->s;
    }
    return IDAD;
}

void nouvelEmprunt(Liste e, int IDjeu, int IDAD)
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);

    int nouvIDEmp;
    Maillon m;
    m.idEmprunt=nouvelIDEmp(e);
    m.idAdherent=IDAD;
    m.idJeu=IDjeu;
    m.jour=instant.tm_mday;
    m.mois=instant.tm_mon+1;
    m.annees=instant.tm_year+1900;
    e=insertionCroissante(e,m);
}

int nouvelIDEmp(Liste e)
{
    int nouvIDEmp;
    while(e!=NULL)
        {
            nouvIDEmp=e->idEmprunt;
            e=e->suiv;
        }
    nouvIDEmp=nouvIDEmp+1;
    return nouvIDEmp;
}

void nouvelleReservation(ListeReserv r, int IDjeu,int IDAD)
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);

    int nouvIDEmp;
    MaillonReserv m;
    m.idResa=nouvelIDRes(r);
    m.idAdherent=IDAD;
    m.idJeu=IDjeu;
    m.jour=instant.tm_mday;
    m.mois=instant.tm_mon+1;
    m.annees=instant.tm_year+1900;
    r=insertionCroissanteReserv(r,m);
}

int nouvelIDRes(ListeReserv r)
{
    int nouvIDRes;
    while(r!=NULL)
        {
            nouvIDRes=r->idResa;
            r=r->next;
        }
    nouvIDRes=nouvIDRes+1;
    return nouvIDRes;
}


//--------------------------- Fonction 5 : retour d'un jeu ------------------------------

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

//--------------------- Fonction 6 : annulation d'une réservation ---------------------




//----------------------- Fonction de sauvegarde ------------------------------