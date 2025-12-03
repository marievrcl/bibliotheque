//
// Created by Marie Viricel on 06/11/2025.
// Module de gestion des emprunts : déclaration de la structure Emprunt
// et des fonctions publiques pour emprunter / retourner / vérifier les retards.
//

#ifndef EMPRUNTS_H
#define EMPRUNTS_H

#include "livres.h"
#include "utilisateurs.h"

// Représente un emprunt d'un livre par un utilisateur
typedef struct {
    int idEmprunt;         // Identifiant unique de l'emprunt (sert à le retrouver facilement)
    int idLivre;           // ID du livre emprunté (fait référence à Livre.id)
    int idUtilisateur;     // ID de l'utilisateur qui a emprunté le livre (fait référence à Utilisateur.id)
    char dateEmprunt[11];  // Date de début de l'emprunt au format "JJ/MM/AAAA"
    char dateRetour[11];   // Date de retour prévue ou réelle, vide si le livre n'est pas encore rendu
    int retard;            // Indique si l'emprunt est en retard : 0 = non, 1 = retard (> 15 jours)
} Emprunt;

/**
 * Permet à un utilisateur d'emprunter un livre.
 *
 * Paramètres :
 * - livres : tableau des livres existants
 * - nbLivres : nombre total de livres dans le tableau
 * - users : tableau des utilisateurs
 * - nbUsers : nombre total d'utilisateurs
 * - emprunts : tableau des emprunts existants
 * - nbEmprunts : pointeur vers le nombre d'emprunts, sera incrémenté si un nouvel emprunt est créé
 *
 * Fonctionnement :
 * 1. Vérifie que le livre demandé existe et est disponible.
 * 2. Vérifie que l'utilisateur existe et n'a pas dépassé son quota.
 * 3. Demande la date d'emprunt à l'utilisateur.
 * 4. Crée un nouvel emprunt et met à jour la disponibilité du livre et éventuellement le quota utilisateur.
 */
void emprunterLivre(Livre *livres, int nbLivres,
                    Utilisateur *users, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts);

/**
 * Enregistre le retour d'un livre.
 *
 * Paramètres :
 * - emprunts : tableau des emprunts existants
 * - nbEmprunts : pointeur vers le nombre total d'emprunts
 * - idLivre : identifiant du livre retourné
 *
 * Fonctionnement :
 * 1. Demande la date de retour à l'utilisateur.
 * 2. Met à jour l'emprunt correspondant (dateRetour et retard si > 15 jours).
 * 3. La remise en disponibilité du livre et l'ajustement du quota peuvent être faits séparément.
 */
void retournerLivre(Emprunt *emprunts, int *nbEmprunts, int idLivre);

/**
 * Parcourt tous les emprunts non rendus et indique ceux en retard
 * par rapport à la date du jour saisie par l'utilisateur.
 *
 * Paramètres :
 * - emprunts : tableau des emprunts
 * - nbEmprunts : nombre total d'emprunts dans le tableau
 *
 * Fonctionnement :
 * 1. Compare la date du jour avec la date d'emprunt.
 * 2. Si l'emprunt dépasse 15 jours, le marque comme retard.
 * 3. Affiche les emprunts en retard.
 */
void verifierRetards(Emprunt *emprunts, int nbEmprunts);
void getDateAujourdhui(char *date); // <-- Prototype de la fonction
#endif // EMPRUNTS_H
