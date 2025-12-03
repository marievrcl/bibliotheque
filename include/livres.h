//
// Module de gestion des livres : structure Livre et fonctions
// pour ajouter, afficher, modifier, supprimer, rechercher et trier.
//

#ifndef LIVRES_H
#define LIVRES_H

// Représente un livre dans la bibliothèque
typedef struct {
    int  id;               // Identifiant unique du livre (sert à le retrouver facilement)
    char titre[100];       // Titre du livre (chaîne de caractères)
    char auteur[100];      // Nom de l'auteur du livre
    char categorie[50];    // Catégorie ou genre du livre (roman, BD, scientifique, etc.)
    char isbn[20];         // Code ISBN unique du livre (pour identification internationale)
    int  annee;            // Année de publication du livre
    int  disponible;       // Disponibilité du livre : 1 = disponible, 0 = emprunté
} Livre;

// Ajoute un nouveau livre dans le tableau 'livres' et incrémente le nombre total de livres
void ajouterLivre(Livre *livres, int *nbLivres);

// Supprime un livre à partir de son id et décale les autres éléments du tableau pour combler le vide
void supprimerLivre(Livre *livres, int *nbLivres, int id);

// Modifie les informations d'un livre existant (identifié par son id)
void modifierLivre(Livre *livres, int nbLivres, int id);

// Affiche la liste complète des livres sous forme de tableau avec toutes les informations
void afficherLivres(Livre *livres, int nbLivres);

// Recherche un livre par son titre exact
// Retourne l'index du livre dans le tableau si trouvé, sinon -1
int rechercherLivre(Livre *livres, int nbLivres, char *titre);

// Recherche un livre par son ISBN
// Retourne l'index du livre si trouvé, sinon -1
int rechercherLivreParISBN(Livre *livres, int nbLivres, char *isbn);

// Trie les livres par ordre alphabétique selon leur titre (tri simple type bubble sort ou insertion)
void trierLivres(Livre *livres, int nbLivres);

// Ajoute un livre en saisie manuelle (utilisé dans console ou tests)
void ajouterLivreManuel(Livre livres[], int *nb, const char *titre);

#endif // LIVRES_H

// Ajoute un livre dans le tableau depuis l'interface graphique
// 'aRajouter' contient toutes les informations du livre à ajouter
void ajouterLivreGui(Livre livres[], int *nb, Livre aRajouter);
