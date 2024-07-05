#include "formatif-fonctions.h"
#include <string.h>

int lireFichier(char fichier[], struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fp1 = NULL;
	fp1 = fopen(fichier,"r");
	if (fp1 == NULL)
	{
		return 0;
	}
	for(int i= 0; i< MAX_NOMS; i++)
	{
		fscanf(fp1, "%s %s", tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
	}
	return 1;
}
// chercher votreNom dans les deux tableaux et affiche les messages
// parameters: 
//         tableauPrenomPopulariteGarcons : le tableau avec les noms des garcons
//         tableauPrenomPopulariteFilles : le tableau avec les noms des filles
//         votreNom : le nom a chercher
// return : 
//         1 : si tout se passe correctement
//         0 : s'il y a une erreur
int chercherNom(struct PrenomPopularite tableauPrenomPopulariteGarcons[],
				struct PrenomPopularite tableauPrenomPopulariteFilles[], char votreNom[])
{
	int position;
	if (chercherNomTableau(tableauPrenomPopulariteGarcons, votreNom, &position))
	{
		afficheMessageNomTrouve(votreNom, position, GARCONS, tableauPrenomPopulariteGarcons[position].popularite );
	}
	else
	{
		afficheMessageNomNonTrouve(votreNom, GARCONS);
		return 0;
	}
	if (chercherNomTableau(tableauPrenomPopulariteFilles, votreNom, &position))
	{
		afficheMessageNomTrouve(votreNom, position, FILLES, tableauPrenomPopulariteFilles[position].popularite );
	}
	else
	{
		afficheMessageNomNonTrouve(votreNom, FILLES);
		return 0;
	}
	return 1;
}

// Cherche votreNom dans un tableau et retourne la position dans un paramètre
// parameters: 
//         tableauPrenomPopularite : un tableau contenant les noms et la popularite
//         votreNom : le nom a chercher
//         position : la position dans le tableau ou se trouve le nom
// return : 
//         1 : si tout se passe correctement
//         0 : s'il y a une erreur
int chercherNomTableau(struct PrenomPopularite tableauPrenomPopularite[],
					   char votreNom[], int* position)
{	
	for (int i = 0; i < MAX_NOMS; i++)
	{
		if (strcmp(votreNom, tableauPrenomPopularite[i].prenom) == 0)
		{
			*position = i;
			return 1;
		}
	}
		
	return 0;
}

// Afficher le mesage lors que le nom a ete trouve
// parameters :
//         nom : le nom trouve
//         position : la position du nom
//         SEXE : le sexe du nom
//         popularite : la popularite du nom
// return :
//         aucun
void afficheMessageNomTrouve(char nom[], int position, char SEXE[],
							 char popularite[])
{
	printf("%s est a la position %d des %s avec %s occurences.\n", nom, position + 1, SEXE, popularite);
}
//Afficher le message lors que le nom n'a pas ete trouve
// parameters :
//         nom : le nom non trouve
//         SEXE : le sexe du nom
void afficheMessageNomNonTrouve(char nom[], char SEXE[])
{
	printf("%s n'est pas dans les 1000 prenomms de %s les plus populaire\n", nom, SEXE);
}

//Creer le rapport de 5 noms plus populaires
// parameters : 
//         nomFIchier : le nom du fichier de sortie
//         sexe : le sexe du tableau
//         nombreElementsRapport : combien d'elements a afficher dans le rapport
//         tableauPrenomPopularite : le tableau de donnees
int creerRapport(char nomFichier[], char sexe[], int nombreElementsRapport,
				 struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fp2 = NULL;
	fp2 = fopen(nomFichier, "w");
	if (fp2 == NULL)
	{
		return 0;
	}
	for( int i = 0; i < nombreElementsRapport; i++)
	{
		fprintf(fp2, "%s    %s\n", tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
	}
	
	
	return 1;
}
