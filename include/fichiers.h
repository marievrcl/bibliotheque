//
// Module de gestion des fichiers de données (dossier data/).
// Déclare les fonctions pour charger et sauvegarder les livres, utilisateurs et emprunts
// dans des fichiers texte (.txt) séparés.
//
#ifndef FICHIERS_H
#define FICHIERS_H

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"

// Charge la liste des livres depuis data/livres.txt
void chargerLivres(Livre *livres, int *nbLivres);

// Sauvegarde tous les livres dans data/livres.txt
void sauvegarderLivres(Livre *livres, int nbLivres);

// Charge la liste des utilisateurs depuis data/utilisateurs.txt
void chargerUtilisateurs(Utilisateur *users, int *nbUsers);

// Sauvegarde les utilisateurs dans data/utilisateurs.txt
void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers);

// Charge la liste des emprunts depuis data/emprunts.txt
void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts);

// Sauvegarde les emprunts dans data/emprunts.txt
void sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts);

#endif // FICHIERS_H

