#include <stdio.h>
#include <string.h>
#include "stats.h"

// Affiche les statistiques globales de la bibliothèque
void afficherStatistiques(Emprunt *emprunts, int nbEmprunts,
                          Utilisateur *users, int nbUsers,
                          Livre *livres, int nbLivres)
{
    printf("\n=== STATISTIQUES DE LA BIBLIOTHÈQUE ===\n");

    printf("Nombre total de livres : %d\n", nbLivres);
    printf("Nombre total d'utilisateurs : %d\n", nbUsers);
    printf("Nombre total d'emprunts : %d\n", nbEmprunts);

    // Calcul du taux de disponibilité
    int dispo = 0;
    for (int i = 0; i < nbLivres; i++)
        if (livres[i].disponible == 1) dispo++;

    float taux = (nbLivres > 0) ? ((float)dispo / nbLivres) * 100.0f : 0.0f;
    printf("Livres disponibles : %d (%.1f%%)\n", dispo, taux);

    // Détails plus avancés
    utilisateurLePlusActif(emprunts, nbEmprunts, users, nbUsers);
    livresLesPlusEmpruntes(emprunts, nbEmprunts, livres, nbLivres);

    printf("========================================\n");
}

// Cherche l'utilisateur ayant réalisé le plus d'emprunts
void utilisateurLePlusActif(Emprunt *emprunts, int nbEmprunts,
                            Utilisateur *users, int nbUsers)
{
    if (nbEmprunts == 0 || nbUsers == 0) {
        printf("Aucune donnée d'activité utilisateur.\n");
        return;
    }

    int maxCount = 0;
    int idMax = -1;

    // Pour chaque utilisateur, on compte le nombre d'emprunts le concernant
    for (int i = 0; i < nbUsers; i++) {
        int count = 0;
        for (int j = 0; j < nbEmprunts; j++)
            if (emprunts[j].idUtilisateur == users[i].id)
                count++;

        if (count > maxCount) {
            maxCount = count;
            idMax = i;
        }
    }

    if (idMax != -1)
        printf("Utilisateur le plus actif : %s %s (%d emprunts)\n",
               users[idMax].prenom, users[idMax].nom, maxCount);
}

// Cherche le livre le plus emprunté
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts, Livre *livres, int nbLivres)
{
    if (nbEmprunts == 0 || nbLivres == 0) {
        printf("Aucune donnée d’emprunt disponible.\n");
        return;
    }

    int count[100] = {0}; // tableau des compteurs, indexé comme livres[]

    // Compte le nombre d'emprunts par livre
    for (int i = 0; i < nbEmprunts; i++) {
        for (int j = 0; j < nbLivres; j++) {
            if (emprunts[i].idLivre == livres[j].id)
                count[j]++;
        }
    }

    int maxCount = 0;
    int indexMax = -1;
    for (int j = 0; j < nbLivres; j++) {
        if (count[j] > maxCount) {
            maxCount = count[j];
            indexMax = j;
        }
    }

    if (indexMax != -1)
        printf("Livre le plus emprunté : \"%s\" de %s (%d emprunts)\n",
               livres[indexMax].titre,
               livres[indexMax].auteur,
               maxCount);
}

