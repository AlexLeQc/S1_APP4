/*********************************************************
Fichier     : formatif-main.c
Auteur      : Domingo Palao Munoz
Date        : 30 octobre 2019
Description : fichier avec le programme principal
**********************************************************/
/* NE CHANGEZ PAS CE FICHIER */

#include "formatif-fonctions.h"

// Prototype - Methodes utilisees si les options SANS lecture de fichier sont decommentes.
void chargerDonneesGarcons(struct PrenomPopularite tableauPrenomPopulariteGarcons[MAX_NOMS]);
void chargerDonneesFilles(struct PrenomPopularite tableauPrenomPopulariteFilles[MAX_NOMS]);

// Le numero d'options dans le menu
const int VALEUR_MINIMALE = 1;
const int VALEUR_MAXIMALE = 5;

// Les choix dans le menu
#define LIRE_FICHIER_GARCONS 1
#define LIRE_FICHIER_FILLES 2
#define CHERCHER_PRENOM 3
#define CREER_RAPPORT 4
#define SORTIR 5

// Fonction principale
int main()
{
    int choix = 0; // choix pour le menu
    char votreNom[TAILLE_NOMS]; // pour la recherche de noms
    int lireFichierFille = 0;
    int lireFichierGarcon = 0;
    int option; // selectionner garcons, filles

    // les tableaux pour les noms de garcons
    struct PrenomPopularite tableauPrenomPopulariteGarcons[MAX_NOMS];

    // les tableaux pour les noms de filles
    struct PrenomPopularite tableauPrenomPopulariteFilles[MAX_NOMS];

    while (choix != SORTIR)
    {
        afficherMenu(); // Afficher le menu utilisateur

        printf("Veuillez entrer votre selection :");
        scanf("%d", &choix);
        switch (choix)
        {
        case LIRE_FICHIER_GARCONS:
            printf("Lire fichier garcons.\n");
            //***********************************************************************//
            // Option SANS lecture de fichier
            //     Note: Decommenter les 4 lignes de code ci-apres SEULEMENT SI 
            //           votre fonction de lecture de fichier ne fonctionne pas.
            //***********************************************************************//
            /*printf ("Charger donnees garcons.\n");
            chargerDonneesGarcons(tableauPrenomPopulariteGarcons);
            lireFichierGarcon = 1;
            break;*/

            // Option AVEC lecture de fichier
            // Si la lecture du fichier ne fonctionne pas, mettre en commentaire la ligne suivante
            lireFichierGarcon = lireFichier(FICHIER_GARCONS, tableauPrenomPopulariteGarcons);
            if (lireFichierGarcon == 1)
            {
                printf("Lecture du fichier des garcons reussi!\n");
            }
            else
            {
                printf("Erreur dans la lecture du fichier des garcons...");
            }
            break;

        case LIRE_FICHIER_FILLES:
            printf("Lire fichier filles.\n");
            //***********************************************************************//
            // Option SANS lecture de fichier
            //     Note: Decommenter les 3 lignes de code ci-apres SEULEMENT SI 
            //           votre fonction de lecture de fichier ne fonctionne pas.
            //***********************************************************************//
            /*printf ("Charger donnees garcons.\n");
            chargerDonneesFilles(tableauPrenomPopulariteFilles);
            lireFichierFille = 1;
            break;*/

            // Option AVEC lecture de fichier
            // Si la lecture du fichier ne fonctionne pas, mettre en commentaire la ligne suivante
            lireFichierFille = lireFichier(FICHIER_FILLES, tableauPrenomPopulariteFilles);
            if (lireFichierFille)
            {
                printf("Lecture du fichier des filles reussi!\n");
            }
            else
            {
                printf("Erreur dans la lecture du fichier des filles...\n");
            }
            break;

        case CHERCHER_PRENOM:
            printf("Chercher prenom.\n");
            if (lireFichierFille && lireFichierGarcon)
            {
                printf("Entrez le nom a chercher\n");
                scanf("%s", votreNom);
                if (chercherNom(tableauPrenomPopulariteGarcons,
                    tableauPrenomPopulariteFilles,
                    votreNom))
                {
                    printf("Recherche du nom reussi!\n");
                }
                else
                {
                    printf("Le nom %s  n'est pas dans la liste.\n", votreNom);
                }
            }
            else
            {
                printf("ATTENTION veuillez lire les fichiers de noms de GARCONS et de FILLES\n");
                printf("AVANT de faire la recherche d'un nom.\n");
            }
            break;

        case CREER_RAPPORT:
            printf("Creer rapport.\n");
            printf("Vous voulez un rapport de Garcons (1) ou de Filles (2) :");
            scanf("%d", &option);
            if (option == 1)
            {
                if (lireFichierGarcon)
                {
                    if (creerRapport(FICHIER_SORTIE_GARCONS,
                        GARCONS,
                        NOMBRE_ELEMENTS_RAPPORT,
                        tableauPrenomPopulariteGarcons))
                    {
                        printf("Creation du rapport reussi!\n");
                    }
                    else
                    {
                        printf("Erreur dans la creation du rapport...\n");
                    }
                }
                else
                {
                    printf("ATTENTION veuillez lire le fichier de noms de GARCONS\n");
                    printf("AVANT de creer le rapport.\n");
                }
            }
            else if (option == 2)
            {
                if (lireFichierFille)
                {
                    if (creerRapport(FICHIER_SORTIE_FILLES,
                        FILLES,
                        NOMBRE_ELEMENTS_RAPPORT,
                        tableauPrenomPopulariteFilles))
                    {
                        printf("Creation du rapport reussi!\n");
                    }
                    else
                    {
                        printf("Erreur dans la creation du rapport...\n");
                    }
                }
                else
                {
                    printf("ATTENTION veuillez lire le fichier de noms de FILLE\n");
                    printf("AVANT de creer le rapport.\n");
                }
            }
            else
                printf("Option non valide.\n");
            break;

        case SORTIR:
            return EXIT_SUCCESS;
        default:
            printf("Option incorrecte...");
        }
    }

    printf("Fin du programme.\n");

    return 0;
}

