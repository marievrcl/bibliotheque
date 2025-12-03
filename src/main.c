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

// Buffers pour la saisie des informations des livres
char titreInput[100] = "";        // Buffer pour le titre d’un livre
char auteurInput[100] = "";       // Buffer pour le nom de l’auteur
char categorieInput[50] = "";     // Buffer pour la catégorie du livre
char isbnInput[20] = "";          // Buffer pour le code ISBN
char anneeBuf[10] = "";           // Buffer pour l’année en texte
int anneeInput = 0;               // Variable pour l’année convertie en entier

// Buffers pour la suppression par ID
char livreASupprimerBuf[10] = ""; // Buffer pour saisir l’ID du livre à supprimer
char userASupprimerBuf[10] = "";  // Buffer pour saisir l’ID de l’utilisateur à supprimer

// Buffers pour la saisie des utilisateurs
char nomInput[50] = "";           // Buffer pour le nom de l’utilisateur
char prenomInput[50] = "";        // Buffer pour le prénom de l’utilisateur
char emailInput[100] = "";        // Buffer pour l’email de l’utilisateur

// Booléens pour savoir si un textbox est actif
bool titreEdit = false;           // État du textbox pour le titre
bool auteurEdit = false;          // État du textbox pour l’auteur
bool categorieEdit = false;       // État du textbox pour la catégorie
bool isbnEdit = false;            // État du textbox pour l’ISBN
bool anneeEdit = false;           // État du textbox pour l’année
bool nomEdit = false;             // État du textbox pour le nom utilisateur
bool prenomEdit = false;          // État du textbox pour le prénom utilisateur
bool emailEdit = false;           // État du textbox pour l’email utilisateur

// Définition des modes de l’interface graphique
typedef enum {
    MENU,           // Mode menu principal
    LIVRES,         // Mode affichage des livres
    AJOUT_LIVRE,    // Mode ajout d’un livre
    SUPPR_LIVRE,    // Mode suppression d’un livre
    USERS,          // Mode affichage des utilisateurs
    AJOUT_USER,     // Mode ajout d’un utilisateur
    SUPPR_USER,     // Mode suppression d’un utilisateur
    EMPRUNTS,       // Mode gestion des emprunts
    STATS           // Mode affichage des statistiques
} Mode;

