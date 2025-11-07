//
// Created by Marie Viricel on 06/11/2025.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utilisateurs.h"

// utilitaire: lire une ligne entière (remplace avantageusement scanf("%[^\n]"))
static void lireLigne(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) { buf[0] = '\0'; return; }
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
}

// utilitaire: mettre une chaîne en minuscules (pour comparer emails)
static void toLowerStr(char *s) { for (; *s; ++s) *s = (char)tolower((unsigned char)*s); }

// renvoie l'index par email (insensible à la casse), sinon -1
static int indexParEmail(Utilisateur *users, int nbUsers, const char *email) {
    char ref[100]; strncpy(ref, email, sizeof(ref)); ref[sizeof(ref)-1] = '\0'; toLowerStr(ref);
    for (int i = 0; i < nbUsers; i++) {
        char cur[100]; strncpy(cur, users[i].email, sizeof(cur)); cur[sizeof(cur)-1] = '\0'; toLowerStr(cur);
        if (strcmp(cur, ref) == 0) return i;
    }
    return -1;
}

void ajouterUtilisateur(Utilisateur *users, int *nbUsers) {
    Utilisateur u;
    // ID auto-incrémenté (simple : max existant + 1)
    int nextId = 1;
    for (int i = 0; i < *nbUsers; i++)
        if (users[i].id >= nextId) nextId = users[i].id + 1;
    u.id = nextId;

    printf("\n--- AJOUT UTILISATEUR ---\n");
    printf("Nom : ");    lireLigne(u.nom, sizeof(u.nom));
    printf("Prénom : "); lireLigne(u.prenom, sizeof(u.prenom));

    // Email unique
    while (1) {
        printf("Email : "); lireLigne(u.email, sizeof(u.email));
        if (u.email[0] == '\0') { printf("Email vide, réessaie.\n"); continue; }
        if (indexParEmail(users, *nbUsers, u.email) != -1) {
            printf("Email déjà utilisé. Réessaie.\n");
            continue;
        }
        break;
    }

    u.quota = 0; // 0 livre emprunté au départ

    users[*nbUsers] = u;
    (*nbUsers)++;
    printf("Utilisateur ajouté (id=%d).\n", u.id);
}

void supprimerUtilisateur(Utilisateur *users, int *nbUsers, int id) {
    int pos = -1;
    for (int i = 0; i < *nbUsers; i++) {
        if (users[i].id == id) { pos = i; break; }
    }
    if (pos == -1) { printf("Utilisateur introuvable (id=%d).\n", id); return; }

    // décaler pour combler le trou
    for (int j = pos; j < *nbUsers - 1; j++) users[j] = users[j + 1];
    (*nbUsers)--;
    printf("Utilisateur %d supprimé.\n", id);
}

void afficherUtilisateurs(Utilisateur *users, int nbUsers) {
    printf("\n--- LISTE DES UTILISATEURS ---\n");
    if (nbUsers == 0) { printf("Aucun utilisateur.\n"); return; }

    printf("%-4s | %-15s | %-15s | %-25s | %-5s\n", "ID", "Nom", "Prénom", "Email", "Quota");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < nbUsers; i++) {
        printf("%-4d | %-15s | %-15s | %-25s | %-5d\n",
               users[i].id, users[i].nom, users[i].prenom, users[i].email, users[i].quota);
    }
}

int authentifierUtilisateur(char *email) {
    // Stub : retourne 1 si une chaîne non vide est fournie
    // (Tu pourras plus tard vérifier contre un tableau d’utilisateurs chargé)
    return (email && email[0] != '\0') ? 1 : 0;
}
