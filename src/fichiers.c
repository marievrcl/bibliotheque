#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "fichiers.h"

/*
 * VERSION FIXÉE — UTILISE TOUJOURS LE DOSSIER "data/" DU PROJET
 * Peu importe où l'exécutable se trouve (cmake-build-debug/ ou ailleurs),
 * les fichiers seront toujours lus/écrits dans :
 *
 *    ./data/livres.txt
 *    ./data/utilisateurs.txt
 *    ./data/emprunts.txt
 */

static const char *DATA_PATH = "../data";

/* Assure que le dossier data existe */
static void ensure_dir_exists(const char *path) {
#ifdef _WIN32
    _mkdir(path);
#else
    mkdir(path, 0777);
#endif
}

/* ============================================================
 *                      CHARGEMENT LIVRES
 * ============================================================ */
void chargerLivres(Livre *livres, int *nbLivres) {
    *nbLivres = 0;

    ensure_dir_exists(DATA_PATH);

    char path[256];
    snprintf(path, sizeof(path), "%s/livres.txt", DATA_PATH);

    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Aucun fichier livres.txt trouvé. Un nouveau sera créé.\n");
        return;
    }

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
}

/* ============================================================
 *                      SAUVEGARDE LIVRES
 * ============================================================ */
void sauvegarderLivres(Livre *livres, int nbLivres) {
    ensure_dir_exists(DATA_PATH);

    char path[256];
    snprintf(path, sizeof(path), "%s/livres.txt", DATA_PATH);

    FILE *f = fopen(path, "w");
    if (!f) {
        printf("Erreur : impossible d’ouvrir %s\n", path);
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
}

/* ============================================================
 *                     CHARGEMENT UTILISATEURS
 * ============================================================ */
void chargerUtilisateurs(Utilisateur *users, int *nbUsers) {
    *nbUsers = 0;

    ensure_dir_exists(DATA_PATH);

    char path[256];
    snprintf(path, sizeof(path), "%s/utilisateurs.txt", DATA_PATH);

    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Aucun fichier utilisateurs.txt trouvé. Un nouveau sera créé.\n");
        return;
    }

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
}

/* ============================================================
 *                     SAUVEGARDE UTILISATEURS
 * ============================================================ */
void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers) {
    ensure_dir_exists(DATA_PATH);

    char path[256];
    snprintf(path, sizeof(path), "%s/utilisateurs.txt", DATA_PATH);

    FILE *f = fopen(path, "w");
    if (!f) {
        printf("Erreur : impossible d’ouvrir %s\n", path);
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
}

/* ============================================================
 *                     CHARGEMENT EMPRUNTS
 * ============================================================ */
void chargerEmprunts(Emprunt *e, int *nbE) {
    *nbE = 0;

    ensure_dir_exists(DATA_PATH);

    char path[256];
    snprintf(path, sizeof(path), "%s/emprunts.txt", DATA_PATH);

    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Aucun fichier emprunts.txt trouvé. Un nouveau sera créé.\n");
        return;
    }

    while (fscanf(f, "%d;%d;%d;%10[^;];%10[^;];%d\n",
                  &e[*nbE].idEmprunt,
                  &e[*nbE].idLivre,
                  &e[*nbE].idUtilisateur,
                  e[*nbE].dateEmprunt,
                  e[*nbE].dateRetour,
                  &e[*nbE].retard) == 6)
    {
        (*nbE)++;
    }

    fclose(f);
}

/* ============================================================
 *                     SAUVEGARDE EMPRUNTS
 * ============================================================ */
void sauvegarderEmprunts(Emprunt *e, int nbE) {
    ensure_dir_exists(DATA_PATH);

    char path[256];
    snprintf(path, sizeof(path), "%s/emprunts.txt", DATA_PATH);

    FILE *f = fopen(path, "w");
    if (!f) {
        printf("Erreur : impossible d’ouvrir %s\n", path);
        return;
    }

    for (int i = 0; i < nbE; i++) {
        fprintf(f, "%d;%d;%d;%s;%s;%d\n",
                e[i].idEmprunt,
                e[i].idLivre,
                e[i].idUtilisateur,
                e[i].dateEmprunt,
                e[i].dateRetour,
                e[i].retard);
    }

    fclose(f);
}

