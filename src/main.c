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

// ==================== Buffers et flags pour saisie ====================
char titreInput[100] = "", auteurInput[100] = "", categorieInput[50] = "", isbnInput[20] = "", anneeBuf[10] = "";
int anneeInput = 0;
bool titreEdit = false, auteurEdit = false, categorieEdit = false, isbnEdit = false, anneeEdit = false;

char nomInput[50] = "", prenomInput[50] = "", emailInput[100] = "";
bool nomEdit = false, prenomEdit = false, emailEdit = false;

// ==================== Modes interface ====================
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
    // ========== Tableaux et compteurs ==========
    Livre livres[MAX_LIVRES];
    Utilisateur utilisateurs[MAX_USERS];
    Emprunt emprunts[MAX_EMPRUNTS];
    int nbLivres = 0, nbUsers = 0, nbEmprunts = 0;

    // ========== Chargement des fichiers ==========
    chargerLivres(livres, &nbLivres);
    chargerUtilisateurs(utilisateurs, &nbUsers);
    chargerEmprunts(emprunts, &nbEmprunts);

    // ========== Fenêtre Raylib ==========
    InitWindow(900, 600, "Bibliotheque - Interface Graphique");
    SetTargetFPS(60);

    Mode mode = MENU;

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

        // ===================== AJOUT LIVRE =====================
        else if (mode == AJOUT_LIVRE)
        {
            DrawText("Ajouter un livre", 50, 30, 25, DARKGRAY);

            DrawText("Titre :", 50, 120, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 110, 500, 40}, titreInput, sizeof(titreInput), titreEdit)) titreEdit = !titreEdit;

            DrawText("Auteur :", 50, 170, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 160, 500, 40}, auteurInput, sizeof(auteurInput), auteurEdit)) auteurEdit = !auteurEdit;

            DrawText("Categorie :", 50, 220, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 210, 300, 40}, categorieInput, sizeof(categorieInput), categorieEdit)) categorieEdit = !categorieEdit;

            DrawText("ISBN :", 50, 270, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 260, 200, 40}, isbnInput, sizeof(isbnInput), isbnEdit)) isbnEdit = !isbnEdit;

            DrawText("Annee :", 50, 320, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 310, 100, 40}, anneeBuf, sizeof(anneeBuf), anneeEdit)) anneeEdit = !anneeEdit;

            if (GuiButton((Rectangle){140, 380, 200, 40}, "Valider"))
            {
                Livre nouveau;
                strcpy(nouveau.titre, titreInput);
                strcpy(nouveau.auteur, auteurInput);
                strcpy(nouveau.categorie, categorieInput);
                strcpy(nouveau.isbn, isbnInput);
                nouveau.annee = atoi(anneeBuf);
                nouveau.id = nbLivres + 1;
                nouveau.disponible = 1;

                ajouterLivreGui(livres, &nbLivres, nouveau);

                titreInput[0] = auteurInput[0] = categorieInput[0] = isbnInput[0] = '\0';
                anneeBuf[0] = '\0';

                mode = LIVRES;
            }

            if (GuiButton((Rectangle){140, 440, 200, 40}, "Annuler"))
            {
                titreInput[0] = auteurInput[0] = categorieInput[0] = isbnInput[0] = '\0';
                anneeBuf[0] = '\0';
                mode = LIVRES;
            }
        }

        // ===================== USERS =====================
        else if (mode == USERS)
        {
            DrawText("Liste des utilisateurs :", 50, 20, 25, DARKGRAY);
            for (int i = 0; i < nbUsers; i++)
            {
                char buffer[200];
                snprintf(buffer, sizeof(buffer), "%d - %s %s", utilisateurs[i].id, utilisateurs[i].nom, utilisateurs[i].prenom);
                DrawText(buffer, 50, 70 + i * 25, 20, BLACK);
            }

            if (GuiButton((Rectangle){600, 70, 250, 40}, "Ajouter un utilisateur")) mode = AJOUT_USER;
            if (GuiButton((Rectangle){600, 120, 250, 40}, "Supprimer un utilisateur")) mode = SUPPR_USER;
            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu")) mode = MENU;
        }

        // ===================== AJOUT USER =====================
        else if (mode == AJOUT_USER)
        {
            DrawText("Ajouter un utilisateur", 50, 30, 25, DARKGRAY);

            DrawText("Nom :", 50, 120, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 110, 500, 40}, nomInput, sizeof(nomInput), nomEdit)) nomEdit = !nomEdit;

            DrawText("Prenom :", 50, 170, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 160, 500, 40}, prenomInput, sizeof(prenomInput), prenomEdit)) prenomEdit = !prenomEdit;

            DrawText("Email :", 50, 220, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 210, 500, 40}, emailInput, sizeof(emailInput), emailEdit)) emailEdit = !emailEdit;

            if (GuiButton((Rectangle){140, 280, 200, 40}, "Valider"))
            {
                Utilisateur nouveau;
                nouveau.id = nbUsers + 1;
                strcpy(nouveau.nom, nomInput);
                strcpy(nouveau.prenom, prenomInput);
                strcpy(nouveau.email, emailInput);
                nouveau.quota = 0;

                ajouterUtilisateurManuel(utilisateurs, &nbUsers, nouveau.nom, nouveau.prenom, nouveau.email, nouveau.quota);

                nomInput[0] = prenomInput[0] = emailInput[0] = '\0';
                mode = USERS;
            }

            if (GuiButton((Rectangle){140, 340, 200, 40}, "Annuler"))
            {
                nomInput[0] = prenomInput[0] = emailInput[0] = '\0';
                mode = USERS;
            }
        }

        EndDrawing();
    }

    // ========== Sauvegarde ==========
    sauvegarderLivres(livres, nbLivres);
    sauvegarderUtilisateurs(utilisateurs, nbUsers);
    sauvegarderEmprunts(emprunts, nbEmprunts);

    CloseWindow();
    return 0;
}



