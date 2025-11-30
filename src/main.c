//
// Created by Marie Viricel on 06/11/2025.
//

//
// Created by Marie Viricel on 06/11/2025.
//

#include <stdio.h>
#include "raylib.h"

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"
#include "fichiers.h"
#include "stats.h"

// ---------------------------------------------------------
// Déclaration du menu console dans une fonction séparée
// ---------------------------------------------------------
void lancerMenuConsole() {

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
        printf("\n=== MENU BIBLIOTHÈQUE ===\n");
        printf("1. Gestion des livres\n");
        printf("2. Gestion des utilisateurs\n");
        printf("3. Gestion des emprunts\n");
        printf("4. Statistiques\n");
        printf("5. Ouvrir interface graphique\n");
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
                        case 1: afficherLivres(livres, nbLivres); break;
                        case 2: ajouterLivre(livres, &nbLivres); break;
                        case 0: break;
                        default: printf("Choix invalide.\n");
                    }
                } while (sousChoix != 0);
                break;
            }

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

                    int c; while ((c = getchar()) != '\n' && c != EOF) {} // vide buffer

                    switch (sous) {
                        case 1: afficherUtilisateurs(utilisateurs, nbUsers); break;
                        case 2: ajouterUtilisateur(utilisateurs, &nbUsers); break;
                        case 3: {
                            int id;
                            printf("ID à supprimer : ");
                            if (scanf("%d", &id) == 1)
                                supprimerUtilisateur(utilisateurs, &nbUsers, id);
                            break;
                        }
                        case 0: break;
                        default: printf("Choix invalide.\n");
                    }
                } while (sous != 0);
                break;
            }

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

                    int c; while ((c = getchar()) != '\n' && c != EOF) {}

                    switch (sous) {
                        case 1:
                            emprunterLivre(livres, nbLivres,
                                           utilisateurs, nbUsers,
                                           emprunts, &nbEmprunts);
                            break;
                        case 2: {
                            int idLivre;
                            printf("ID du livre à retourner : ");
                            if (scanf("%d", &idLivre) == 1)
                                retournerLivre(emprunts, &nbEmprunts, idLivre);
                            break;
                        }
                        case 3: verifierRetards(emprunts, nbEmprunts); break;
                        case 0: break;
                        default: printf("Choix invalide.\n");
                    }
                } while (sous != 0);
                break;
            }

            case 4:
                afficherStatistiques(emprunts, nbEmprunts,
                                     utilisateurs, nbUsers,
                                     livres, nbLivres);
                break;

            case 0:
                printf("Sauvegarde et fermeture...\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    sauvegarderLivres(livres, nbLivres);
    sauvegarderUtilisateurs(utilisateurs, nbUsers);
    sauvegarderEmprunts(emprunts, nbEmprunts);
}



// ---------------------------------------------------------
// FONCTION PRINCIPALE RAYLIB + MENU
// ---------------------------------------------------------
int main(void)
{
    // === 1) Fenêtre Raylib ===
    InitWindow(800, 450, "Interface graphique - Raylib");
    SetTargetFPS(60);

    // === 2) Boucle Raylib ===
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Raylib fonctionne !", 200, 200, 20, BLACK);
        DrawText("Appuie sur ENTER pour lancer le menu console", 150, 260, 18, DARKGRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) {
            CloseWindow();     // fermer Raylib avant la console
            lancerMenuConsole();
            return 0;
        }
    }

    CloseWindow();
    return 0;
}

