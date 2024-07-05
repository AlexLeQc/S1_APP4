
/*********************************************************
Fichier     : formatif-fonctions.c
Auteur      : Domingo Palao Munoz
Date        : 30 octobre 2019
Description : description: fichier avec les fonctions
**********************************************************/

/////////////////////////////////////////////////////////////////////////////////
// Le solutionnaire est une maniere de resoudre le probleme. Il est possible et
// tres probable que votre solution ne soit pas exactement pareille a la notre.
// Si le resultat obtenu est valide et que vous respectez les normes de
// programmation et les noms de fonctions et parametres, votre solution est correcte.
/////////////////////////////////////////////////////////////////////////////////

#include "formatif-fonctions.h"

// Lire un fichier selon le format indique
int lireFichier(char fichier[], 
                struct PrenomPopularite tableauPrenomPopularite[])
{
    FILE *fichierEntree;
    int i = 0; // compteur pour remplir les tableaux

    if ((fichierEntree = fopen(fichier, "r")) == NULL)
        return 0; //erreur

    while (!feof(fichierEntree))
    {
        fscanf(fichierEntree, "%s %s", tableauPrenomPopularite[i].prenom,
            tableauPrenomPopularite[i].popularite);
        i++;
    }
    fclose(fichierEntree);

    return 1;	// lecture reussie
}

// chercher votreNom dans les deux tableaux et affiche les messages
int chercherNom(struct PrenomPopularite tableauPrenomPopulariteGarcons[],
                struct PrenomPopularite tableauPrenomPopulariteFilles[], 
                char votreNom[])
{
    int position;
    int nomTrouve = 0;

    // On cherche chez les filles
    if (chercherNomTableau(tableauPrenomPopulariteFilles, votreNom, &position))
    {
        afficheMessageNomTrouve(votreNom, position, FILLES,
            tableauPrenomPopulariteFilles[position].popularite);
        nomTrouve = 1;
    }
    else
    {
        afficheMessageNomNonTrouve(votreNom, FILLES);
    }

    // On cherche chez les garcons.
    if (chercherNomTableau(tableauPrenomPopulariteGarcons, votreNom, &position))
    {
        afficheMessageNomTrouve(votreNom, position, GARCONS,
            tableauPrenomPopulariteGarcons[position].popularite);
        nomTrouve = 1;
    }
    else
    {
        afficheMessageNomNonTrouve(votreNom, GARCONS);
    }
    return nomTrouve;
}

// Cherche votreNom dans un tableau et retourne la position dans un parametre
int chercherNomTableau(struct PrenomPopularite tableauPrenomPopularite[MAX_NOMS],
                       char votreNom[TAILLE_NOMS], 
                       int *position)
{
    int i;
    for (i = 0; i < MAX_NOMS; i++)
    {
        if (strcmp(tableauPrenomPopularite[i].prenom, votreNom) == 0)
        {
            *position = i;
            return 1;
        }
    }
    return 0;
}

// Afficher le mesage lors que le nom a ete trouve
void afficheMessageNomTrouve(char nom[TAILLE_NOMS], 
                             int position,
                             char sexe[TAILLE_POPULARITE], 
                             char popularite[TAILLE_POPULARITE])
{
    printf("%s est a la position %d des %s avec %s occurences.\n",
        nom, position + 1, sexe, popularite);
}

//Afficher le message lors que le nom n'a pas ete trouve
void afficheMessageNomNonTrouve(char nom[TAILLE_NOMS], 
                                char sexe[TAILLE_POPULARITE])
{
    printf("%s n'est pas dans les 1000 prenoms de %s les plus populaires.\n",
        nom, sexe);
}

//Creer le rapport de 5 noms plus populaires
int creerRapport(char nomFichier[], 
                 char sexe[], 
                 int nombreElementsRapport,
                 struct PrenomPopularite tableauPrenomPopularite[])
{
    FILE *fichierRapport;
    int i;

    fichierRapport = fopen(nomFichier, "w");
    if (fichierRapport == NULL)
        return 0;		// lecture a echouee

    //Creation de l'entete
    fprintf(fichierRapport, "Rapport des %d noms les plus populaires chez les %s:\n\n",
        nombreElementsRapport, sexe);
    fprintf(fichierRapport, "Position    Nom                 Utilisations \n");

    for (i = 0; i < nombreElementsRapport; i++)
    {
        fprintf(fichierRapport, "%4d        %-25s %6s\n", i + 1,
            tableauPrenomPopularite[i].prenom, tableauPrenomPopularite[i].popularite);
    }
    fclose(fichierRapport);
    return 1;
}