int main(void)  // Fonction principale
{
    // ========= Déclaration des tableaux de données =========
    Livre livres[MAX_LIVRES];               // Tableau pour stocker les livres
    Utilisateur utilisateurs[MAX_USERS];    // Tableau pour stocker les utilisateurs
    Emprunt emprunts[MAX_EMPRUNTS];         // Tableau pour stocker les emprunts

    // Compteurs des éléments dans chaque tableau
    int nbLivres = 0, nbUsers = 0, nbEmprunts = 0;

    // ========= Chargement des données depuis les fichiers =========
    chargerLivres(livres, &nbLivres);               // Charger les livres depuis "data/livres.txt"
    chargerUtilisateurs(utilisateurs, &nbUsers);   // Charger les utilisateurs depuis "data/utilisateurs.txt"
    chargerEmprunts(emprunts, &nbEmprunts);        // Charger les emprunts depuis "data/emprunts.txt"

    // ========= Initialisation de la fenêtre Raylib =========
    InitWindow(900, 600, "Bibliotheque - Interface Graphique"); // Crée une fenêtre 900x600 px
    SetTargetFPS(60);                                         // Limite le rendu à 60 images par seconde

    Mode mode = MENU; // Mode initial : menu principal

    // ========= Boucle principale =========
    while (!WindowShouldClose())  // Tant que l’utilisateur n’a pas fermé la fenêtre
    {
        BeginDrawing();            // Commence le dessin de la frame
        ClearBackground(RAYWHITE); // Fond blanc

        // ================= MENU PRINCIPAL =================
        if (mode == MENU)
        {
            DrawText("MENU PRINCIPAL", 300, 30, 30, DARKGRAY); // Affiche le titre du menu

            // Boutons principaux du menu
            if (GuiButton((Rectangle){300, 120, 300, 50}, "Gerer les livres")) mode = LIVRES;
            if (GuiButton((Rectangle){300, 190, 300, 50}, "Gerer les utilisateurs")) mode = USERS;
            if (GuiButton((Rectangle){300, 260, 300, 50}, "Gerer les emprunts")) mode = EMPRUNTS;
            if (GuiButton((Rectangle){300, 330, 300, 50}, "Statistiques")) mode = STATS;
            if (GuiButton((Rectangle){300, 400, 300, 50}, "Quitter")) break; // Quitte la boucle principale
        }

        // ===================== LIVRES =====================
        else if (mode == LIVRES)
        {
            DrawText("Liste des livres :", 50, 20, 25, DARKGRAY); // Titre section livres

            // Boucle d’affichage de tous les livres
            for (int i = 0; i < nbLivres; i++)
            {
                char buffer[200]; // Buffer temporaire pour afficher ID + titre
                snprintf(buffer, sizeof(buffer), "%d - %s", livres[i].id, livres[i].titre); // Formatte la chaîne
                DrawText(buffer, 50, 70 + i * 25, 20, BLACK); // Affiche le livre à la position correspondante
            }

            // Boutons d’actions
            if (GuiButton((Rectangle){600, 70, 250, 40}, "Ajouter un livre")) mode = AJOUT_LIVRE;
            if (GuiButton((Rectangle){600, 120, 250, 40}, "Supprimer un livre")) mode = SUPPR_LIVRE;
            if (GuiButton((Rectangle){600, 500, 250, 40}, "Retour menu")) mode = MENU;
        }

        // ================ AJOUT D’UN LIVRE ====================
        else if (mode == AJOUT_LIVRE)
        {
            DrawText("Ajouter un livre", 50, 30, 25, DARKGRAY); // Titre page ajout

            // ==== TextBox Titre ====
            DrawText("Titre :", 50, 120, 20, BLACK); // Label
            if (GuiTextBox((Rectangle){140, 110, 500, 40}, titreInput, sizeof(titreInput), titreEdit))
                titreEdit = !titreEdit; // Alterne l’état actif/inactif du textbox

            // ==== TextBox Auteur ====
            DrawText("Auteur :", 50, 170, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 160, 500, 40}, auteurInput, sizeof(auteurInput), auteurEdit))
                auteurEdit = !auteurEdit;

            // ==== TextBox Catégorie ====
            DrawText("Catégorie :", 50, 220, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 210, 300, 40}, categorieInput, sizeof(categorieInput), categorieEdit))
                categorieEdit = !categorieEdit;

            // ==== TextBox ISBN ====
            DrawText("ISBN :", 50, 270, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 260, 200, 40}, isbnInput, sizeof(isbnInput), isbnEdit))
                isbnEdit = !isbnEdit;

            // ==== TextBox Année ====
            DrawText("Année :", 50, 320, 20, BLACK);
            if (GuiTextBox((Rectangle){140, 310, 100, 40}, anneeBuf, sizeof(anneeBuf), anneeEdit))
                anneeEdit = !anneeEdit;

            // Bouton Valider
            if (GuiButton((Rectangle){140, 380, 200, 40}, "Valider"))
            {
                Livre nouveau; // Création d’un nouveau livre
                strcpy(nouveau.titre, titreInput); // Copie titre
                strcpy(nouveau.auteur, auteurInput); // Copie auteur
                strcpy(nouveau.categorie, categorieInput); // Copie catégorie
                strcpy(nouveau.isbn, isbnInput); // Copie ISBN
                nouveau.annee = atoi(anneeBuf); // Conversion année string -> int

                ajouterLivreGui(livres, &nbLivres, nouveau); // Ajout du livre dans le tableau

                // Réinitialisation des champs
                titreInput[0] = auteurInput[0] = categorieInput[0] = isbnInput[0] = '\0';
                anneeBuf[0] = '\0';

                mode = LIVRES; // Retour à la liste des livres
            }

            // Bouton Annuler
            if (GuiButton((Rectangle){140, 440, 200, 40}, "Annuler"))
            {
                titreInput[0] = auteurInput[0] = categorieInput[0] = isbnInput[0] = '\0';
                anneeBuf[0] = '\0';
                anneeInput = 0;
                mode = LIVRES; // Retour à la liste
            }
        }

        EndDrawing(); // Fin du dessin de la frame
    }

    // ========= Sauvegarde des données =========
    sauvegarderLivres(livres, nbLivres);             // Sauvegarde livres
    sauvegarderUtilisateurs(utilisateurs, nbUsers); // Sauvegarde utilisateurs
    sauvegarderEmprunts(emprunts, nbEmprunts);      // Sauvegarde emprunts

    CloseWindow(); // Fermeture de la fenêtre
    return 0;      // Fin du programme
}



