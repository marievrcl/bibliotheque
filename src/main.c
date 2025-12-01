#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <stdio.h>
#include <string.h>

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"
#include "fichiers.h"
#include "stats.h"

#define MAX_LIVRES 100
#define MAX_USERS 100
#define MAX_EMPRUNTS 100

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
    // ========= Données mémoire =========
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

    // ========= TextBox Ajout Livre =========
    char titreInput[100] = "";
    bool titreEdit = false;
    int livreASupprimer = 0;

    // ========= TextBox Ajout Utilisateur =========
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

            if (GuiButton((Rectangle){600, 70, 250, 40}, "Ajouter un livre"))
                mode = AJOUT_LIVRE;

            if (GuiButton((Rectangle){600, 120, 250, 40}, "Supprimer un livre"))
                mode = SUPPR_LIVRE;

            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu"))
                mode = MENU;
        }

        // ================ AJOUT D’UN LIVRE ====================
        else if (mode == AJOUT_LIVRE)
        {
            DrawText("Ajouter un livre", 50, 30, 25, DARKGRAY);

            DrawText("Titre :", 50, 120, 20, BLACK);

            if (GuiTextBox((Rectangle){140, 110, 500, 40}, titreInput, 100, titreEdit))
                titreEdit = !titreEdit;

            if (GuiButton((Rectangle){140, 180, 200, 40}, "Valider"))
            {
                Livre aRajouter={-1,"","","","",1970,1};
                strcpy(aRajouter.titre, titreInput);
                ajouterLivreGui(livres, &nbLivres, aRajouter);
                titreInput[0] = '\0';
                mode = LIVRES;
            }

            if (GuiButton((Rectangle){140, 240, 200, 40}, "Annuler"))
            {
                titreInput[0] = '\0';
                mode = LIVRES;
            }
        }

        // ================ SUPPRESSION LIVRE ==================
        else if (mode == SUPPR_LIVRE)
        {
            DrawText("Supprimer un livre", 50, 30, 25, DARKGRAY);

            DrawText("ID du livre à supprimer :", 50, 120, 20, BLACK);

            char buf[10];
            sprintf(buf, "%d", livreASupprimer);
            if (GuiTextBox((Rectangle){250, 110, 100, 40}, buf, 10, true))
                livreASupprimer = atoi(buf);

            if (GuiButton((Rectangle){140, 180, 200, 40}, "Supprimer"))
            {

                supprimerLivre(livres, &nbLivres, livreASupprimer);
                livreASupprimer = 0;
                mode = LIVRES;
            }

            if (GuiButton((Rectangle){140, 240, 200, 40}, "Annuler"))
                mode = LIVRES;
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

            if (GuiButton((Rectangle){600, 70, 250, 40}, "Ajouter utilisateur"))
                mode = AJOUT_USER;

            if (GuiButton((Rectangle){600, 120, 250, 40}, "Supprimer utilisateur"))
                mode = SUPPR_USER;

            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu"))
                mode = MENU;
        }

        // ================ AJOUT UTILISATEUR ====================
        else if (mode == AJOUT_USER)
        {
            DrawText("Ajouter un utilisateur", 50, 30, 25, DARKGRAY);

            DrawText("Nom :", 50, 120, 20, BLACK);

            if (GuiTextBox((Rectangle){140, 110, 500, 40}, userInput, 100, userEdit))
                userEdit = !userEdit;

            if (GuiButton((Rectangle){140, 180, 200, 40}, "Valider"))
            {


                //ajouterUtilisateurManuel(utilisateurs, &nbUsers, aRajouter);
                userInput[0] = '\0';
                mode = USERS;
            }

            if (GuiButton((Rectangle){140, 240, 200, 40}, "Annuler"))
            {
                userInput[0] = '\0';
                mode = USERS;
            }
        }

        // ================ SUPPRESSION UTILISATEUR ==================
        else if (mode == SUPPR_USER)
        {
            DrawText("Supprimer un utilisateur", 50, 30, 25, DARKGRAY);

            DrawText("ID utilisateur à supprimer :", 50, 120, 20, BLACK);

            char buf[10];
            sprintf(buf, "%d", userASupprimer);
            if (GuiTextBox((Rectangle){250, 110, 100, 40}, buf, 10, true))
                userASupprimer = atoi(buf);

            if (GuiButton((Rectangle){140, 180, 200, 40}, "Supprimer"))
            {
                supprimerUtilisateur(utilisateurs, &nbUsers, userASupprimer);
                userASupprimer = 0;
                mode = USERS;
            }

            if (GuiButton((Rectangle){140, 240, 200, 40}, "Annuler"))
                mode = USERS;
        }

        // ================ EMPRUNTS ====================
        else if (mode == EMPRUNTS)
        {
            DrawText("Gestion des emprunts", 50, 20, 25, DARKGRAY);

            char buffer[300];
            snprintf(buffer, sizeof(buffer), "Emprunts totaux : %d", nbEmprunts);
            DrawText(buffer, 50, 70, 20, BLACK);

            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu"))
                mode = MENU;
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

            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu"))
                mode = MENU;
        }

        EndDrawing();
    }

    sauvegarderLivres(livres, nbLivres);
    sauvegarderUtilisateurs(utilisateurs, nbUsers);
    sauvegarderEmprunts(emprunts, nbEmprunts);
    CloseWindow();
    return 0;
}