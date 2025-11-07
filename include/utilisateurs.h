//
// Created by Marie Viricel on 06/11/2025.
//
#ifndef UTILISATEURS_H
#define UTILISATEURS_H

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char email[100];
    int quota; // nb de livres empruntés
} Utilisateur;

void ajouterUtilisateur(Utilisateur *users, int *nbUsers);
void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id);
void afficherUtilisateurs(Utilisateur *users, int nbUsers);
int  authentifierUtilisateur(char *email);

#endif
