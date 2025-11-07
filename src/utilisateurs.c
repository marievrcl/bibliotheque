//
// Created by Marie Viricel on 06/11/2025.
//

#include <stdio.h>
#include <string.h>
#include "utilisateurs.h"

void ajouterUtilisateur(Utilisateur *users, int *nbUsers) {
    printf("[TODO] ajouterUtilisateur\n");
    (void)users; (void)nbUsers;
}
void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id) {
    printf("[TODO] supprimerUtilisateur id=%d\n", id);
    (void)users; (void)nbUsers;
}
void afficherUtilisateurs(Utilisateur *users, int nbUsers) {
    printf("[TODO] afficherUtilisateurs (%d)\n", nbUsers);
    (void)users;
}
int authentifierUtilisateur(char *email) {
    printf("[TODO] authentifierUtilisateur email=%s\n", email ? email : "(null)");
    return 1; // par défaut : "ok"
}