#include "test.h"

void test1 (void)
{    
    int tailleLogJeux;
    Jeux *tabJeux[50];
    tailleLogJeux=remplirTab(tabJeux,50);
    triTabJeux(tabJeux,tailleLogJeux);
    afficherJeux(tabJeux,tailleLogJeux);
}

int choixMenu (void)
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
		test1();
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

