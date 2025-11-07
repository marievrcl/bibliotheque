//
// Created by Marie Viricel on 06/11/2025.
//

#include <stdio.h>
#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"
#include <stdio.h>
#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"
#include "fichiers.h"
#include "stats.h"

int main(void) {
    Livre livres[100];
    Utilisateur utilisateurs[100];
    Emprunt emprunts[100];
    int nbLivres = 0, nbUsers = 0, nbEmprunts = 0;

    // Chargement des données depuis les fichiers
    chargerLivres(livres, &nbLivres);
    chargerUtilisateurs(utilisateurs, &nbUsers);
    chargerEmprunts(emprunts, &nbEmprunts);

    int choix;
    do {
        printf("\n=== MENU BIBLIOTHÈQUE ===\n");
        printf("1. Gestion des livres\n");
        printf("2. Gestion des utilisateurs\n");
        printf("3. Gestion des emprunts\n");
        printf("4. Statistiques\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        if (scanf("%d", &choix) != 1) choix = 0;

        switch (choix) {
            case 1: {
                int sousChoix;
                do {
                    printf("\n--- GESTION DES LIVRES ---\n");
                    printf("1. Afficher les livres\n");
                    printf("2. Ajouter un livre\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if (scanf("%d", &sousChoix) != 1) sousChoix = 0;

                    switch (sousChoix) {
                        case 1:
                            afficherLivres(livres, nbLivres);
                            break;
                        case 2:
                            ajouterLivre(livres, &nbLivres);
                            break;
                        case 0:
                            printf("Retour au menu principal...\n");
                            break;
                        default:
                            printf("Choix invalide.\n");
                    }
                } while (sousChoix != 0);
                break;
            }

            case 2:
                afficherUtilisateurs(utilisateurs, nbUsers);
                break;

            case 3:
                verifierRetards(emprunts, nbEmprunts);
                break;

            case 4:
                afficherStatistiques(emprunts, nbEmprunts, utilisateurs, nbUsers, livres, nbLivres);
                break;

            case 0:
                printf("Sauvegarde et fermeture...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    // Sauvegarde à la fermeture
    sauvegarderLivres(livres, nbLivres);
    sauvegarderUtilisateurs(utilisateurs, nbUsers);
    sauvegarderEmprunts(emprunts, nbEmprunts);

    return 0;
}
