//
// Created by Marie Viricel on 06/11/2025.
//

#ifndef BIBLIOTHEQUE_STATS_H
#define BIBLIOTHEQUE_STATS_H

#endif //BIBLIOTHEQUE_STATS_H

#ifndef STATS_H
#define STATS_H
#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"

void afficherStatistiques(Emprunt *emprunts, int nbEmprunts, Utilisateur *users, int nbUsers, Livre *livres, int nbLivres);
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts);
void utilisateurLePlusActif(Emprunt *emprunts, Utilisateur *users, int nbUsers);

#endif
