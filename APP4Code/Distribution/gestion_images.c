/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 25 octobre 2018
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"
#include "Autovalidation.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];
struct MetaData wow = {"Nom prenom", "2003-02-13","jamal"};
int main()
{
	AutoValidation();
	
   /* int lignes1, colonnes1;
    int lignes2, colonnes2;
    int maxval;
    int maxvalRGB;
    int histogramme[MAX_VALEUR+1];
    char nom[MAX_CHAINE];
    struct MetaData metadonnees;
    struct MetaData metadonneesRGB;

	int retour;

    printf("-> Debut!\n");

	// exemple d'appel de fonction
    retour = pgm_lire("Sherbrooke_Frontenac_nuit1.pgm", image1, 
                      &lignes1, &colonnes1, 
                      &maxval, &metadonnees);

	// exemple detraitement d'un code de retour (erreur ou reussite)
	printf("-> Retour: ");
	if (retour == OK)
		printf("-> OK");
	else
		printf("-> ERREUR");
	printf("\n");

	// autre exemple d'appel de fonction

               
    //pgm_creer_histogramme(image1, lignes1, colonnes1, histogramme);
    
    //pgm_couleur_preponderante(image1, lignes1, colonnes1);
    
    //pgm_eclaircir_noircir(image1,lignes1, colonnes1, maxval, 100);
    
    //pgm_creer_negatif(image1, lignes1, colonnes1, maxval);
    
	//pgm_extraire(image1, 30, 40, 100, 110, &lignes1, &colonnes1);
	
	//pgm_pivoter90(image1, &lignes1, &colonnes1, 0);
    
    //pgm_ecrire("grosbs.pgm", image1, lignes1, colonnes1, maxval, metadonnees);
                   
	//pgm_sont_identiques(image1, lignes1, colonnes1, image1, lignes1, colonnes1;
	    printf("-> Debut!\n");

	// exemple d'appel de fonction
    retour = ppm_lire("Sherbrooke_Frontenac_nuit344.ppm", imageRGB1, 
                      &lignes2, &colonnes2, 
                      &maxvalRGB, &metadonneesRGB);
    ppm_pivoter90(imageRGB1, &lignes2, &colonnes2, 1);
    if  (ppm_sont_identiques(imageRGB1, lignes2, colonnes2, imageRGB1, lignes2, colonnes2)== IDENTIQUES)
    {
		printf("IDENTIQUE");
	}
	
    
    ppm_ecrire("fraisinette.ppm",imageRGB1, lignes2, colonnes2, maxvalRGB, metadonneesRGB);
    
    

	// exemple detraitement d'un code de retour (erreur ou reussite)
	printf("-> Retour: ");
	if (retour == OK)
		printf("-> OK");
	else
		printf("-> ERREUR");
	printf("\n");

    printf("-> Fin!");*/

    return 0;
}
