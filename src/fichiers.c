//
// Created by Marie Viricel on 06/11/2025.
//

#include <stdio.h>
#include <string.h>
#include "fichiers.h"

// === LIVRES ===
void chargerLivres(Livre *livres, int *nbLivres) {
    FILE *f = fopen("data/livres.txt", "r");
    if (!f) {
        printf("Impossible d'ouvrir data/livres.txt (créé à la sauvegarde)\n");
        *nbLivres = 0;
        return;
    }

    *nbLivres = 0;
    while (fscanf(f, "%d;%99[^;];%99[^;];%49[^;];%19[^;];%d;%d\n",
                  &livres[*nbLivres].id,
                  livres[*nbLivres].titre,
                  livres[*nbLivres].auteur,
                  livres[*nbLivres].categorie,
                  livres[*nbLivres].isbn,
                  &livres[*nbLivres].annee,
                  &livres[*nbLivres].disponible) == 7)
    {
        (*nbLivres)++;
    }

    fclose(f);
    printf("%d livres chargés depuis le fichier.\n", *nbLivres);
}

void sauvegarderLivres(Livre *livres, int nbLivres) {
    FILE *f = fopen("data/livres.txt", "w");
    if (!f) {
        printf("Erreur : impossible d'ouvrir data/livres.txt pour écriture.\n");
        return;
    }

    for (int i = 0; i < nbLivres; i++) {
        fprintf(f, "%d;%s;%s;%s;%s;%d;%d\n",
                livres[i].id,
                livres[i].titre,
                livres[i].auteur,
                livres[i].categorie,
                livres[i].isbn,
                livres[i].annee,
                livres[i].disponible);
    }

    fclose(f);
    printf("%d livres sauvegardés dans data/livres.txt.\n", nbLivres);
}

// === UTILISATEURS ===
void chargerUtilisateurs(Utilisateur *users, int *nbUsers) {
    FILE *f = fopen("data/utilisateurs.txt", "r");
    if (!f) {
        printf("Impossible d'ouvrir data/utilisateurs.txt (créé à la sauvegarde)\n");
        *nbUsers = 0;
        return;
    }

    *nbUsers = 0;
    while (fscanf(f, "%d;%49[^;];%49[^;];%99[^;];%d\n",
                  &users[*nbUsers].id,
                  users[*nbUsers].nom,
                  users[*nbUsers].prenom,
                  users[*nbUsers].email,
                  &users[*nbUsers].quota) == 5)
    {
        (*nbUsers)++;
    }

    fclose(f);
    printf("%d utilisateurs chargés depuis le fichier.\n", *nbUsers);
}

void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers) {
    FILE *f = fopen("data/utilisateurs.txt", "w");
    if (!f) {
        printf("Erreur : impossible d'ouvrir data/utilisateurs.txt.\n");
        return;
    }

    for (int i = 0; i < nbUsers; i++) {
        fprintf(f, "%d;%s;%s;%s;%d\n",
                users[i].id,
                users[i].nom,
                users[i].prenom,
                users[i].email,
                users[i].quota);
    }

    fclose(f);
    printf("%d utilisateurs sauvegardés dans data/utilisateurs.txt.\n", nbUsers);
}

// === EMPRUNTS ===
void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts) {
    FILE *f = fopen("data/emprunts.txt", "r");
    if (!f) {
        printf("Impossible d'ouvrir data/emprunts.txt (créé à la sauvegarde)\n");
        *nbEmprunts = 0;
        return;
    }

    *nbEmprunts = 0;
    while (fscanf(f, "%d;%d;%d;%10[^;];%10[^;];%d\n",
                  &emprunts[*nbEmprunts].idEmprunt,
                  &emprunts[*nbEmprunts].idLivre,
                  &emprunts[*nbEmprunts].idUtilisateur,
                  emprunts[*nbEmprunts].dateEmprunt,
                  emprunts[*nbEmprunts].dateRetour,
                  &emprunts[*nbEmprunts].retard) == 6)
    {
        (*nbEmprunts)++;
    }

    fclose(f);
    printf("%d emprunts chargés depuis le fichier.\n", *nbEmprunts);
}

void sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts) {
    FILE *f = fopen("data/emprunts.txt", "w");
    if (!f) {
        printf("Erreur : impossible d'ouvrir data/emprunts.txt.\n");
        return;
    }

    for (int i = 0; i < nbEmprunts; i++) {
        fprintf(f, "%d;%d;%d;%s;%s;%d\n",
                emprunts[i].idEmprunt,
                emprunts[i].idLivre,
                emprunts[i].idUtilisateur,
                emprunts[i].dateEmprunt,
                emprunts[i].dateRetour,
                emprunts[i].retard);
    }

    fclose(f);
    printf("%d emprunts sauvegardés dans data/emprunts.txt.\n", nbEmprunts);
}
