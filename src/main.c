
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

// ======= Buffers pour livres =======
char titreInput[100]="", auteurInput[100]="", categorieInput[50]="", isbnInput[20]="", anneeBuf[10]="";
bool titreEdit=false, auteurEdit=false, categorieEdit=false, isbnEdit=false, anneeEdit=false;
char livreASupprimerBuf[10]="";

// ======= Buffers pour utilisateurs =======
char nomInput[50]="", prenomInput[50]="", emailInput[100]="";
bool nomEdit=false, prenomEdit=false, emailEdit=false;
char userASupprimerBuf[10]="";

// ======= Buffers pour emprunts =======
char empruntISBN[20]="";      // ISBN du livre à emprunter ou rendre
int empruntIdUser=0;          // ID de l'utilisateur
char dateEmpruntBuf[12]="";   // Date du jour pour l'emprunt
char dateRetourBuf[12]="";    // Date retour pour le retour

// ======= Modes =======
typedef enum {
    MENU, LIVRES, AJOUT_LIVRE, SUPPR_LIVRE,
    USERS, AJOUT_USER, SUPPR_USER,
    EMPRUNTS, AJOUT_EMPRUNT, RETOUR_EMPRUNT,
    STATS
} Mode;

int main(void)
{
    // ======= Données =======
    Livre livres[MAX_LIVRES];
    Utilisateur utilisateurs[MAX_USERS];
    Emprunt emprunts[MAX_EMPRUNTS];
    int nbLivres=0, nbUsers=0, nbEmprunts=0;

    chargerLivres(livres,&nbLivres);
    chargerUtilisateurs(utilisateurs,&nbUsers);
    chargerEmprunts(emprunts,&nbEmprunts);

    InitWindow(900,600,"Bibliotheque - Interface Graphique");
    SetTargetFPS(60);

    Mode mode = MENU;

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ================== MENU ==================
        if(mode==MENU)
        {
            DrawText("MENU PRINCIPAL",300,30,30,DARKGRAY);
            if(GuiButton((Rectangle){300,120,300,50},"Gerer les livres")) mode=LIVRES;
            if(GuiButton((Rectangle){300,190,300,50},"Gerer les utilisateurs")) mode=USERS;
            if(GuiButton((Rectangle){300,260,300,50},"Gerer les emprunts")) mode=EMPRUNTS;
            if(GuiButton((Rectangle){300,330,300,50},"Statistiques")) mode=STATS;
            if(GuiButton((Rectangle){300,400,300,50},"Quitter")) break;
        }

        // ================== LIVRES ==================
        else if(mode==LIVRES)
        {
            DrawText("Liste des livres :",50,20,25,DARKGRAY);
            for(int i=0;i<nbLivres;i++)
            {
                char buf[200];
                snprintf(buf,sizeof(buf),"%d - %s",livres[i].id,livres[i].titre);
                DrawText(buf,50,70+i*25,20,BLACK);
            }
            if(GuiButton((Rectangle){600,70,250,40},"Ajouter un livre")) mode=AJOUT_LIVRE;
            if(GuiButton((Rectangle){600,120,250,40},"Supprimer un livre")) mode=SUPPR_LIVRE;
            if(GuiButton((Rectangle){600,500,250,40},"Retour menu")) mode=MENU;
        }

        // ================== AJOUT LIVRE ==================
        else if (mode == AJOUT_LIVRE)
{
    DrawText("Ajouter un livre", 50, 30, 25, DARKGRAY);

    Rectangle rTitre     = (Rectangle){140,110,500,40};
    Rectangle rAuteur    = (Rectangle){140,160,500,40};
    Rectangle rCategorie = (Rectangle){140,210,300,40};
    Rectangle rISBN      = (Rectangle){140,260,200,40};
    Rectangle rAnnee     = (Rectangle){140,310,100,40};

    // Gestion du toggle d’édition
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 m = GetMousePosition();
        titreEdit     = CheckCollisionPointRec(m, rTitre);
        auteurEdit    = CheckCollisionPointRec(m, rAuteur);
        categorieEdit = CheckCollisionPointRec(m, rCategorie);
        isbnEdit      = CheckCollisionPointRec(m, rISBN);
        anneeEdit     = CheckCollisionPointRec(m, rAnnee);
    }

    DrawText("Titre :", 50, 120, 20, BLACK);
    GuiTextBox(rTitre, titreInput, sizeof(titreInput)-1, titreEdit);

    DrawText("Auteur :", 50, 170, 20, BLACK);
    GuiTextBox(rAuteur, auteurInput, sizeof(auteurInput)-1, auteurEdit);

    DrawText("Catégorie :", 50, 220, 20, BLACK);
    GuiTextBox(rCategorie, categorieInput, sizeof(categorieInput)-1, categorieEdit);

    DrawText("ISBN :", 50, 270, 20, BLACK);
    GuiTextBox(rISBN, isbnInput, sizeof(isbnInput)-1, isbnEdit);

    DrawText("Année :", 50, 320, 20, BLACK);
    GuiTextBox(rAnnee, anneeBuf, sizeof(anneeBuf)-1, anneeEdit);

    if (GuiButton((Rectangle){140,380,200,40}, "Valider"))
    {
        Livre L;
        strcpy(L.titre, titreInput);
        strcpy(L.auteur, auteurInput);
        strcpy(L.categorie, categorieInput);
        strcpy(L.isbn, isbnInput);
        L.annee = atoi(anneeBuf);

        ajouterLivreGui(livres, &nbLivres, L);

        titreInput[0]=auteurInput[0]=categorieInput[0]=isbnInput[0]=anneeBuf[0]=0;
        titreEdit=auteurEdit=categorieEdit=isbnEdit=anneeEdit=false;

        mode = LIVRES;
    }

    if (GuiButton((Rectangle){140,440,200,40}, "Annuler"))
    {
        titreInput[0]=auteurInput[0]=categorieInput[0]=isbnInput[0]=anneeBuf[0]=0;
        titreEdit=auteurEdit=categorieEdit=isbnEdit=anneeEdit=false;
        mode = LIVRES;
    }
}


        // ================== SUPPR LIVRE ==================
        else if(mode==SUPPR_LIVRE)
        {
            DrawText("Supprimer un livre par ID :",50,100,25,DARKGRAY);
            int idToDel=atoi(livreASupprimerBuf);
            GuiTextBox((Rectangle){300,90,100,40},livreASupprimerBuf,sizeof(livreASupprimerBuf),true);
            if(GuiButton((Rectangle){450,90,200,40},"Supprimer"))
            {
                supprimerLivre(livres,&nbLivres,idToDel);
                livreASupprimerBuf[0]='\0';
                mode=LIVRES;
            }
            if(GuiButton((Rectangle){600,500,250,40},"Retour")) mode=LIVRES;
        }

        // ================== USERS ==================
        else if(mode==USERS)
        {
            DrawText("Liste des utilisateurs :",50,20,25,DARKGRAY);
            for(int i=0;i<nbUsers;i++)
            {
                char buf[200];
                snprintf(buf,sizeof(buf),"%d - %s %s",utilisateurs[i].id,utilisateurs[i].nom,utilisateurs[i].prenom);
                DrawText(buf,50,70+i*25,20,BLACK);
            }
            if(GuiButton((Rectangle){600,70,250,40},"Ajouter un utilisateur")) mode=AJOUT_USER;
            if(GuiButton((Rectangle){600,120,250,40},"Supprimer un utilisateur")) mode=SUPPR_USER;
            if(GuiButton((Rectangle){600,500,250,40},"Retour menu")) mode=MENU;
        }

        // ================== AJOUT USER ==================
        else if (mode == AJOUT_USER)
        {
            DrawText("Ajouter un utilisateur", 50, 30, 25, DARKGRAY);

            Rectangle rNom    = (Rectangle){140,100,500,40};
            Rectangle rPrenom = (Rectangle){140,150,500,40};
            Rectangle rEmail  = (Rectangle){140,200,500,40};

            // Gestion du toggle d’édition
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 m = GetMousePosition();
                nomEdit    = CheckCollisionPointRec(m, rNom);
                prenomEdit = CheckCollisionPointRec(m, rPrenom);
                emailEdit  = CheckCollisionPointRec(m, rEmail);
            }

            DrawText("Nom :", 50, 110, 20, BLACK);
            GuiTextBox(rNom, nomInput, sizeof(nomInput)-1, nomEdit);

            DrawText("Prénom :", 50, 160, 20, BLACK);
            GuiTextBox(rPrenom, prenomInput, sizeof(prenomInput)-1, prenomEdit);

            DrawText("Email :", 50, 210, 20, BLACK);
            GuiTextBox(rEmail, emailInput, sizeof(emailInput)-1, emailEdit);

            // ---------- BOUTON VALIDER ----------
            if (GuiButton((Rectangle){140,270,200,40}, "Valider"))
            {
                if (strlen(nomInput) == 0 || strlen(prenomInput) == 0 || strlen(emailInput) == 0)
                {
                    // tu peux mettre un message d'erreur si tu veux
                }
                else
                {
                    ajouterUtilisateurManuel(utilisateurs, &nbUsers, nomInput, prenomInput, emailInput, 0);

                    // Reset
                    nomInput[0] = prenomInput[0] = emailInput[0] = 0;
                    nomEdit = prenomEdit = emailEdit = false;

                    mode = USERS;
                }
            }

            // ---------- BOUTON ANNULER ----------
            if (GuiButton((Rectangle){140,320,200,40}, "Annuler"))
            {
                nomInput[0] = prenomInput[0] = emailInput[0] = 0;
                nomEdit = prenomEdit = emailEdit = false;

                mode = USERS;
            }
        }

        // ================== SUPPR USER ==================
        else if(mode==SUPPR_USER)
        {
            DrawText("Supprimer un utilisateur par ID :",50,100,25,DARKGRAY);
            int idToDel=atoi(userASupprimerBuf);
            GuiTextBox((Rectangle){300,90,100,40},userASupprimerBuf,sizeof(userASupprimerBuf),true);
            if(GuiButton((Rectangle){450,90,200,40},"Supprimer"))
            {
                supprimerUtilisateur(utilisateurs,&nbUsers,idToDel);
                userASupprimerBuf[0]='\0';
                mode=USERS;
            }
            if(GuiButton((Rectangle){600,500,250,40},"Retour")) mode=USERS;
        }

        // ================== EMPRUNTS ==================
        else if(mode==EMPRUNTS)
        {
            DrawText("Gestion des emprunts",50,30,25,DARKGRAY);
            DrawText("ISBN livre :",50,100,20,BLACK);
            GuiTextBox((Rectangle){150,90,150,30},empruntISBN,sizeof(empruntISBN),true);
            DrawText("ID Utilisateur :",50,150,20,BLACK);
            char bufUser[10]; snprintf(bufUser,sizeof(bufUser),"%d",empruntIdUser);
            GuiTextBox((Rectangle){200,140,100,30},bufUser,sizeof(bufUser),true);
            empruntIdUser=atoi(bufUser);

            if(GuiButton((Rectangle){50,200,200,40},"Emprunter"))
            {
                char date[12]; getDateAujourdhui(date);
                emprunterLivre(livres,nbLivres,utilisateurs,nbUsers,emprunts,&nbEmprunts);
            }

            if(GuiButton((Rectangle){50,250,200,40},"Retourner"))
            {
                retournerLivre(emprunts,&nbEmprunts,0); // Pour simplifier
            }

            if(GuiButton((Rectangle){600,500,250,40},"Retour menu")) mode=MENU;
        }

        // ================== STATISTIQUES ==================
        else if(mode==STATS)
        {
            DrawText("Statistiques", 50, 30, 25, DARKGRAY);

            int y = 80;
            for(int i=0;i<nbLivres;i++)
            {
                char buf[200];
                snprintf(buf, sizeof(buf), "%d - %s [%s] - %s",
                         livres[i].id, livres[i].titre, livres[i].categorie,
                         livres[i].disponible ? "Dispo" : "Emprunté");
                DrawText(buf, 50, y, 20, BLACK);
                y += 25;
            }

            if(GuiButton((Rectangle){600,500,250,40},"Retour menu")) mode=MENU;

        }

        EndDrawing();
    }

    sauvegarderLivres(livres,nbLivres);
    sauvegarderUtilisateurs(utilisateurs,nbUsers);
    sauvegarderEmprunts(emprunts,nbEmprunts);

    CloseWindow();
    return 0;
}



