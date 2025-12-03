//
// Created by Marie Viricel on 06/11/2025.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utilisateurs.h"

// -----------------------------------------------------------
// UTILITAIRES
// -----------------------------------------------------------

// Lire une ligne proprement (supprime \n et \r)
static void lireLigne(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) { // Lit une ligne depuis stdin, retourne NULL si erreur
        buf[0] = '\0';                 // Si erreur, initialise le buffer à vide
        return;
    }
    size_t len = strlen(buf);          // Longueur de la chaîne lue
    while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) { // Supprime CR/LF à la fin
        buf[len-1] = '\0';
        len--;
    }
}

// Met une chaîne en minuscules
static void toLowerStr(char *s) {
    for (; *s; s++) {                  // Parcourt chaque caractère jusqu'au '\0'
        *s = (char)tolower((unsigned char)*s); // Convertit en minuscule
    }
}

// Retourne l'index d'un utilisateur par email (insensible à la casse)
static int indexParEmail(Utilisateur *users, int nbUsers, const char *email) {
    char ref[100];
    strncpy(ref, email, sizeof(ref) - 1); // Copie email dans ref
    ref[sizeof(ref)-1] = '\0';            // S'assure que ref est terminé par '\0'
    toLowerStr(ref);                       // Met en minuscules pour comparaison insensible à la casse

    for (int i = 0; i < nbUsers; i++) {   // Parcourt tous les utilisateurs
        char cur[100];
        strncpy(cur, users[i].email, sizeof(cur) - 1); // Copie email utilisateur
        cur[sizeof(cur)-1] = '\0';                     // Terminaison sécurisée
        toLowerStr(cur);                               // Conversion en minuscules

        if (strcmp(cur, ref) == 0)                    // Si égal
            return i;                                 // Retourne l'index
    }
    return -1; // Non trouvé
}

// -----------------------------------------------------------
// AJOUT
// -----------------------------------------------------------

// Ajoute un utilisateur via console
void ajouterUtilisateur(Utilisateur *users, int *nbUsers) {
    Utilisateur u;

    // Déterminer l'ID suivant automatiquement
    int nextId = 1;
    for (int i = 0; i < *nbUsers; i++) {
        if (users[i].id >= nextId) {
            nextId = users[i].id + 1; // ID supérieur au plus grand existant
        }
    }
    u.id = nextId; // Assigne l'ID

    printf("\n--- AJOUT UTILISATEUR ---\n");

    printf("Nom : ");
    lireLigne(u.nom, sizeof(u.nom)); // Lit le nom

    printf("Prénom : ");
    lireLigne(u.prenom, sizeof(u.prenom)); // Lit le prénom

    // Email unique
    while (1) {
        printf("Email : ");
        lireLigne(u.email, sizeof(u.email)); // Lit l’email

        if (u.email[0] == '\0') {           // Vérifie que ce n'est pas vide
            printf("Email vide, réessaie.\n");
            continue;
        }

        if (strlen(u.email) >= 90) {        // Vérifie la longueur max
            printf("Email trop long.\n");
            continue;
        }

        if (indexParEmail(users, *nbUsers, u.email) != -1) { // Vérifie unicité
            printf("Cet email est déjà utilisé.\n");
            continue;
        }

        break; // Email valide
    }

    u.quota = 0; // Quota initial à 0

    users[*nbUsers] = u; // Ajoute l’utilisateur au tableau
    (*nbUsers)++;        // Incrémente le nombre total

    printf("Utilisateur ajouté (id=%d).\n", u.id);
}

// Ajoute un utilisateur minimal pour l'interface graphique
void ajouterUtilisateurManuel(Utilisateur users[], int *nb,
                              const char *nom, const char *prenom,
                              const char *email, int quota) {
    if (*nb >= MAX_USERS) return; // Vérifie limite max

    int nextId = 1;
    for (int i = 0; i < *nb; i++)
        if (users[i].id >= nextId)
            nextId = users[i].id + 1; // ID supérieur au plus grand existant

    users[*nb].id = nextId;

    strncpy(users[*nb].nom, nom, sizeof(users[*nb].nom)-1); // Copie nom
    users[*nb].nom[sizeof(users[*nb].nom)-1] = '\0';        // Terminaison

    strncpy(users[*nb].prenom, prenom, sizeof(users[*nb].prenom)-1); // Copie prénom
    users[*nb].prenom[sizeof(users[*nb].prenom)-1] = '\0';

    strncpy(users[*nb].email, email, sizeof(users[*nb].email)-1);   // Copie email
    users[*nb].email[sizeof(users[*nb].email)-1] = '\0';

    users[*nb].quota = quota; // Assigne le quota

    (*nb)++; // Incrémente nombre total
}

// -----------------------------------------------------------
// SUPPRESSION
// -----------------------------------------------------------

void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id) {
    int pos = -1;

    for (int i = 0; i < *nbUsers; i++) {
        if (users[i].id == id) { // Cherche l’utilisateur par ID
            pos = i;
            break;
        }
    }

    if (pos == -1) { // Non trouvé
        printf("Aucun utilisateur trouvé avec l'id %d.\n", id);
        return;
    }

    // Décalage des utilisateurs suivants
    for (int i = pos; i < *nbUsers - 1; i++) {
        users[i] = users[i + 1];
    }

    (*nbUsers)--; // Décrémente le nombre d’utilisateurs

    printf("Utilisateur %d supprimé.\n", id);
}

// -----------------------------------------------------------
// AFFICHAGE
// -----------------------------------------------------------

void afficherUtilisateurs(Utilisateur *users, int nbUsers) {
    printf("\n--- LISTE DES UTILISATEURS ---\n");

    if (nbUsers == 0) { // Aucun utilisateur
        printf("Aucun utilisateur.\n");
        return;
    }

    // Affichage des entêtes du tableau
    printf("%-4s | %-15s | %-15s | %-25s | %-5s\n",
           "ID", "Nom", "Prénom", "Email", "Quota");
    printf("----------------------------------------------------------------------\n");

    // Boucle pour afficher tous les utilisateurs
    for (int i = 0; i < nbUsers; i++) {
        printf("%-4d | %-15s | %-15s | %-25s | %-5d\n",
               users[i].id,
               users[i].nom,
               users[i].prenom,
               users[i].email,
               users[i].quota);
    }
}

// -----------------------------------------------------------
// AUTHENTIFICATION
// -----------------------------------------------------------

int authentifierUtilisateur(Utilisateur *users, int nbUsers, const char *email) {
    if (!email || email[0] == '\0')       // Si email vide ou NULL
        return 0;                          // Retourne faux

    return (indexParEmail(users, nbUsers, email) != -1); // Retourne vrai si trouvé
}
