//
// Created by Marie Viricel on 06/11/2025.
//

#ifndef STATS_H
#define STATS_H

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"

// Fonction principale : affichage global des stats
void afficherStatistiques(Emprunt *emprunts, int nbEmprunts,
                          Utilisateur *users, int nbUsers,
                          Livre *livres, int nbLivres);

// Sous-fonctions utilisées par afficherStatistiques
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts,
                            Livre *livres, int nbLivres);

void utilisateurLePlusActif(Emprunt *emprunts, int nbEmprunts,
                            Utilisateur *users, int nbUsers);

#endif


