/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include "bibliotheque_images.h"
#include <string.h>

int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
             int *p_lignes, int *p_colonnes, 
             int *p_maxval, struct MetaData *p_metadonnees)
{
	char magic_numb[3];
	char verif[MAX_CHAINE];
	char placement1[MAX_CHAINE];
	char placement2[MAX_CHAINE];
	char placement3[MAX_CHAINE];
	FILE *flot_entree = NULL;
	flot_entree = fopen(nom_fichier, "r");
	if (flot_entree == NULL)
	{
		return ERREUR;
	}
	fgets(verif,MAX_CHAINE, flot_entree);
	if (verif[0] == '#')
	{
		int position = 1;
	    int finchaine = 1;		
		for (int i=1 ; verif[i] != ';';i++)
		{
			placement1[i-1] = verif[i];
			position++;
			finchaine++;
			if (verif[i] == '\0')
			{
				return ERREUR_FORMAT;
			}
		}
		placement1[finchaine] == '\0';
		finchaine = 1;
		position++;
		strcpy(p_metadonnees->auteur,placement1);
		for (int i=0 ; verif[position] != ';';i++)
		{
			placement2[i] = verif[position];
			position++;
			finchaine++;
			if (verif[i] == '\0')
			{
				return ERREUR_FORMAT;
			}
		}
		placement2[finchaine] == '\0';
		finchaine = 1;
		position++;
		strcpy(p_metadonnees->dateCreation,placement2);
		for (int i=0 ; verif[position] != '\n';i++)
		{
			placement3[i] = verif[position];
			finchaine++;
			position++;
		}
		strcpy(p_metadonnees->lieuCreation,placement3);
		placement3[finchaine] == '\0';
		fscanf(flot_entree,"%s", magic_numb);
	}
	else
	{
		magic_numb[0]=verif[0];
		magic_numb[1]=verif[1];
	}
	if (magic_numb[0] != 'P')
	{
		return ERREUR_FORMAT;
	}
	if (magic_numb[1] != '2')
	{
		return ERREUR_FORMAT;
	}
	fscanf(flot_entree, "%d %d", p_colonnes, p_lignes);
	if (*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
	{
		return ERREUR_TAILLE;
	}
	fscanf(flot_entree, "%d", p_maxval);
	if (*p_maxval > MAX_VALEUR)
	{
		return ERREUR_FORMAT;
	}
	for (int i = 0; i < *p_lignes; i++)
	{
		for (int j = 0; j < *p_colonnes; j++)
		{
			fscanf(flot_entree,"%d",&matrice[i][j]);
			if (matrice[i][j] > *p_maxval)
			{
				return ERREUR_FORMAT;
			}
		}
	}
	
	if(flot_entree != NULL) fclose(flot_entree);

    return OK;
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], 
               int lignes, int colonnes, 
               int maxval, struct MetaData metadonnees)
{
	FILE *flot_sortie = NULL;
	flot_sortie = fopen(nom_fichier,"w");
		if (flot_sortie == NULL)
	{
		return ERREUR;
	}
	char valid1[MAX_CHAINE];
	char valid2[MAX_CHAINE];
	char valid3[MAX_CHAINE];
	strcpy(valid1, metadonnees.auteur);
	strcpy(valid2, metadonnees.dateCreation);
	strcpy(valid3, metadonnees.lieuCreation);
	if (valid1[0] != '\0' || valid2[0] != '\0' || valid3[0] != '\0')
	{
		fprintf(flot_sortie, "#");
	}
	if (valid1[0] != '\0')
	{
		fprintf(flot_sortie, "%s", metadonnees.auteur);
	}
	if (valid1[0] != '\0' || valid2[0] != '\0' || valid3[0] != '\0')
	{
		fprintf(flot_sortie, ";");
	}
	if (valid2[0] != '\0')
	{
		fprintf(flot_sortie, "%s", metadonnees.dateCreation);
	}
	if (valid1[0] != '\0' || valid2[0] != '\0' || valid3[0] != '\0')
	{
		fprintf(flot_sortie, ";");
	}
	if (valid3[0] != '\0')
	{
		fprintf(flot_sortie, "%s",metadonnees.lieuCreation);
	}
	fprintf(flot_sortie, "\n");
	fprintf(flot_sortie, "P2\n");
	fprintf(flot_sortie, "%d %d\n", colonnes, lignes);
	if (colonnes > MAX_LARGEUR || lignes > MAX_HAUTEUR)
	{
		return ERREUR_FORMAT;
	}
	fprintf(flot_sortie, "%d\n", maxval);
	for (int i = 0; i < lignes; i++)
	{
		for (int j = 0; j < colonnes;j++)
		{
			fprintf(flot_sortie, "%d ",matrice[i][j]);
		}

	}
	if(flot_sortie != NULL) fclose(flot_sortie);
			
    return OK;
}

