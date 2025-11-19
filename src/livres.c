#include <stdio.h>
#include <string.h>
#include "livres.h"

// === AJOUTER UN LIVRE ===
void ajouterLivre(Livre *livres, int *nbLivres) {
    Livre nouveau;

    printf("\n--- AJOUT D'UN LIVRE ---\n");

    // ID simple : position dans le tableau + 1
    nouveau.id = *nbLivres + 1;

    printf("Titre : ");
    scanf(" %[^\n]", nouveau.titre);
    printf("Auteur : ");
    scanf(" %[^\n]", nouveau.auteur);
    printf("Catégorie : ");
    scanf(" %[^\n]", nouveau.categorie);
    printf("ISBN : ");
    scanf(" %[^\n]", nouveau.isbn);
    printf("Année : ");
    scanf("%d", &nouveau.annee);

    // Le livre est dispo par défaut
    nouveau.disponible = 1;

    // Insertion dans le tableau
    livres[*nbLivres] = nouveau;
    (*nbLivres)++;

    printf("Livre ajouté avec succès ! (ID: %d, ISBN: %s)\n",
           nouveau.id, nouveau.isbn);
}

// === AFFICHER LES LIVRES ===
void afficherLivres(Livre *livres, int nbLivres) {
    printf("\n--- LISTE DES LIVRES ---\n");
    if (nbLivres == 0) {
        printf("Aucun livre enregistré.\n");
        return;
    }

    // En-tête de tableau bien alignée
    printf("%-4s | %-30s | %-18s | %-12s | %-10s | %-3s\n",
           "ID", "Titre", "Auteur", "Catégorie", "ISBN", "Dispo");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < nbLivres; i++) {
        printf("%-4d | %-30s | %-18s | %-12s | %-10s | %-3s\n",
               livres[i].id,
               livres[i].titre,
               livres[i].auteur,
               livres[i].categorie,
               livres[i].isbn,
               livres[i].disponible ? "Oui" : "Non");
    }
}

// === SUPPRIMER UN LIVRE ===
void supprimerLivre(Livre *livres, int *nbLivres, int id) {
    int found = 0;
    for (int i = 0; i < *nbLivres; i++) {
        if (livres[i].id == id) {
            // Décale tous les livres suivants vers la gauche
            for (int j = i; j < *nbLivres - 1; j++) {
                livres[j] = livres[j + 1];
            }
            (*nbLivres)--;
            found = 1;
            printf("Livre supprimé avec succès (ID %d).\n", id);
            break;
        }
    }
    if (!found) printf("Livre non trouvé.\n");
}

// === MODIFIER UN LIVRE ===
void modifierLivre(Livre *livres, int nbLivres, int id) {
    for (int i = 0; i < nbLivres; i++) {
        if (livres[i].id == id) {
            printf("\n--- MODIFICATION DU LIVRE [%d] ---\n", id);
            printf("Nouveau titre : ");
            scanf(" %[^\n]", livres[i].titre);
            printf("Nouvel auteur : ");
            scanf(" %[^\n]", livres[i].auteur);
            printf("Nouvelle catégorie : ");
            scanf(" %[^\n]", livres[i].categorie);
            printf("Nouveau ISBN : ");
            scanf(" %[^\n]", livres[i].isbn);
            printf("Nouvelle année : ");
            scanf("%d", &livres[i].annee);
            printf("Livre modifié avec succès.\n");
            return;
        }
    }
    printf("Livre introuvable.\n");
}

// === RECHERCHER UN LIVRE PAR TITRE ===
int rechercherLivre(Livre *livres, int nbLivres, char *titre) {
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].titre, titre) == 0) {
            return i;
        }
    }
    return -1;
}

// === RECHERCHER UN LIVRE PAR ISBN ===
int rechercherLivreParISBN(Livre *livres, int nbLivres, char *isbn) {
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].isbn, isbn) == 0) {
            return i;
        }
    }
    return -1;
}

// === TRIER LES LIVRES PAR TITRE (tri simple par échange) ===
void trierLivres(Livre *livres, int nbLivres) {
    Livre temp;
    for (int i = 0; i < nbLivres - 1; i++) {
        for (int j = i + 1; j < nbLivres; j++) {
            if (strcmp(livres[i].titre, livres[j].titre) > 0) {
                temp = livres[i];
                livres[i] = livres[j];
                livres[j] = temp;
            }
        }
    }
    printf("Livres triés par titre.\n");
}


