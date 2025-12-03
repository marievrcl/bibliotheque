#include <stdio.h>
#include <string.h>
#include "livres.h"

// === AJOUTER UN LIVRE ===
void ajouterLivre(Livre *livres, int *nbLivres) {
    Livre nouveau;  // création d'une variable pour stocker le nouveau livre

    printf("\n--- AJOUT D'UN LIVRE ---\n");  // titre pour l'utilisateur

    // ID simple : position dans le tableau + 1
    nouveau.id = *nbLivres + 1;

    // Saisie des informations du livre
    printf("Titre : ");
    scanf(" %[^\n]", nouveau.titre);      // lit une ligne complète pour le titre
    printf("Auteur : ");
    scanf(" %[^\n]", nouveau.auteur);     // lit une ligne complète pour l'auteur
    printf("Catégorie : ");
    scanf(" %[^\n]", nouveau.categorie);  // lit une ligne complète pour la catégorie
    printf("ISBN : ");
    scanf(" %[^\n]", nouveau.isbn);       // lit une ligne complète pour l'ISBN
    printf("Année : ");
    scanf("%d", &nouveau.annee);          // lit un entier pour l'année

    // Le livre est dispo par défaut
    nouveau.disponible = 1;

    // Insertion dans le tableau des livres
    livres[*nbLivres] = nouveau;
    (*nbLivres)++;  // incrémente le nombre de livres

    // Confirmation
    printf("Livre ajouté avec succès ! (ID: %d, ISBN: %s)\n",
           nouveau.id, nouveau.isbn);
}

// === AFFICHER LES LIVRES ===
void afficherLivres(Livre *livres, int nbLivres) {
    printf("\n--- LISTE DES LIVRES ---\n");

    if (nbLivres == 0) {  // si aucun livre
        printf("Aucun livre enregistré.\n");
        return;
    }

    // En-tête du tableau
    printf("%-4s | %-30s | %-18s | %-12s | %-10s | %-3s\n",
           "ID", "Titre", "Auteur", "Catégorie", "ISBN", "Dispo");
    printf("-------------------------------------------------------------------------------------------\n");

    // Affichage de chaque livre
    for (int i = 0; i < nbLivres; i++) {
        printf("%-4d | %-30s | %-18s | %-12s | %-10s | %-3s\n",
               livres[i].id,                   // ID
               livres[i].titre,                // Titre
               livres[i].auteur,               // Auteur
               livres[i].categorie,            // Catégorie
               livres[i].isbn,                 // ISBN
               livres[i].disponible ? "Oui" : "Non"); // Disponibilité
    }
}

// === SUPPRIMER UN LIVRE ===
void supprimerLivre(Livre *livres, int *nbLivres, int id) {
    int found = 0;  // flag pour savoir si le livre est trouvé
    for (int i = 0; i < *nbLivres; i++) {
        if (livres[i].id == id) {  // si on trouve le livre à supprimer
            // Décale tous les livres suivants vers la gauche
            for (int j = i; j < *nbLivres - 1; j++) {
                livres[j] = livres[j + 1];
            }
            (*nbLivres)--;  // décrémente le nombre de livres
            found = 1;
            printf("Livre supprimé avec succès (ID %d).\n", id);
            break;
        }
    }
    if (!found) printf("Livre non trouvé.\n"); // si livre non trouvé
}

// === MODIFIER UN LIVRE ===
void modifierLivre(Livre *livres, int nbLivres, int id) {
    for (int i = 0; i < nbLivres; i++) {
        if (livres[i].id == id) {  // trouve le livre à modifier
            printf("\n--- MODIFICATION DU LIVRE [%d] ---\n", id);

            // Saisie des nouvelles informations
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
    printf("Livre introuvable.\n"); // si livre non trouvé
}

// === RECHERCHER UN LIVRE PAR TITRE ===
int rechercherLivre(Livre *livres, int nbLivres, char *titre) {
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].titre, titre) == 0) { // comparaison exacte
            return i;  // retourne l'index si trouvé
        }
    }
    return -1; // pas trouvé
}

// === RECHERCHER UN LIVRE PAR ISBN ===
int rechercherLivreParISBN(Livre *livres, int nbLivres, const char *isbn) {
    for(int i = 0; i < nbLivres; i++) {
        if(strcmp(livres[i].isbn, isbn) == 0) return i;
    }
    return -1;
}

// === TRIER LES LIVRES PAR TITRE (tri simple par échange) ===
void trierLivres(Livre *livres, int nbLivres) {
    Livre temp;  // variable temporaire pour échange
    for (int i = 0; i < nbLivres - 1; i++) {
        for (int j = i + 1; j < nbLivres; j++) {
            if (strcmp(livres[i].titre, livres[j].titre) > 0) { // si titre[i] > titre[j]
                temp = livres[i];       // échange des livres
                livres[i] = livres[j];
                livres[j] = temp;
            }
        }
    }
    printf("Livres triés par titre.\n"); // confirmation
}

// === AJOUTER UN LIVRE VIA L'INTERFACE GRAPHIQUE ===
void ajouterLivreGui(Livre livres[], int *nb, Livre aRajouter)
{
    // Génération automatique de l'ID
    if (*nb == 0)
        aRajouter.id = 1;             // si aucun livre, ID = 1
    else
        aRajouter.id = livres[*nb - 1].id + 1; // sinon ID = dernier ID +1

    // Livre disponible par défaut
    aRajouter.disponible = 1;

    // Ajout du livre dans le tableau
    livres[*nb] = aRajouter;
    (*nb)++; // incrémente le nombre total de livres
}



