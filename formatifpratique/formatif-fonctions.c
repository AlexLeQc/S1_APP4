
#include "formatif-fonctions.h"




int lireFichier(char fichier[],
struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fp1;
	fp1 = fopen(fichier, "r");
	if (fp1==NULL)
	{
		return 0;
	}
	for(int i=0; i<MAX_NOMS; i++)
	{
		fscanf(fp1,"%s %s",tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
		//printf("%s %s\n",tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
	}
	fclose(fp1);
	return 1;
}

int chercherNom(struct PrenomPopularite tableauPrenomPopulariteGarcons[],
struct PrenomPopularite tableauPrenomPopulariteFilles[], char votreNom[])
{
	int position;
	if (chercherNomTableau(tableauPrenomPopulariteGarcons, votreNom, &position)== 1)
	{
		afficheMessageNomTrouve(votreNom, position, GARCONS, tableauPrenomPopulariteGarcons[position-1].popularite);
	}
	else
	{
		afficheMessageNomNonTrouve(votreNom, GARCONS);
	}
	if (chercherNomTableau(tableauPrenomPopulariteFilles, votreNom, &position)== 1)
	{
		afficheMessageNomTrouve(votreNom, position, FILLES, tableauPrenomPopulariteFilles[position-1].popularite);
	}
	else
	{
		afficheMessageNomNonTrouve(votreNom, FILLES);
	}
	return 1;
}

int chercherNomTableau(struct PrenomPopularite tableauPrenomPopularite[],
    char votreNom[], int* position)
    {
		int validation = 0;
		for(int i = 0; i < MAX_NOMS; i++)
		{
			if(strcmp(tableauPrenomPopularite[i].prenom, votreNom)==0)
			{
				validation = 1;
				*position = i+1;
			}
		}
		return validation;
	 }
	 
void afficheMessageNomTrouve(char nom[], int position, char SEXE[],
    char popularite[])
    {
		printf("%s est a la position %d des %s avec %s occurrences.\n", nom, position, SEXE, popularite);
	}
	
void afficheMessageNomNonTrouve(char nom[], char SEXE[])
{
	printf("%s n'est pas dans les %d prenom de %s les plus populaires.\n", nom, MAX_NOMS, SEXE);
}

int creerRapport(char nomFichier[], char sexe[], int nombreElementsRapport,
struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fp2;
	fp2 = fopen(nomFichier,"w");
	fprintf(fp2,"	%d prenoms des %s les plus populaires\n",nombreElementsRapport, sexe);
	fprintf(fp2,"		Nom			Occurences\n");
	for(int i = 0; i < nombreElementsRapport; i++)
	{
		fprintf(fp2,"	%s 		%s\n", tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
	}
	fclose(fp2);			
	return 1;
}








