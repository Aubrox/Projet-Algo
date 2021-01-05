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
    
    /*----------------------------------------------------------------------------*/
    choixMenu(tabJeux,tailleLogJeux,l);            //Puis le choix 
}
int test1 (Jeux *tabJeux[])
{    
    int tailleLogJeux;
    tailleLogJeux=remplirTab(tabJeux,50);
    triTabJeux(tabJeux,tailleLogJeux);
    afficherJeux(tabJeux,tailleLogJeux);
    return tailleLogJeux;
}

int choixMenu (Jeux *tabJeux[],int tailleLogJeux,Liste l)
{
	int choix;
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
        afficherJeux(tabJeux,tailleLogJeux);
        break;
	case 2:
        afficherListe(l,tabJeux,tailleLogJeux);
        break;
	default:
		break;
	}
	return choix;
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
    Liste l;
    l=NULL;
    return l;
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
    char dateEmp[20];
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

void afficherListe(Liste l, Jeux *tabJeux[], int tailleLogJeux)
{   
    int trouve;
    int rang;
    printf("Nom du jeu\tId de l'emprunteur\tDate de l'emprunteur\n");
    trouve=rechercheID(l,tabJeux,&rang,tailleLogJeux);
    while (!vide(l))
    {   
        if (trouve==1)
        {    
            printf("%s\t",tabJeux[rang]->nom);
            printf("ID emprunteur(nom prenom etc)\t");
            printf("%d/%d/%d\t\n", l->jour,l->mois,l->annees);    // FAUT FAIRE ADERENT POUR TOUS Y METRE DANS LE FIAK
        }
        else
        {
            printf("Pas de nom correspondant\t");
            printf("ID emprunteur(nom prenom etc)\t");
            printf("%d/%d/%d\t\n", l->jour,l->mois,l->annees);  
        }           
        printf("\n");
        l = l->suiv;
        trouve=rechercheID(l,tabJeux,&rang,tailleLogJeux);
    }
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
/*Liste insertionEnTete(Liste l, int x)
{   
    FILE* flot;
    
    Maillon *m;
    m = (Maillon*)malloc(sizeof(maillon));
    if (m==NULL)
    {
        printf("Pb malloc\n");
        exit(1);
    }
    m->idEmprunt = x;
    m->idAdherent = x;
    m->idJeu = x;
    m->dateEmp = x;
    m->suiv = l;
    return m;
}


/*Liste inserer(Liste l, int x)
{
    if(l==NULL)
        return insertionEnTete(l, x); 
    if(x < l->v)
        return insertionEnTete(l, x);
    if(x==l->v)
        return l;
    l->suiv = inserer(l->suiv, x);
    return l;
}
*/