//
// Module de gestion des utilisateurs : structure Utilisateur
// et fonctions pour ajouter, afficher et supprimer des utilisateurs.
//

#ifndef UTILISATEURS_H
#define UTILISATEURS_H

#define MAX_USERS 100

typedef struct {
    int  id;          // Identifiant unique de l'utilisateur
    char nom[50];     // Nom
    char prenom[50];  // Prénom
    char email[100];  // Adresse email (unique, insensible à la casse)
    int  quota;       // Nombre de livres actuellement empruntés
} Utilisateur;

void ajouterUtilisateur(Utilisateur *users, int *nbUsers);

void ajouterUtilisateurManuel(Utilisateur users[], int *nb,
                              const char *nom, const char *prenom,
                              const char *email, int quota);

void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id);

void afficherUtilisateurs(Utilisateur *users, int nbUsers);

int authentifierUtilisateur(Utilisateur *users, int nbUsers, const char *email);

#endif // UTILISATEURS_H

