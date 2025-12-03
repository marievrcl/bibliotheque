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
    if (!fgets(buf, (int)n, stdin)) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
        buf[len-1] = '\0';
        len--;
    }
}

// Met une chaîne en minuscules
static void toLowerStr(char *s) {
    for (; *s; s++) {
        *s = (char)tolower((unsigned char)*s);
    }
}

// Retourne l'index d'un utilisateur par email (insensible à la casse)
static int indexParEmail(Utilisateur *users, int nbUsers, const char *email) {
    char ref[100];
    strncpy(ref, email, sizeof(ref) - 1);
    ref[sizeof(ref)-1] = '\0';
    toLowerStr(ref);

    for (int i = 0; i < nbUsers; i++) {
        char cur[100];
        strncpy(cur, users[i].email, sizeof(cur) - 1);
        cur[sizeof(cur)-1] = '\0';
        toLowerStr(cur);

        if (strcmp(cur, ref) == 0)
            return i;
    }
    return -1;
}

// -----------------------------------------------------------
// AJOUT
// -----------------------------------------------------------

void ajouterUtilisateur(Utilisateur *users, int *nbUsers) {
    Utilisateur u;

    // Déterminer l'ID suivant
    int nextId = 1;
    for (int i = 0; i < *nbUsers; i++) {
        if (users[i].id >= nextId) {
            nextId = users[i].id + 1;
        }
    }
    u.id = nextId;

    printf("\n--- AJOUT UTILISATEUR ---\n");

    printf("Nom : ");
    lireLigne(u.nom, sizeof(u.nom));

    printf("Prénom : ");
    lireLigne(u.prenom, sizeof(u.prenom));

    // Email unique
    while (1) {
        printf("Email : ");
        lireLigne(u.email, sizeof(u.email));

        if (u.email[0] == '\0') {
            printf("Email vide, réessaie.\n");
            continue;
        }

        if (strlen(u.email) >= 90) {
            printf("Email trop long.\n");
            continue;
        }

        if (indexParEmail(users, *nbUsers, u.email) != -1) {
            printf("Cet email est déjà utilisé.\n");
            continue;
        }

        break;
    }

    u.quota = 0;

    users[*nbUsers] = u;
    (*nbUsers)++;

    printf("Utilisateur ajouté (id=%d).\n", u.id);
}

// Ajoute un utilisateur minimal pour l'interface graphique
void ajouterUtilisateurManuel(Utilisateur users[], int *nb,
                              const char *nom, const char *prenom,
                              const char *email, int quota) {
    if (*nb >= MAX_USERS) return;

    int nextId = 1;
    for (int i = 0; i < *nb; i++)
        if (users[i].id >= nextId)
            nextId = users[i].id + 1;

    users[*nb].id = nextId;
    strncpy(users[*nb].nom, nom, sizeof(users[*nb].nom)-1);
    users[*nb].nom[sizeof(users[*nb].nom)-1] = '\0';

    strncpy(users[*nb].prenom, prenom, sizeof(users[*nb].prenom)-1);
    users[*nb].prenom[sizeof(users[*nb].prenom)-1] = '\0';

    strncpy(users[*nb].email, email, sizeof(users[*nb].email)-1);
    users[*nb].email[sizeof(users[*nb].email)-1] = '\0';

    users[*nb].quota = quota;

    (*nb)++;
}

// -----------------------------------------------------------
// SUPPRESSION
// -----------------------------------------------------------

void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id) {
    int pos = -1;

    for (int i = 0; i < *nbUsers; i++) {
        if (users[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Aucun utilisateur trouvé avec l'id %d.\n", id);
        return;
    }

    // Décalage
    for (int i = pos; i < *nbUsers - 1; i++) {
        users[i] = users[i + 1];
    }

    (*nbUsers)--;

    printf("Utilisateur %d supprimé.\n", id);
}

// -----------------------------------------------------------
// AFFICHAGE
// -----------------------------------------------------------

void afficherUtilisateurs(Utilisateur *users, int nbUsers) {
    printf("\n--- LISTE DES UTILISATEURS ---\n");

    if (nbUsers == 0) {
        printf("Aucun utilisateur.\n");
        return;
    }

    printf("%-4s | %-15s | %-15s | %-25s | %-5s\n",
           "ID", "Nom", "Prénom", "Email", "Quota");
    printf("----------------------------------------------------------------------\n");

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
    if (!email || email[0] == '\0')
        return 0;

    return (indexParEmail(users, nbUsers, email) != -1);
}
