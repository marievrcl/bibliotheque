#ifndef LIVRES_H
#define LIVRES_H

// Représente un livre dans la bibliothèque
typedef struct {
    int  id;               // Identifiant unique du livre
    char titre[100];       // Titre du livre
    char auteur[100];      // Nom de l'auteur
    char categorie[50];    // Catégorie (roman, BD, etc.)
    char isbn[20];         // Code ISBN
    int  annee;            // Année de publication
    int  disponible;       // 1 = disponible, 0 = actuellement emprunté
} Livre;

// Ajoute un nouveau livre dans le tableau et incrémente nbLivres
void ajouterLivre(Livre *livres, int *nbLivres);

// Supprime un livre à partir de son id (décale le tableau)
void supprimerLivre(Livre *livres, int *nbLivres, int id);

// Modifie les informations d'un livre existant (recherche par id)
void modifierLivre(Livre *livres, int nbLivres, int id);

// Affiche la liste complète des livres sous forme de tableau
void afficherLivres(Livre *livres, int nbLivres);

// Recherche un livre par son titre exact
// Renvoie l'index dans le tableau, ou -1 si non trouvé.
int rechercherLivre(Livre *livres, int nbLivres, char *titre);

// Recherche un livre par son ISBN (utilisé dans livres.c)
int rechercherLivreParISBN(Livre *livres, int nbLivres, char *isbn);

// Trie les livres par ordre alphabétique de titre (tri simple)
void trierLivres(Livre *livres, int nbLivres);

void ajouterLivreGui(Livre livres[], int *nb, Livre aRajouter);
#endif // LIVRES_H
