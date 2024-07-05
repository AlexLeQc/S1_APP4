 #include "formatif-fonctions.h"



int lireFichier(char fichier[],
struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fichier_entre;
	fichier_entre = fopen(fichier,"r");
	if (fichier_entre == NULL)
	{
		return 0;
	}
	int i = 0;
	while (!feof(fichier_entre))
	{
		fscanf(fichier_entre, "%s %s", tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
		printf("%s %s\n",tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
		i++;
	}
	fclose(fichier_entre);
	return 1;
}
int chercherNom(struct PrenomPopularite tableauPrenomPopulariteGarcons[],
struct PrenomPopularite tableauPrenomPopulariteFilles[], char votreNom[])
{
	return 0;
}
int chercherNomTableau(struct PrenomPopularite tableauPrenomPopularite[],
    char votreNom[], int* position)
    {
		return 0;
	}
	
void afficheMessageNomTrouve(char nom[], int position, char SEXE[],
    char popularite[])
    {
	}
	
void afficheMessageNomNonTrouve(char nom[], char SEXE[])
{
}

int creerRapport(char nomFichier[], char sexe[], int nombreElementsRapport,
struct PrenomPopularite tableauPrenomPopularite[])
{
	FILE *fichier_sortie;
	fichier_sortie = fopen(nomFichier,"w");
	if (fichier_sortie == NULL)
	{
		return 0;
	}
	fprintf(fichier_sortie, "		Rapport des %d %s les plus populaires\n", nombreElementsRapport, sexe);
	fprintf(fichier_sortie, " 				NOM				OCCURENCE\n");
	for (int i = 0; i < nombreElementsRapport; i++)
	{
		fprintf(fichier_sortie, "                 %s               %s\n", tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
	}
	
	fclose(fichier_sortie);
	return 1;
}
