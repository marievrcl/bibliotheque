//
// Created by Marie Viricel on 06/11/2025.
//

#ifndef LIVRES_H
#define LIVRES_H

typedef struct {
    int id;
    char titre[100];
    char auteur[100];
    char categorie[50];
    char isbn[20];
    int annee;
    int disponible; // 1 = dispo, 0 = emprunté
} Livre;

void ajouterLivre(Livre *livres, int *nbLivres);
void supprimerLivre(Livre *livres, int *nbLivres, int id);
void modifierLivre(Livre *livres, int nbLivres, int id);
void afficherLivres(Livre *livres, int nbLivres);
int  rechercherLivre(Livre *livres, int nbLivres, char *titre);
void trierLivres(Livre *livres, int nbLivres);

#endif
