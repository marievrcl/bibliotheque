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
    int idEmprunt;         // Identifiant unique de l'emprunt
    int idLivre;           // ID du livre emprunté (référence à Livre.id)
    int idUtilisateur;     // ID de l'utilisateur (référence à Utilisateur.id)
    char dateEmprunt[11];  // Date de début d'emprunt au format "JJ/MM/AAAA"
    char dateRetour[11];   // Date de retour au même format, vide si pas encore rendu
    int retard;            // 0 = pas de retard, 1 = retard (> 15 jours)
} Emprunt;

/**
 * Permet à un utilisateur d'emprunter un livre.
 * - Vérifie que le livre existe et est disponible.
 * - Vérifie que l'utilisateur existe et n'a pas dépassé son quota.
 * - Demande la date d'emprunt.
 * - Crée un nouvel Emprunt et met à jour la disponibilité du livre et le quota de l'utilisateur.
 */
void emprunterLivre(Livre *livres, int nbLivres,
                    Utilisateur *users, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts);

/**
 * Enregistre le retour d'un livre :
 * - Demande la date de retour.
 * - Met à jour l'emprunt correspondant (dateRetour, retard si >15 jours).
 * (La remise en dispo du livre et l'ajustement du quota peuvent être faits séparément si besoin.)
 */
void retournerLivre(Emprunt *emprunts, int *nbEmprunts, int idLivre);

/**
 * Parcourt tous les emprunts non rendus et indique ceux en retard
 * par rapport à une date du jour saisie par l'utilisateur.
 */
void verifierRetards(Emprunt *emprunts, int nbEmprunts);

#endif // EMPRUNTS_H
