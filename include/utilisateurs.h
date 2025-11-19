//
// Module de gestion des utilisateurs : structure Utilisateur
// et fonctions pour ajouter, afficher et supprimer des utilisateurs.
//

#ifndef UTILISATEURS_H
#define UTILISATEURS_H

// Représente un utilisateur de la bibliothèque
typedef struct {
    int  id;          // Identifiant unique de l'utilisateur
    char nom[50];     // Nom
    char prenom[50];  // Prénom
    char email[100];  // Adresse email (unique, insensible à la casse)
    int  quota;       // Nombre de livres actuellement empruntés
} Utilisateur;

/**
 * Ajoute un nouvel utilisateur :
 * - Génère un id automatique
 * - Saisit nom, prénom, email
 * - Vérifie que l'email n'est pas déjà utilisé (insensible à la casse)
 */
void ajouterUtilisateur(Utilisateur *users, int *nbUsers);

/**
 * Supprime un utilisateur à partir de son id (décale le tableau).
 */
void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id);

/**
 * Affiche la liste des utilisateurs sous forme de tableau.
 */
void afficherUtilisateurs(Utilisateur *users, int nbUsers);

/**
 * Exemple de fonction d'authentification (simplifiée dans ton code).
 * Pour l'instant, renvoie 1 si la chaîne email n'est pas vide.
 */
int authentifierUtilisateur(char *email);

#endif // UTILISATEURS_H