int pgm_copier( int matrice1[MAX_HAUTEUR][MAX_LARGEUR],int lignes1,int colonnes1,
				int matrice2[MAX_HAUTEUR][MAX_LARGEUR],int *p_lignes2,int *p_colonnes2)
{
	*p_lignes2 = lignes1;
	*p_colonnes2 = colonnes1;
	for (int i = 0; i < lignes1; i++)
	{
		for (int j = 0; j < colonnes1;j++)
		{
			matrice2[i][j]= matrice1[i][j];
		}

	}
	return OK; 

int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
							int lignes, int colonnes, int histogramme[MAX_VALEUR+1]) 
{
	int valeur;
	for (int i = 0; i < lignes; i++)
	{
		for (int j = 0; j < colonnes;j++)
		{
			valeur = matrice[i][j];
			histogramme[valeur]++;
		}

	}
	return OK;
}
	
	
int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
								int lignes, int colonnes)	
{
	int nbrtongris = 0;
	int tongris = 0;
	int histogramme[MAX_VALEUR];
	pgm_creer_histogramme(matrice,lignes,colonnes,histogramme);
	for (int i=0; i < 256; i++)
	{
		if (histogramme[i] > nbrtongris)
		{
			tongris = i;
			nbrtongris = histogramme[i];
		}
	}
	return tongris;
}
								
int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
				int lignes, int colonnes, int maxval, int valeur)
{
	for (int i = 0; i < lignes; i++)
	{
		for (int j = 0; j < colonnes;j++)
		{
			if (matrice[i][j] + valeur < 0 )
			{
				matrice[i][j] = 0;
			}
			else if (matrice[i][j] + valeur > maxval)
			{
				matrice[i][j] = maxval;
			}
			else 
			{
				matrice[i][j] = matrice[i][j] + valeur;
			}
		}

	}
	
	return OK;
}

int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
						int lignes, int colonnes, int maxval)
{
	for (int i = 0; i < lignes; i++)
	{
		for (int j = 0; j < colonnes;j++)
		{
			matrice[i][j] = maxval - matrice[i][j];
		}

	}
	
	return OK;
}		
	
int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
					int lignes1, int colonnes1, int lignes2, int colonnes2,
					int *p_lignes, int *p_colonnes)	
{
	if (*p_lignes <= lignes2 || *p_colonnes <= colonnes2 || *p_lignes <= lignes1 || *p_colonnes <= colonnes1 || lignes1 < 0 || colonnes1 < 0)
	{
		return ERREUR;
	}
	else 
	{
		*p_lignes = lignes2 - lignes1+1;
		*p_colonnes = colonnes2 - colonnes1+1;
	}
	
	for (int i = 0  ; i < *p_lignes; i++)
	{
		for (int j = 0; j < *p_colonnes; j++)
		{
			matrice[i][j] = matrice[lignes1 + i][colonnes1 + j];
		}

	}

	return OK;
}
	
int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1,
						int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)	
{
	if (lignes1 != lignes2 || colonnes1 != colonnes2)
	{
		return ERREUR_TAILLE;
	}
	
	for (int i = 0; i < lignes1; i++)
	{
		for (int j = 0; j < colonnes1;j++)
		{
			if (matrice1[i][j] != matrice2[i][j])
			{
				return DIFFERENTES;
			}
			
		}

	}

	return IDENTIQUES;
}


