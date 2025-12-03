//
// Module de gestion des utilisateurs : structure Utilisateur
// et fonctions pour ajouter, afficher et supprimer des utilisateurs.
//

#ifndef UTILISATEURS_H
#define UTILISATEURS_H

#define MAX_USERS 100  // Nombre maximum d'utilisateurs que la bibliothèque peut gérer

// Représente un utilisateur de la bibliothèque
typedef struct {
    int  id;          // Identifiant unique de l'utilisateur
    char nom[50];     // Nom de l'utilisateur
    char prenom[50];  // Prénom de l'utilisateur
    char email[100];  // Adresse email (doit être unique, insensible à la casse)
    int  quota;       // Nombre de livres actuellement empruntés
} Utilisateur;

/**
 * Ajoute un nouvel utilisateur dans le tableau users.
 * - nbUsers est incrémenté après l'ajout.
 */
void ajouterUtilisateur(Utilisateur *users, int *nbUsers);

/**
 * Ajoute un utilisateur avec des informations précises (utile pour tests ou interface).
 * Paramètres :
 * - users : tableau d'utilisateurs
 * - nb : nombre actuel d'utilisateurs
 * - nom, prenom, email, quota : informations de l'utilisateur à ajouter
 */
void ajouterUtilisateurManuel(Utilisateur users[], int *nb,
                              const char *nom, const char *prenom,
                              const char *email, int quota);

/**
 * Supprime un utilisateur identifié par son id.
 * - Décale le tableau pour combler l'emplacement supprimé.
 * - Décrémente nbUsers.
 */
void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id);

/**
 * Affiche la liste complète des utilisateurs sous forme de tableau.
 */
void afficherUtilisateurs(Utilisateur *users, int nbUsers);

/**
 * Authentifie un utilisateur à partir de son email.
 * - Renvoie l'index dans le tableau si trouvé, sinon -1.
 * - Comparaison insensible à la casse.
 */
int authentifierUtilisateur(Utilisateur *users, int nbUsers, const char *email);

#endif // UTILISATEURS_H


