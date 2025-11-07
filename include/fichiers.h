//
// Created by Marie Viricel on 06/11/2025.
//

#ifndef FICHIERS_H
#define FICHIERS_H
#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"

void chargerLivres(Livre *livres, int *nbLivres);
void sauvegarderLivres(Livre *livres, int nbLivres);
void chargerUtilisateurs(Utilisateur *users, int *nbUsers);
void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers);
void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts);
void sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts);

#endif

