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
 * Affiche un récapitulatif des statistiques de la bibliothèque.
 *
 * Paramètres :
 * - emprunts : tableau des emprunts existants
 * - nbEmprunts : nombre total d'emprunts
 * - users : tableau des utilisateurs
 * - nbUsers : nombre total d'utilisateurs
 * - livres : tableau des livres
 * - nbLivres : nombre total de livres
 *
 * Fonctionnement :
 * 1. Affiche le nombre total de livres, utilisateurs et emprunts.
 * 2. Calcule le taux de disponibilité des livres.
 * 3. Identifie et affiche l'utilisateur ayant effectué le plus d'emprunts.
 * 4. Identifie et affiche le ou les livres les plus empruntés.
 */
void afficherStatistiques(Emprunt *emprunts, int nbEmprunts,
                          Utilisateur *users, int nbUsers,
                          Livre *livres, int nbLivres);

/**
 * Calcule et affiche le ou les livres les plus empruntés.
 *
 * Paramètres :
 * - emprunts : tableau des emprunts existants
 * - nbEmprunts : nombre total d'emprunts
 * - livres : tableau des livres
 * - nbLivres : nombre total de livres
 *
 * Fonctionnement :
 * 1. Parcourt tous les emprunts pour compter le nombre de fois
 *    que chaque livre a été emprunté.
 * 2. Affiche le(s) livre(s) ayant le plus grand nombre d'emprunts.
 */
void livresLesPlusEmpruntes(Emprunt *emprunts, int nbEmprunts,
                            Livre *livres, int nbLivres);

/**
 * Calcule et affiche l'utilisateur ayant effectué le plus d'emprunts.
 *
 * Paramètres :
 * - emprunts : tableau des emprunts existants
 * - nbEmprunts : nombre total d'emprunts
 * - users : tableau des utilisateurs
 * - nbUsers : nombre total d'utilisateurs
 *
 * Fonctionnement :
 * 1. Parcourt tous les emprunts pour compter combien d'emprunts
 *    chaque utilisateur a effectué.
 * 2. Identifie et affiche l'utilisateur ayant le plus grand nombre d'emprunts.
 */
void utilisateurLePlusActif(Emprunt *emprunts, int nbEmprunts,
                            Utilisateur *users, int nbUsers);

#endif // STATS_H