/////////////////////////////////////////////////////////////////////////
//Fonctions utilitaires
/////////////////////////////////////////////////////////////////////////
void afficherMenu()
{
    // menu utilisateur
    printf(" \n");
    printf("-------------------------------------------------------------------\n");
    printf("Bienvenue au systeme d'aide au choix d'un prenom pour votre enfant.\n");
    printf(" 1.	Lire le fichier de prenoms de garcons.\n");
    printf(" 2.	Lire le fichier de prenoms de filles.\n");
    printf(" 3.	Chercher un prenom.\n");
    printf(" 4.	Creer fichier rapport (Les 5 plus populaires).\n");
    printf(" 5.	Sortir.\n");
    printf("-------------------------------------------------------------------\n");
    printf(" \n");

}

// Option SANS lecture de fichier...
// Chargement des donnees du tableau de prenom et popularite de garcons.
void chargerDonneesGarcons(struct PrenomPopularite tableauPrenomPopulariteGarcons[MAX_NOMS])
{
    struct PrenomPopularite nouveauNom1 = { "Jacob", "29195" };
    tableauPrenomPopulariteGarcons[0] = nouveauNom1;
    struct PrenomPopularite nouveauNom2 = { "Michael", "26991" };
    tableauPrenomPopulariteGarcons[1] = nouveauNom2;
    struct PrenomPopularite nouveauNom3 = { "Joshua", "24950" };
    tableauPrenomPopulariteGarcons[2] = nouveauNom3;
    struct PrenomPopularite nouveauNom4 = { "Matthew", "23706" };
    tableauPrenomPopulariteGarcons[3] = nouveauNom4;
    struct PrenomPopularite nouveauNom5 = { "Andrew", "21852" };
    tableauPrenomPopulariteGarcons[4] = nouveauNom5;
    struct PrenomPopularite nouveauNom6 = { "Joseph", "21265" };
    tableauPrenomPopulariteGarcons[5] = nouveauNom6;
    struct PrenomPopularite nouveauNom7 = { "Ethan", "21206" };
    tableauPrenomPopulariteGarcons[6] = nouveauNom7;
    struct PrenomPopularite nouveauNom8 = { "Daniel", "20947" };
    tableauPrenomPopulariteGarcons[7] = nouveauNom8;
    struct PrenomPopularite nouveauNom9 = { "Christopher", "20781" };
    tableauPrenomPopulariteGarcons[8] = nouveauNom9;
    struct PrenomPopularite nouveauNom10 = { "Anthony", "19990" };
    tableauPrenomPopulariteGarcons[9] = nouveauNom10;
}

// Option SANS lecture de fichier...
// Chargement des donnees du tableau de prenom et popularite de filles.
void chargerDonneesFilles(struct PrenomPopularite tableauPrenomPopulariteFilles[MAX_NOMS])
{

    struct PrenomPopularite nouveauNom1 = { "Emily", "25494" };
    tableauPrenomPopulariteFilles[0] = nouveauNom1;
    struct PrenomPopularite nouveauNom2 = { "Emma", "22532" };
    tableauPrenomPopulariteFilles[1] = nouveauNom2;
    struct PrenomPopularite nouveauNom3 = { "Madison", "19986" };
    tableauPrenomPopulariteFilles[2] = nouveauNom3;
    struct PrenomPopularite nouveauNom4 = { "Hannah", "17393" };
    tableauPrenomPopulariteFilles[3] = nouveauNom4;
    struct PrenomPopularite nouveauNom5 = { "Olivia", "15982" };
    tableauPrenomPopulariteFilles[4] = nouveauNom5;
    struct PrenomPopularite nouveauNom6 = { "Abigail", "15789" };
    tableauPrenomPopulariteFilles[5] = nouveauNom6;
    struct PrenomPopularite nouveauNom7 = { "Alexis", "14659" };
    tableauPrenomPopulariteFilles[6] = nouveauNom7;
    struct PrenomPopularite nouveauNom8 = { "Ashley", "14402" };
    tableauPrenomPopulariteFilles[7] = nouveauNom8;
    struct PrenomPopularite nouveauNom9 = { "Elizabeth", "13927" };
    tableauPrenomPopulariteFilles[8] = nouveauNom9;
    struct PrenomPopularite nouveauNom10 = { "Samantha", "13733" };
    tableauPrenomPopulariteFilles[9] = nouveauNom10;
}
