//
// Created by Marie Viricel on 06/11/2025.
//

//
// main.c
// Bibliothèque - Interface graphique
//

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"
#include "fichiers.h"
#include "stats.h"

#define MAX_LIVRES 100
#define MAX_USERS 100
#define MAX_EMPRUNTS 100

// Buffers pour la saisie
char titreInput[100] = "";
char auteurInput[100] = "";
char categorieInput[50] = "";
char isbnInput[20] = "";
char anneeBuf[10] = "";
int anneeInput = 0;
char livreASupprimerBuf[10] = "";
char userASupprimerBuf[10] = "";
char nomInput[50] = "";
char prenomInput[50] = "";
char emailInput[100] = "";

// Bool pour savoir si le textbox est actif
bool titreEdit = false;
bool auteurEdit = false;
bool categorieEdit = false;
bool isbnEdit = false;
bool anneeEdit = false;
bool nomEdit = false, prenomEdit = false, emailEdit = false;

typedef enum {
    MENU,
    LIVRES,
    AJOUT_LIVRE,
    SUPPR_LIVRE,
    USERS,
    AJOUT_USER,
    SUPPR_USER,
    EMPRUNTS,
    STATS
} Mode;

int main(void)
{
    // ========= Données en mémoire =========
    Livre livres[MAX_LIVRES];
    Utilisateur utilisateurs[MAX_USERS];
    Emprunt emprunts[MAX_EMPRUNTS];

    int nbLivres = 0, nbUsers = 0, nbEmprunts = 0;

    chargerLivres(livres, &nbLivres);
    chargerUtilisateurs(utilisateurs, &nbUsers);
    chargerEmprunts(emprunts, &nbEmprunts);

    // ========= Fenêtre Raylib =========
    InitWindow(900, 600, "Bibliotheque - Interface Graphique");
    SetTargetFPS(60);

    Mode mode = MENU;

    // ========= TextBox / Inputs =========
    char titreInput[100] = "", auteurInput[50] = "", categorieInput[50] = "", isbnInput[20] = "";
    int anneeInput = 0;
    bool titreEdit = false, auteurEdit = false, categorieEdit = false, isbnEdit = false;
    int livreASupprimer = 0;

    char userInput[100] = "";
    bool userEdit = false;
    int userASupprimer = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ================= MENU PRINCIPAL =================
        if (mode == MENU)
        {
            DrawText("MENU PRINCIPAL", 300, 30, 30, DARKGRAY);

            if (GuiButton((Rectangle){300, 120, 300, 50}, "Gerer les livres")) mode = LIVRES;
            if (GuiButton((Rectangle){300, 190, 300, 50}, "Gerer les utilisateurs")) mode = USERS;
            if (GuiButton((Rectangle){300, 260, 300, 50}, "Gerer les emprunts")) mode = EMPRUNTS;
            if (GuiButton((Rectangle){300, 330, 300, 50}, "Statistiques")) mode = STATS;
            if (GuiButton((Rectangle){300, 400, 300, 50}, "Quitter")) break;
        }

        // ===================== LIVRES =====================
        else if (mode == LIVRES)
        {
            DrawText("Liste des livres :", 50, 20, 25, DARKGRAY);

            for (int i = 0; i < nbLivres; i++)
            {
                char buffer[200];
                snprintf(buffer, sizeof(buffer), "%d - %s", livres[i].id, livres[i].titre);
                DrawText(buffer, 50, 70 + i * 25, 20, BLACK);
            }

            if (GuiButton((Rectangle){600, 70, 250, 40}, "Ajouter un livre")) mode = AJOUT_LIVRE;
            if (GuiButton((Rectangle){600, 120, 250, 40}, "Supprimer un livre")) mode = SUPPR_LIVRE;
            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu")) mode = MENU;
        }

        // ================ AJOUT D’UN LIVRE ====================
        else if (mode == AJOUT_LIVRE)
        {
            DrawText("Ajouter un livre", 50, 30, 25, DARKGRAY);

            DrawText("Titre :", 50, 120, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 110, 500, 40}, titreInput, sizeof(titreInput), titreEdit))
                titreEdit = !titreEdit;

            DrawText("Auteur :", 50, 170, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 160, 500, 40}, auteurInput, sizeof(auteurInput), auteurEdit))
                auteurEdit = !auteurEdit;

            DrawText("Catégorie :", 50, 220, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 210, 300, 40}, categorieInput, sizeof(categorieInput), categorieEdit))
                categorieEdit = !categorieEdit;

            DrawText("ISBN :", 50, 270, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 260, 200, 40}, isbnInput, sizeof(isbnInput), isbnEdit))
                isbnEdit = !isbnEdit;

            DrawText("Année :", 50, 320, 20, BLACK);
            // GuiTextBox prend un buffer char[], pas un int
            if (GuiTextBox((Rectangle){140, 310, 100, 40}, anneeBuf, sizeof(anneeBuf), anneeEdit))
                anneeEdit = !anneeEdit;

            if (GuiButton((Rectangle){140, 380, 200, 40}, "Valider"))
            {
                Livre nouveau;
                strcpy(nouveau.titre, titreInput);
                strcpy(nouveau.auteur, auteurInput);
                strcpy(nouveau.categorie, categorieInput);
                strcpy(nouveau.isbn, isbnInput);

                // Conversion du buffer en int
                nouveau.annee = atoi(anneeBuf);

                ajouterLivreGui(livres, &nbLivres, nouveau);

                // Reset des champs
                titreInput[0] = auteurInput[0] = categorieInput[0] = isbnInput[0] = '\0';
                anneeBuf[0] = '\0';

                mode = LIVRES;
            }

            if (GuiButton((Rectangle){140, 440, 200, 40}, "Annuler"))
            {
                titreInput[0] = auteurInput[0] = categorieInput[0] = isbnInput[0] = '\0';
                anneeBuf[0] = '\0';
                anneeInput = 0;
                mode = LIVRES;
            }
        }

        // ================ SUPPRESSION LIVRE ==================
        else if (mode == SUPPR_LIVRE)
        {
            DrawText("Supprimer un livre", 50, 30, 25, DARKGRAY);
            DrawText("ID du livre à supprimer :", 50, 120, 20, BLACK);

            if (GuiTextBox((Rectangle){250, 110, 100, 40}, livreASupprimerBuf, sizeof(livreASupprimerBuf), true))
            {
                // Rien à faire ici, le buffer est mis à jour automatiquement
            }

            if (GuiButton((Rectangle){140, 180, 200, 40}, "Supprimer"))
            {
                int id = atoi(livreASupprimerBuf);
                supprimerLivre(livres, &nbLivres, id);
                livreASupprimerBuf[0] = '\0';  // Reset champ
                mode = LIVRES;
            }

            if (GuiButton((Rectangle){140, 240, 200, 40}, "Annuler"))
            {
                livreASupprimerBuf[0] = '\0';
                mode = LIVRES;
            }
        }


        // ===================== UTILISATEURS =====================
        else if (mode == USERS)
        {
            DrawText("Utilisateurs :", 50, 20, 25, DARKGRAY);

            for (int i = 0; i < nbUsers; i++)
            {
                char buffer[200];
                snprintf(buffer, sizeof(buffer), "%d - %s", utilisateurs[i].id, utilisateurs[i].nom);
                DrawText(buffer, 50, 70 + i * 25, 20, BLACK);
            }

            if (GuiButton((Rectangle){600, 70, 250, 40}, "Ajouter utilisateur")) mode = AJOUT_USER;
            if (GuiButton((Rectangle){600, 120, 250, 40}, "Supprimer utilisateur")) mode = SUPPR_USER;
            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu")) mode = MENU;
        }

        // ================ AJOUT UTILISATEUR ====================
        else if (mode == AJOUT_USER)
        {
            DrawText("Ajouter un utilisateur", 50, 30, 25, DARKGRAY);

            DrawText("Nom :", 50, 120, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 110, 500, 40}, nomInput, 50, nomEdit))
                nomEdit = !nomEdit;

            DrawText("Prénom :", 50, 170, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 160, 500, 40}, prenomInput, 50, prenomEdit))
                prenomEdit = !prenomEdit;

            DrawText("Email :", 50, 220, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 210, 500, 40}, emailInput, 100, emailEdit))
                emailEdit = !emailEdit;

            if (GuiButton((Rectangle){140, 260, 200, 40}, "Valider"))
            {
                // Appel de la fonction manuelle avec tous les champs
                ajouterUtilisateurManuel(utilisateurs, &nbUsers,
                                         nomInput, prenomInput, emailInput, 0); // quota = 0

                // Réinitialiser les champs
                nomInput[0] = prenomInput[0] = emailInput[0] = '\0';
                mode = USERS;
            }

            if (GuiButton((Rectangle){140, 320, 200, 40}, "Annuler"))
            {
                nomInput[0] = prenomInput[0] = emailInput[0] = '\0';
                mode = USERS;
            }
        }

        // ================ SUPPRESSION UTILISATEUR ==================
        else if (mode == SUPPR_USER)
        {
            DrawText("Supprimer un utilisateur", 50, 30, 25, DARKGRAY);

            DrawText("ID utilisateur à supprimer :", 50, 120, 20, BLACK);

            // Zone de texte pour saisir l'ID
            if (GuiTextBox((Rectangle){250, 110, 100, 40}, userASupprimerBuf, sizeof(userASupprimerBuf), true))
            {
                // Rien à faire ici, le buffer est mis à jour automatiquement
            }

            if (GuiButton((Rectangle){140, 180, 200, 40}, "Supprimer"))
            {
                int id = atoi(userASupprimerBuf);
                supprimerUtilisateur(utilisateurs, &nbUsers, id);
                userASupprimerBuf[0] = '\0';  // Reset champ
                mode = USERS;
            }

            if (GuiButton((Rectangle){140, 240, 200, 40}, "Annuler"))
            {
                userASupprimerBuf[0] = '\0';
                mode = USERS;
            }
        }

        // ================ EMPRUNTS ====================
        else if (mode == EMPRUNTS)
        {
            DrawText("Gestion des emprunts", 50, 20, 25, DARKGRAY);

            char buffer[300];
            snprintf(buffer, sizeof(buffer), "Emprunts totaux : %d", nbEmprunts);
            DrawText(buffer, 50, 70, 20, BLACK);

            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu")) mode = MENU;
        }

        // ================ STATISTIQUES ====================
        else if (mode == STATS)
        {
            DrawText("Statistiques :", 50, 20, 25, DARKGRAY);

            char buffer[500];
            snprintf(buffer, sizeof(buffer),
                     "Livres : %d\nUtilisateurs : %d\nEmprunts : %d",
                     nbLivres, nbUsers, nbEmprunts);

            DrawText(buffer, 50, 70, 20, BLACK);

            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu")) mode = MENU;
        }

        EndDrawing();
    }

    // ========= Sauvegarde =========
    sauvegarderLivres(livres, nbLivres);
    sauvegarderUtilisateurs(utilisateurs, nbUsers);
    sauvegarderEmprunts(emprunts, nbEmprunts);

    CloseWindow();
    return 0;
}