int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR],
					int *p_lignes, int *p_colonnes, int sens)
{
	int rotmatrice[*p_colonnes][*p_lignes];
	if (sens == SENS_HORAIRE)
	{
		for (int i = 0; i < *p_lignes; i++)
		{
			for (int j = 0; j < *p_colonnes;j++)
			{
				rotmatrice[j][*p_lignes-(i+1)] = matrice[i][j];
			}

		}	
	}	
	else if (sens == SENS_ANTIHORAIRE)
	{
		for (int i = 0; i < *p_lignes; i++)
		{
			for (int j = *p_colonnes-1; j >=0;j--)
			{
				rotmatrice[*p_colonnes-(j+1)][i] = matrice[i][j];
			}

		}	
	}	
	else {
		return ERREUR;
	}		
	int change = *p_lignes;
	*p_lignes = *p_colonnes;
	*p_colonnes = change;
	for (int i = 0; i < *p_lignes; i++)
	{
		for (int j = 0; j < *p_colonnes;j++)
		{
			matrice[i][j]= rotmatrice[i][j];
		}

	}

	return OK;
}
		
int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR],
				int *p_lignes, int *p_colonnes, int *p_maxval,
				struct MetaData *p_metadonnees)
{
	char magic_numb[3];
	char verif[MAX_CHAINE];
	char placement1[MAX_CHAINE];
	char placement2[MAX_CHAINE];
	char placement3[MAX_CHAINE];
	FILE *flot_entree = NULL;
	flot_entree = fopen(nom_fichier, "r");
	if (flot_entree == NULL)
	{
		return ERREUR;
	}
	fgets(verif,MAX_CHAINE, flot_entree);
	if (verif[0] == '#')
	{
		int position = 1;
		for (int i=1 ; verif[i] != ';';i++)
		{
			placement1[i-1] = verif[i];
			position++;
		}
		position++;
		strcpy(p_metadonnees->auteur,placement1);
		for (int i=0 ; verif[position] != ';';i++)
		{
			placement2[i] = verif[position];
			position++;
		}
		position++;
		strcpy(p_metadonnees->dateCreation,placement2);
		for (int i=0 ; verif[position] != '\n';i++)
		{
			placement3[i] = verif[position];
			position++;
		}
		strcpy(p_metadonnees->lieuCreation,placement3);
		
		fscanf(flot_entree,"%s", magic_numb);
	}
	else
	{
		magic_numb[0]=verif[0];
		magic_numb[1]=verif[1];
	}
	if (magic_numb[0] != 'P' || magic_numb[1] != '3')
	{
		return ERREUR_FORMAT;
	}
	fscanf(flot_entree, "%d %d", p_colonnes, p_lignes);
	if (*p_colonnes > MAX_LARGEUR || *p_lignes > MAX_HAUTEUR)
	{
		return ERREUR_TAILLE;
	}
	fscanf(flot_entree, "%d", p_maxval);
	if (*p_maxval > MAX_VALEUR)
	{
		return ERREUR_FORMAT;
	}
	for (int i = 0; i < *p_lignes; i++)
	{
		for (int j = 0; j < *p_colonnes; j++)
		{
			fscanf(flot_entree,"%d %d %d", &matrice[i][j].valeurR, &matrice[i][j].valeurG, &matrice[i][j].valeurB);
			if (matrice[i][j].valeurB > *p_maxval || matrice[i][j].valeurR > *p_maxval || matrice[i][j].valeurG > *p_maxval )
			{
				return ERREUR_FORMAT;
			}
		}
	}
	fclose(flot_entree);

    return OK;
}
							
