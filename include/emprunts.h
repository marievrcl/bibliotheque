//
// Created by Marie Viricel on 06/11/2025.
//

#ifndef EMPRUNTS_H
#define EMPRUNTS_H
#include "livres.h"
#include "utilisateurs.h"

typedef struct {
    int idEmprunt;
    int idLivre;
    int idUtilisateur;
    char dateEmprunt[11]; // "JJ/MM/AAAA"
    char dateRetour[11];  // "JJ/MM/AAAA" (vide si pas rendu)
    int retard;           // 0/1
} Emprunt;

void emprunterLivre(Livre *livres, int nbLivres, Utilisateur *users, int nbUsers, Emprunt *emprunts, int *nbEmprunts);
void retournerLivre(Emprunt *emprunts, int *nbEmprunts, int idLivre);
void verifierRetards(Emprunt *emprunts, int nbEmprunts);

#endif
