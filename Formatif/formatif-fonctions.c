/*********************************************************
Fichier     : formatif-fonctions.c
Auteur      : Alexis Guerard
Date        : 2 novembre 2022
Description : fichier avec fonction pour l'examen formatif
**********************************************************/

#include <stdio.h>
#include "formatif-fonctions.h"
#include <string.h>

int lireFichier(char fichier[],
struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fentrer;
	fentrer = fopen(fichier, "r");
	if (fentrer == NULL)
	{
		return 0;
	}
	for (int i = 0; i < MAX_NOMS; i++)
	{
		fscanf(fentrer, "%s %s", tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
	}
	fclose(fentrer);
	return 1;
}


int chercherNom(struct PrenomPopularite tableauPrenomPopulariteGarcons[],
struct PrenomPopularite tableauPrenomPopulariteFilles[], char votreNom[])
{
	int position;
	int nomtrouve = 0;
	if (chercherNomTableau(tableauPrenomPopulariteGarcons, votreNom, &position) == 1)
	{
		afficheMessageNomTrouve(votreNom, position, GARCONS, tableauPrenomPopulariteGarcons[position].popularite);
		nomtrouve = 1;
	}
	else
	{
		afficheMessageNomNonTrouve(votreNom, GARCONS);
	}
	if (chercherNomTableau(tableauPrenomPopulariteFilles, votreNom, &position) == 1)
	{
		afficheMessageNomTrouve(votreNom, position, FILLES, tableauPrenomPopulariteFilles[position].popularite);
		nomtrouve = 1;
	}
	else
	{
		afficheMessageNomNonTrouve(votreNom, FILLES);
	}
	return nomtrouve;

}



int chercherNomTableau(struct PrenomPopularite tableauPrenomPopularite[],
    char votreNom[], int* position)
   {	
	for (int i = 0; i < MAX_NOMS; i++)
	{
		if (strcmp(tableauPrenomPopularite[i].prenom, votreNom) == 0)
		{
			*position = i;
			return 1;
		}

	}	
	return 0;
}
    
 void afficheMessageNomTrouve(char nom[], int position, char SEXE[],
    char popularite[])
{
	printf("%s est a la position %d des %s avec %s occurences.\n", nom, position + 1, SEXE, popularite);
}
    
   
void afficheMessageNomNonTrouve(char nom[], char SEXE[])
{
	printf("%s n'est pas dans les 1000 prenoms de %s les plus populaires.\n", nom, SEXE);
}

int creerRapport(char nomFichier[], char sexe[], int nombreElementsRapport,
struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fsortie;
	fsortie = fopen(nomFichier,"w");
	if (fsortie == NULL)
	{
		return 0;
	}
	//creation du rapport
	fprintf(fsortie, "Voici le rapport des %d nom de %s les plus populaire\n", nombreElementsRapport, sexe);
	for (int i = 0;i < nombreElementsRapport; i++)
	{
		fprintf(fsortie," %d- %s		%s\n", i +1, tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
	}
	
	fclose(fsortie);
	
	
	return 1;
}