int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	FILE *flot_sortie = NULL;
	flot_sortie = fopen(nom_fichier,"w");
	char valid1[MAX_CHAINE];
	char valid2[MAX_CHAINE];
	char valid3[MAX_CHAINE];
	strcpy(valid1, metadonnees.auteur);
	strcpy(valid2, metadonnees.dateCreation);
	strcpy(valid3, metadonnees.lieuCreation);
	if (valid1[0] != '\0' || valid2[0] != '\0' || valid3[0] != '\0')
	{
		fprintf(flot_sortie, "#");
	}
	if (valid1[0] != '\0')
	{
		fprintf(flot_sortie, "%s", metadonnees.auteur);
	}
	if (valid1[0] != '\0' || valid2[0] != '\0' || valid3[0] != '\0')
	{
		fprintf(flot_sortie, ";");
	}
	if (valid2[0] != '\0')
	{
		fprintf(flot_sortie, "%s", metadonnees.dateCreation);
	}
	if (valid1[0] != '\0' || valid2[0] != '\0' || valid3[0] != '\0')
	{
		fprintf(flot_sortie, ";");
	}
	if (valid3[0] != '\0')
	{
		fprintf(flot_sortie, "%s",metadonnees.lieuCreation);
	}
	fprintf(flot_sortie,"\n");
	fprintf(flot_sortie, "P3\n");
	fprintf(flot_sortie, "%d %d\n", colonnes, lignes);
	fprintf(flot_sortie, "%d\n", maxval);
	for (int i = 0; i < lignes; i++)
	{
		for (int j = 0; j < colonnes;j++)
		{
			fprintf(flot_sortie, "%d %d %d ",matrice[i][j].valeurR, matrice[i][j].valeurG, matrice[i][j].valeurB);
		}
		fprintf(flot_sortie,"\n");
	}
	fclose(flot_sortie);
			
    return OK;
}		
		
int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	*p_lignes2 = lignes1;
	*p_colonnes2 = colonnes1;
	for (int i = 0; i < lignes1; i++)
	{
		for (int j = 0; j < colonnes1;j++)
		{
			matrice2[i][j].valeurR= matrice1[i][j].valeurR;
			matrice2[i][j].valeurG= matrice1[i][j].valeurG;
			matrice2[i][j].valeurB= matrice1[i][j].valeurB;
		}

	}
	return OK; 
}
			
int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	if (lignes1 != lignes2 || colonnes1 != colonnes2)
	{
		return ERREUR_TAILLE;
	}
	
	for (int i = 0; i < lignes1; i++)
	{
		for (int j = 0; j < colonnes1;j++)
		{
			if (matrice1[i][j].valeurR != matrice2[i][j].valeurR || matrice1[i][j].valeurG != matrice2[i][j].valeurG ||  matrice1[i][j].valeurB != matrice2[i][j].valeurB )
			{
				return DIFFERENTES;
			}
			
		}

	}

	return IDENTIQUES;
}


int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	struct RGB rotmatrice[*p_colonnes][*p_lignes];
	if (sens == SENS_HORAIRE)
	{
		for (int i = 0; i < *p_lignes; i++)
		{
			for (int j = 0; j < *p_colonnes;j++)
			{
				rotmatrice[j][*p_lignes-(i+1)].valeurR = matrice[i][j].valeurR;
				rotmatrice[j][*p_lignes-(i+1)].valeurG = matrice[i][j].valeurG;
				rotmatrice[j][*p_lignes-(i+1)].valeurB = matrice[i][j].valeurB;
			}

		}	
	}	
	else if (sens == SENS_ANTIHORAIRE)
	{
		for (int i = 0; i < *p_lignes; i++)
		{
			for (int j = *p_colonnes-1; j >=0;j--)
			{
			rotmatrice[*p_colonnes-(j+1)][i].valeurR = matrice[i][j].valeurR;
			rotmatrice[*p_colonnes-(j+1)][i].valeurG = matrice[i][j].valeurG;
			rotmatrice[*p_colonnes-(j+1)][i].valeurB = matrice[i][j].valeurB;			
			}

		}	
	}	
	else {
		return ERREUR;
	}		
	int change = *p_lignes;
	*p_lignes = *p_colonnes;
	*p_colonnes = change;
	for (int i = 0; i < *p_lignes; i++)
	{
		for (int j = 0; j < *p_colonnes;j++)
		{
			matrice[i][j].valeurR= rotmatrice[i][j].valeurR;
			matrice[i][j].valeurG= rotmatrice[i][j].valeurG;
			matrice[i][j].valeurB= rotmatrice[i][j].valeurB;
		}

	}

	return OK;
}			
		
		
		
		
	
	
	
	
	
	
	
	
	
	
							

