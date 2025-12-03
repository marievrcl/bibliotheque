#include <stdio.h>
#include <string.h>
#include "stats.h"

// Affiche les statistiques globales de la bibliothèque
void afficherStatistiques(Emprunt *emprunts, int nbEmprunts,
                          Utilisateur *users, int nbUsers,
                          Livre *livres, int nbLivres)
{
    printf("\n=== STATISTIQUES DE LA BIBLIOTHÈQUE ===\n"); // Titre des stats

    // Affiche le nombre total de livres
    printf("Nombre total de livres : %d\n", nbLivres);

    // Affiche le nombre total d'utilisateurs
    printf("Nombre total d'utilisateurs : %d\n", nbUsers);

    // Affiche le nombre total d'emprunts
    printf("Nombre total d'emprunts : %d\n", nbEmprunts);

    // Calcul du nombre de livres disponibles
    int dispo = 0;                       // Compteur de livres disponibles
    for (int i = 0; i < nbLivres; i++)  // Boucle sur tous les livres
        if (livres[i].disponible == 1)  // Si le livre est disponible
            dispo++;                     // Incrémente le compteur

    // Calcul du taux de disponibilité en pourcentage
    float taux = (nbLivres > 0) ? ((float)dispo / nbLivres) * 100.0f : 0.0f;
    printf("Livres disponibles : %d (%.1f%%)\n", dispo, taux); // Affiche dispo et pourcentage

    // Affiche l'utilisateur le plus actif (celui ayant le plus d'emprunts)
    utilisateurLePlusActif(emprunts, nbEmprunts, users, nbUsers);

    // Affiche le livre le plus emprunté
    livresLesPlusEmpruntes(emprunts, nbEmprunts, livres, nbLivres);

    printf("========================================\n"); // Séparateur de fin
}

// Cherche l'utilisateur ayant réalisé le plus d'emprunts
void utilisateurLePlusActif(Emprunt *emprunts, int nbEmprunts,
                            Utilisateur *users, int nbUsers)
{
    // Cas où il n'y a pas de données
    if (nbEmprunts == 0 || nbUsers == 0) {
        printf("Aucune donnée d'activité utilisateur.\n");
        return;
    }

    int maxCount = 0; // Nombre maximum d'emprunts trouvés
    int idMax = -1;   // Index de l'utilisateur le plus actif

    // Pour chaque utilisateur, on compte le nombre d'emprunts le concernant
    for (int i = 0; i < nbUsers; i++) {
        int count = 0;                 // Compteur temporaire pour cet utilisateur
        for (int j = 0; j < nbEmprunts; j++) // Parcourt tous les emprunts
            if (emprunts[j].idUtilisateur == users[i].id) // Si emprunt de cet utilisateur
                count++;                // Incrémente le compteur

        // Si ce compteur est le plus grand trouvé jusqu'ici
        if (count > maxCount) {
            maxCount = count;          // Mise à jour du max
            idMax = i;                 // Sauvegarde de l’index
        }
    }

    // Si on a trouvé un utilisateur actif
    if (idMax != -1)
        printf("Utilisateur le plus actif : %s %s (%d emprunts)\n",
               users[idMax].prenom, users[idMax].nom, maxCount); // Affiche le résultat
}

// Cherche le livre le plus emprunté
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts, Livre *livres, int nbLivres)
{
    // Cas où il n'y a pas de données
    if (nbEmprunts == 0 || nbLivres == 0) {
        printf("Aucune donnée d’emprunt disponible.\n");
        return;
    }

    int count[100] = {0}; // Tableau pour compter les emprunts par livre, indexé comme livres[]

    // Compte le nombre d'emprunts par livre
    for (int i = 0; i < nbEmprunts; i++) {   // Pour chaque emprunt
        for (int j = 0; j < nbLivres; j++) { // Pour chaque livre
            if (emprunts[i].idLivre == livres[j].id) // Si l’emprunt concerne ce livre
                count[j]++;                        // Incrémente le compteur
        }
    }

    int maxCount = 0;  // Nombre maximum d’emprunts trouvés
    int indexMax = -1; // Index du livre le plus emprunté
    for (int j = 0; j < nbLivres; j++) {     // Parcourt tous les livres
        if (count[j] > maxCount) {           // Si ce livre a plus d’emprunts
            maxCount = count[j];             // Mise à jour du max
            indexMax = j;                     // Sauvegarde de l’index
        }
    }

    // Si on a trouvé un livre emprunté au moins une fois
    if (indexMax != -1)
        printf("Livre le plus emprunté : \"%s\" de %s (%d emprunts)\n",
               livres[indexMax].titre,      // Affiche le titre
               livres[indexMax].auteur,    // Affiche l’auteur
               maxCount);                   // Affiche le nombre d’emprunts
}
