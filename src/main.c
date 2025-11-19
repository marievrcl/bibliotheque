//
// Created by Marie Viricel on 06/11/2025.
//

#include <stdio.h>
#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"
#include "fichiers.h"
#include "stats.h"

int main(void) {
    // Tableaux statiques pour stocker les données en mémoire
    Livre livres[100];
    Utilisateur utilisateurs[100];
    Emprunt emprunts[100];

    int nbLivres = 0, nbUsers = 0, nbEmprunts = 0;

    // ========= CHARGEMENT DES DONNÉES =========
    chargerLivres(livres, &nbLivres);
    chargerUtilisateurs(utilisateurs, &nbUsers);
    chargerEmprunts(emprunts, &nbEmprunts);

    int choix;
    do {
        // ========= MENU PRINCIPAL =========
        printf("\n=== MENU BIBLIOTHÈQUE ===\n");
        printf("1. Gestion des livres\n");
        printf("2. Gestion des utilisateurs\n");
        printf("3. Gestion des emprunts\n");
        printf("4. Statistiques\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        if (scanf("%d", &choix) != 1) choix = 0;

        switch (choix) {

            // ---------- MENU LIVRES ----------
            case 1: {
                int sousChoix;
                do {
                    printf("\n--- GESTION DES LIVRES ---\n");
                    printf("1. Afficher les livres\n");
                    printf("2. Ajouter un livre\n");
                    // Tu pourras rajouter ici : modifier, supprimer, trier...
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

            // ---------- MENU UTILISATEURS ----------
            case 2: {
                int sous;
                do {
                    printf("\n--- GESTION DES UTILISATEURS ---\n");
                    printf("1. Afficher les utilisateurs\n");
                    printf("2. Ajouter un utilisateur\n");
                    printf("3. Supprimer un utilisateur\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if (scanf("%d", &sous) != 1) sous = 0;
                    int c; while ((c = getchar()) != '\n' && c != EOF) {} // vide le buffer

                    switch (sous) {
                        case 1:
                            afficherUtilisateurs(utilisateurs, nbUsers);
                            break;
                        case 2:
                            ajouterUtilisateur(utilisateurs, &nbUsers);
                            break;
                        case 3: {
                            int id;
                            printf("ID à supprimer : ");
                            if (scanf("%d", &id) != 1) {
                                while ((c = getchar()) != '\n' && c != EOF) {}
                                break;
                            }
                            while ((c = getchar()) != '\n' && c != EOF) {}
                            supprimerUtilisateur(utilisateurs, &nbUsers, id);
                            break;
                        }
                        case 0:
                            printf("Retour au menu principal...\n");
                            break;
                        default:
                            printf("Choix invalide.\n");
                    }
                } while (sous != 0);
                break;
            }

            // ---------- MENU EMPRUNTS ----------
            case 3: {
                int sous;
                do {
                    printf("\n--- GESTION DES EMPRUNTS ---\n");
                    printf("1. Emprunter un livre\n");
                    printf("2. Retourner un livre\n");
                    printf("3. Vérifier les retards (>15j)\n");
                    printf("0. Retour\n");
                    printf("Choix : ");
                    if (scanf("%d", &sous) != 1) sous = 0;
                    int c; while ((c = getchar()) != '\n' && c != EOF) {} // clearInput

                    switch (sous) {
                        case 1:
                            emprunterLivre(livres, nbLivres,
                                           utilisateurs, nbUsers,
                                           emprunts, &nbEmprunts);
                            break;
                        case 2: {
                            int idLivre;
                            printf("ID du livre à retourner : ");
                            if (scanf("%d", &idLivre) != 1) {
                                while ((c = getchar()) != '\n' && c != EOF) {}
                                break;
                            }
                            while ((c = getchar()) != '\n' && c != EOF) {}
                            retournerLivre(emprunts, &nbEmprunts, idLivre);

                            // Remise en dispo du livre + quota utilisateur
                            // Tu peux ajouter cette logique ici ou dans emprunts.c selon ton choix de conception.
                            break;
                        }
                        case 3:
                            verifierRetards(emprunts, nbEmprunts);
                            break;
                        case 0:
                            printf("Retour au menu principal...\n");
                            break;
                        default:
                            printf("Choix invalide.\n");
                    }
                } while (sous != 0);
                break;
            }

            // ---------- STATISTIQUES ----------
            case 4:
                afficherStatistiques(emprunts, nbEmprunts,
                                     utilisateurs, nbUsers,
                                     livres, nbLivres);
                break;

            // ---------- QUITTER ----------
            case 0:
                printf("Sauvegarde et fermeture...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    // ========= SAUVEGARDE AVANT QUITTER =========
    sauvegarderLivres(livres, nbLivres);
    sauvegarderUtilisateurs(utilisateurs, nbUsers);
    sauvegarderEmprunts(emprunts, nbEmprunts);

    return 0;
}
