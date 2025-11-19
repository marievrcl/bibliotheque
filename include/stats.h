//
// Module de statistiques : fonctions pour afficher des informations globales
// sur la bibliothèque (nombre, disponibilité, top emprunts, utilisateur le plus actif).
//

#ifndef STATS_H
#define STATS_H

#include "livres.h"
#include "utilisateurs.h"
#include "emprunts.h"

/**
 * Affiche un récapitulatif des statistiques :
 * - nombre de livres, utilisateurs, emprunts
 * - taux de disponibilité
 * - utilisateur le plus actif
 * - livre le plus emprunté
 */
void afficherStatistiques(Emprunt *emprunts, int nbEmprunts,
                          Utilisateur *users, int nbUsers,
                          Livre *livres, int nbLivres);

/**
 * Calcule et affiche le ou les livres les plus empruntés.
 */
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts,
                            Livre *livres, int nbLivres);

/**
 * Calcule et affiche l'utilisateur ayant effectué le plus d'emprunts.
 */
void utilisateurLePlusActif(Emprunt *emprunts, int nbEmprunts,
                            Utilisateur *users, int nbUsers);

#endif // STATS_H



