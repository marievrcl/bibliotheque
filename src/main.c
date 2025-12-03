//
// Created by Marie Viricel on 06/11/2025.
//

//
// main.c
// Bibliothèque - Interface graphique
//

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
        else if(mode==AJOUT_LIVRE)
        {
            DrawText("Ajouter un livre",50,30,25,DARKGRAY);
            DrawText("Titre :",50,120,20,BLACK);
            titreEdit=GuiTextBox((Rectangle){140,110,500,40},titreInput,sizeof(titreInput),titreEdit);
            DrawText("Auteur :",50,170,20,BLACK);
            auteurEdit=GuiTextBox((Rectangle){140,160,500,40},auteurInput,sizeof(auteurInput),auteurEdit);
            DrawText("Catégorie :",50,220,20,BLACK);
            categorieEdit=GuiTextBox((Rectangle){140,210,300,40},categorieInput,sizeof(categorieInput),categorieEdit);
            DrawText("ISBN :",50,270,20,BLACK);
            isbnEdit=GuiTextBox((Rectangle){140,260,200,40},isbnInput,sizeof(isbnInput),isbnEdit);
            DrawText("Année :",50,320,20,BLACK);
            anneeEdit=GuiTextBox((Rectangle){140,310,100,40},anneeBuf,sizeof(anneeBuf),anneeEdit);

            if(GuiButton((Rectangle){140,380,200,40},"Valider"))
            {
                Livre nouveau;
                strcpy(nouveau.titre,titreInput);
                strcpy(nouveau.auteur,auteurInput);
                strcpy(nouveau.categorie,categorieInput);
                strcpy(nouveau.isbn,isbnInput);
                nouveau.annee=atoi(anneeBuf);
                ajouterLivreGui(livres,&nbLivres,nouveau);

                titreInput[0]=auteurInput[0]=categorieInput[0]=isbnInput[0]='\0';
                anneeBuf[0]='\0';
                titreEdit=auteurEdit=categorieEdit=isbnEdit=anneeEdit=false;
                mode=LIVRES;
            }
            if(GuiButton((Rectangle){140,440,200,40},"Annuler"))
            {
                titreInput[0]=auteurInput[0]=categorieInput[0]=isbnInput[0]='\0';
                anneeBuf[0]='\0';
                titreEdit=auteurEdit=categorieEdit=isbnEdit=anneeEdit=false;
                mode=LIVRES;
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
        else if(mode==AJOUT_USER)
        {
            DrawText("Ajouter un utilisateur",50,30,25,DARKGRAY);
            DrawText("Nom :",50,110,20,BLACK);
            nomEdit=GuiTextBox((Rectangle){140,100,500,40},nomInput,sizeof(nomInput),nomEdit);
            DrawText("Prénom :",50,160,20,BLACK);
            prenomEdit=GuiTextBox((Rectangle){140,150,500,40},prenomInput,sizeof(prenomInput),prenomEdit);
            DrawText("Email :",50,210,20,BLACK);
            emailEdit=GuiTextBox((Rectangle){140,200,500,40},emailInput,sizeof(emailInput),emailEdit);

            if(GuiButton((Rectangle){140,270,200,40},"Valider"))
            {
                if(strlen(nomInput)==0||strlen(prenomInput)==0||strlen(emailInput)==0) {}
                else
                {
                    ajouterUtilisateurManuel(utilisateurs,&nbUsers,nomInput,prenomInput,emailInput,0);
                    nomInput[0]=prenomInput[0]=emailInput[0]='\0';
                    nomEdit=prenomEdit=emailEdit=false;
                    mode=USERS;
                }
            }
            if(GuiButton((Rectangle){140,320,200,40},"Annuler"))
            {
                nomInput[0]=prenomInput[0]=emailInput[0]='\0';
                nomEdit=prenomEdit=emailEdit=false;
                mode=USERS;
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
            DrawText("Statistiques",50,30,25,DARKGRAY);
            afficherStatistiques(emprunts,nbEmprunts,utilisateurs,nbUsers,livres,nbLivres);
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



