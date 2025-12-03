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

// Constante indiquant le chemin du dossier de données
static const char *DATA_PATH = "data";

/* Assure que le dossier data existe, crée si nécessaire */
static void ensure_dir_exists(const char *path) {
#ifdef _WIN32
    _mkdir(path);        // Windows : création du dossier
#else
    mkdir(path, 0777);   // Linux/Mac : création du dossier avec droits rwxrwxrwx
#endif
}

/* ============================================================
 *                      CHARGEMENT LIVRES
 * ============================================================ */
void chargerLivres(Livre *livres, int *nbLivres) {
    *nbLivres = 0;                     // initialise le compteur de livres

    ensure_dir_exists(DATA_PATH);      // assure que le dossier data existe

    char path[256];                     // buffer pour construire le chemin complet
    snprintf(path, sizeof(path), "%s/livres.txt", DATA_PATH); // crée "./data/livres.txt"

    FILE *f = fopen(path, "r");         // ouvre le fichier en lecture
    if (!f) {                           // si le fichier n'existe pas
        printf("Aucun fichier livres.txt trouvé. Un nouveau sera créé.\n");
        return;                         // on quitte la fonction
    }

    // Lecture ligne par ligne du fichier livres.txt
    while (fscanf(f, "%d;%99[^;];%99[^;];%49[^;];%19[^;];%d;%d\n",
                  &livres[*nbLivres].id,       // ID du livre
                  livres[*nbLivres].titre,     // titre
                  livres[*nbLivres].auteur,    // auteur
                  livres[*nbLivres].categorie,// catégorie
                  livres[*nbLivres].isbn,      // ISBN
                  &livres[*nbLivres].annee,    // année
                  &livres[*nbLivres].disponible) == 7) // disponible
    {
        (*nbLivres)++;                   // incrémente le compteur de livres lus
    }

    fclose(f);                           // ferme le fichier
}

/* ============================================================
 *                      SAUVEGARDE LIVRES
 * ============================================================ */
void sauvegarderLivres(Livre *livres, int nbLivres) {
    ensure_dir_exists(DATA_PATH);        // assure que le dossier data existe

    char path[256];                       // buffer pour chemin
    snprintf(path, sizeof(path), "%s/livres.txt", DATA_PATH); // "./data/livres.txt"

    FILE *f = fopen(path, "w");           // ouvre le fichier en écriture (écrase le fichier existant)
    if (!f) {                             // si ouverture échoue
        printf("Erreur : impossible d’ouvrir %s\n", path);
        return;                           // sortie
    }

    // Écriture des livres dans le fichier
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

    fclose(f);                            // ferme le fichier
}

/* ============================================================
 *                     CHARGEMENT UTILISATEURS
 * ============================================================ */
void chargerUtilisateurs(Utilisateur *users, int *nbUsers) {
    *nbUsers = 0;                         // initialise le compteur

    ensure_dir_exists(DATA_PATH);         // assure que dossier data existe

    char path[256];                        // buffer pour chemin
    snprintf(path, sizeof(path), "%s/utilisateurs.txt", DATA_PATH); // "./data/utilisateurs.txt"

    FILE *f = fopen(path, "r");            // ouvre fichier en lecture
    if (!f) {                              // si fichier inexistant
        printf("Aucun fichier utilisateurs.txt trouvé. Un nouveau sera créé.\n");
        return;
    }

    // Lecture ligne par ligne du fichier utilisateurs.txt
    while (fscanf(f, "%d;%49[^;];%49[^;];%99[^;];%d\n",
                  &users[*nbUsers].id,     // ID utilisateur
                  users[*nbUsers].nom,     // nom
                  users[*nbUsers].prenom,  // prénom
                  users[*nbUsers].email,   // email
                  &users[*nbUsers].quota) == 5) // quota livres
    {
        (*nbUsers)++;                     // incrémente le compteur
    }

    fclose(f);                             // ferme le fichier
}

/* ============================================================
 *                     SAUVEGARDE UTILISATEURS
 * ============================================================ */
void sauvegarderUtilisateurs(Utilisateur *users, int nbUsers) {
    ensure_dir_exists(DATA_PATH);         // assure dossier data

    char path[256];                        // buffer chemin
    snprintf(path, sizeof(path), "%s/utilisateurs.txt", DATA_PATH); // "./data/utilisateurs.txt"

    FILE *f = fopen(path, "w");           // ouvre fichier en écriture
    if (!f) {                             // si impossible
        printf("Erreur : impossible d’ouvrir %s\n", path);
        return;
    }

    // Écriture de tous les utilisateurs
    for (int i = 0; i < nbUsers; i++) {
        fprintf(f, "%d;%s;%s;%s;%d\n",
                users[i].id,
                users[i].nom,
                users[i].prenom,
                users[i].email,
                users[i].quota);
    }

    fclose(f);                            // ferme le fichier
}

/* ============================================================
 *                     CHARGEMENT EMPRUNTS
 * ============================================================ */
void chargerEmprunts(Emprunt *e, int *nbE) {
    *nbE = 0;                             // initialise compteur

    ensure_dir_exists(DATA_PATH);         // assure dossier data

    char path[256];                        // buffer chemin
    snprintf(path, sizeof(path), "%s/emprunts.txt", DATA_PATH); // "./data/emprunts.txt"

    FILE *f = fopen(path, "r");           // ouvre fichier en lecture
    if (!f) {                             // si fichier inexistant
        printf("Aucun fichier emprunts.txt trouvé. Un nouveau sera créé.\n");
        return;
    }

    // Lecture ligne par ligne du fichier emprunts.txt
    while (fscanf(f, "%d;%d;%d;%10[^;];%10[^;];%d\n",
                  &e[*nbE].idEmprunt,    // ID emprunt
                  &e[*nbE].idLivre,      // ID livre
                  &e[*nbE].idUtilisateur, // ID utilisateur
                  e[*nbE].dateEmprunt,    // date emprunt
                  e[*nbE].dateRetour,     // date retour
                  &e[*nbE].retard) == 6)  // retard
    {
        (*nbE)++;                           // incrémente compteur
    }

    fclose(f);                               // ferme fichier
}

/* ============================================================
 *                     SAUVEGARDE EMPRUNTS
 * ============================================================ */
void sauvegarderEmprunts(Emprunt *e, int nbE) {
    ensure_dir_exists(DATA_PATH);           // assure dossier data

    char path[256];                          // buffer chemin
    snprintf(path, sizeof(path), "%s/emprunts.txt", DATA_PATH); // "./data/emprunts.txt"

    FILE *f = fopen(path, "w");             // ouvre fichier en écriture
    if (!f) {                               // si impossible
        printf("Erreur : impossible d’ouvrir %s\n", path);
        return;
    }

    // Écriture de tous les emprunts
    for (int i = 0; i < nbE; i++) {
        fprintf(f, "%d;%d;%d;%s;%s;%d\n",
                e[i].idEmprunt,
                e[i].idLivre,
                e[i].idUtilisateur,
                e[i].dateEmprunt,
                e[i].dateRetour,
                e[i].retard);
    }

    fclose(f);                               // ferme fichier
}


