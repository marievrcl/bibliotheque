//
// Created by Marie Viricel on 06/11/2025.
//
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "fichiers.h"

// Détection automatique du dossier data, même depuis cmake-build-debug
static const char *detect_data_path(void) {
    static char buffer[512];
    FILE *test;

    // 1. Test : "data/livres.txt" dans le dossier courant
    test = fopen("data/livres.txt", "r");
    if (test) { fclose(test); strcpy(buffer, "data"); return buffer; }

    // 2. Test : "../data/livres.txt" (si on est dans cmake-build-debug)
    test = fopen("../data/livres.txt", "r");
    if (test) { fclose(test); strcpy(buffer, "../data"); return buffer; }

    // 3. Sinon, par défaut "data"
    strcpy(buffer, "data");
    return buffer;
}

static void ensure_dir_exists(const char *path) {
    mkdir(path, 0777);
}

/* =================== LIVRES =================== */
void chargerLivres(Livre *livres, int *nbLivres) {
    *nbLivres = 0;
    const char *base = detect_data_path();
    char path[512];
    snprintf(path, sizeof(path), "%s/livres.txt", base);
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("⚠️ Fichier introuvable : %s (créé lors de la première sauvegarde)\n", path);
        return;
    }

    while (fscanf(f, "%d;%99[^;];%99[^;];%49[^;];%19[^;];%d;%d\n",
                  &livres[*nbLivres].id,
                  livres[*nbLivres].titre,
                  livres[*nbLivres].auteur,
                  livres[*nbLivres].categorie,
                  livres[*nbLivres].isbn,
                  &livres[*nbLivres].annee,
                  &livres[*nbLivres].disponible) == 7) {
        (*nbLivres)++;
    }
    fclose(f);
    printf("✅ %d livres chargés depuis %s\n", *nbLivres, path);
}

void sauvegarderLivres(Livre *livres, int nbLivres) {
    const char *base = detect_data_path();
    ensure_dir_exists(base);
    char path[512];
    snprintf(path, sizeof(path), "%s/livres.txt", base);
    FILE *f = fopen(path, "w");
    if (!f) { printf("❌ Impossible d’ouvrir %s\n", path); return; }

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
    printf("💾 %d livres sauvegardés dans %s\n", nbLivres, path);
}

/* =================== UTILISATEURS =================== */
void chargerUtilisateurs(Utilisateur *users, int *nbUsers) {
    *nbUsers = 0;
    const char *base = detect_data_path();
    char path[512];
    snprintf(path, sizeof(path), "%s/utilisateurs.txt", base);
    FILE *f = fopen(path, "r");
    if (!f) { printf("⚠️ Fichier introuvable : %s\n", path); return; }

    while (fscanf(f, "%d;%49[^;];%49[^;];%99[^;];%d\n",
                  &users[*nbUsers].id,
                  users[*nbUsers].nom,
                  users[*nbUsers].prenom,
                  users[*nbUsers].email,
                  &users[*nbUsers].quota) == 5) {
        (*nbUsers)++;
    }
    fclose(f);
    printf("✅ %d utilisateurs chargés depuis %s\n", *nbUsers, path);
}

void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers) {
    const char *base = detect_data_path();
    ensure_dir_exists(base);
    char path[512];
    snprintf(path, sizeof(path), "%s/utilisateurs.txt", base);
    FILE *f = fopen(path, "w");
    if (!f) { printf("❌ Impossible d’ouvrir %s\n", path); return; }

    for (int i = 0; i < nbUsers; i++) {
        fprintf(f, "%d;%s;%s;%s;%d\n",
                users[i].id,
                users[i].nom,
                users[i].prenom,
                users[i].email,
                users[i].quota);
    }
    fclose(f);
    printf("💾 %d utilisateurs sauvegardés dans %s\n", nbUsers, path);
}

/* =================== EMPRUNTS =================== */
void chargerEmprunts(Emprunt *emprunts, int *nbEmprunts) {
    *nbEmprunts = 0;
    const char *base = detect_data_path();
    char path[512];
    snprintf(path, sizeof(path), "%s/emprunts.txt", base);
    FILE *f = fopen(path, "r");
    if (!f) { printf("⚠️ Fichier introuvable : %s\n", path); return; }

    while (fscanf(f, "%d;%d;%d;%10[^;];%10[^;];%d\n",
                  &emprunts[*nbEmprunts].idEmprunt,
                  &emprunts[*nbEmprunts].idLivre,
                  &emprunts[*nbEmprunts].idUtilisateur,
                  emprunts[*nbEmprunts].dateEmprunt,
                  emprunts[*nbEmprunts].dateRetour,
                  &emprunts[*nbEmprunts].retard) == 6) {
        (*nbEmprunts)++;
    }
    fclose(f);
    printf("✅ %d emprunts chargés depuis %s\n", *nbEmprunts, path);
}

void sauvegarderEmprunts(Emprunt *emprunts, int nbEmprunts) {
    const char *base = detect_data_path();
    ensure_dir_exists(base);
    char path[512];
    snprintf(path, sizeof(path), "%s/emprunts.txt", base);
    FILE *f = fopen(path, "w");
    if (!f) { printf("❌ Impossible d’ouvrir %s\n", path); return; }

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
    printf("💾 %d emprunts sauvegardés dans %s\n", nbEmprunts, path);
}
