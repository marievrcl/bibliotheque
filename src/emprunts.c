#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "emprunts.h"

// ================== FONCTIONS UTILITAIRES ==================

// Lit une ligne complète depuis l'entrée standard (stdin) et supprime le '\n' final
static void lireLigne(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) { // lit au maximum n caractères depuis stdin, retourne NULL si erreur
        buf[0] = '\0';                 // si fgets échoue, on met la chaîne vide
        return;                         // on sort de la fonction
    }
    size_t len = strlen(buf);          // calcule la longueur de la chaîne lue
    if (len && buf[len-1] == '\n')     // si le dernier caractère est un saut de ligne '\n'
        buf[len-1] = '\0';             // on le remplace par le caractère nul
}

// Vide le buffer d'entrée pour éviter les caractères résiduels après scanf
static void clearInput(void) {
    int c;                              // variable temporaire pour stocker le caractère lu
    while ((c = getchar()) != '\n' && c != EOF) {} // on lit tous les caractères jusqu'à la fin de ligne ou EOF
}

// --------- Fonctions de gestion des dates (format "JJ/MM/AAAA") ----------

// Vérifie si une année est bissextile (retourne 1 si oui, 0 sinon)
static int estBissextile(int y){
    return (y%4==0 && y%100!=0) || (y%400==0); // conditions standard des années bissextiles
}

// Retourne le nombre de jours dans un mois donné, en tenant compte des années bissextiles
static int joursDansMois(int m, int y){
    static const int base[12]={31,28,31,30,31,30,31,31,30,31,30,31}; // jours par mois par défaut
    if(m==2 && estBissextile(y)) return 29;  // février dans une année bissextile
    return base[m-1];                        // renvoie le nombre de jours pour le mois
}

// Convertit une date JJ/MM/AAAA en nombre de jours depuis 01/01/1970
static int toEpochLike(const char *d){
    int j=0, m=0, a=0;                         // variables pour jour, mois, année
    if (sscanf(d, "%d/%d/%d", &j, &m, &a) != 3) return -1; // lit la date, retourne -1 si format invalide
    if(a<1970||m<1||m>12||j<1||j>31) return -1; // vérifie que les valeurs sont dans les plages valides
    int days = 0;                              // compteur de jours
    for(int y=1970; y<a; ++y) days += estBissextile(y)?366:365; // ajoute les jours des années complètes
    for(int mm=1; mm<m; ++mm) days += joursDansMois(mm,a);       // ajoute les jours des mois de l'année
    if (j > joursDansMois(m,a)) return -1;      // vérifie que le jour n'excède pas le mois
    days += (j-1);                              // ajoute le jour courant
    return days;                                // retourne le total de jours
}

// Calcule la différence en jours entre deux dates d2 - d1
static int diffJours(const char *d1, const char *d2){
    int a = toEpochLike(d1), b = toEpochLike(d2); // convertit les dates en "jours depuis 1970"
    if (a<0 || b<0) return 0;                     // retourne 0 si une date est invalide
    return b - a;                                 // différence en jours
}

// Recherche un livre par son ID dans le tableau et retourne son index
static int indexLivreParId(Livre *livres, int nbLivres, int id){
    for(int i=0; i<nbLivres; i++)                 // parcours de tous les livres
        if(livres[i].id==id) return i;            // si ID trouvé, retourne l'index
    return -1;                                    // sinon retourne -1
}

// Recherche un utilisateur par son ID dans le tableau et retourne son index
static int indexUserParId(Utilisateur *u, int nb, int id){
    for(int i=0; i<nb; i++)                       // parcours de tous les utilisateurs
        if(u[i].id==id) return i;                 // si ID trouvé, retourne l'index
    return -1;                                    // sinon retourne -1
}

// Cherche un emprunt actif (non rendu) pour un livre donné
static int indexEmpruntActifParLivre(Emprunt *e, int nb, int idLivre){
    for(int i=0; i<nb; i++) {                     // parcours de tous les emprunts
        if(e[i].idLivre==idLivre &&              // si le livre correspond
           (e[i].dateRetour[0]=='\0' || strcmp(e[i].dateRetour,"-")==0)) // et qu'il n'est pas encore rendu
            return i;                             // retourne l'index de l'emprunt
    }
    return -1;                                    // aucun emprunt actif trouvé
}

// Retourne le prochain ID d'emprunt disponible (max actuel + 1)
static int nextEmpruntId(Emprunt *e, int nb){
    int max=0;                                    // initialise le max à 0
    for(int i=0;i<nb;i++)                          // parcours des emprunts existants
        if(e[i].idEmprunt>max) max=e[i].idEmprunt; // met à jour le max si ID plus grand
    return max+1;                                 // retourne le prochain ID disponible
}

// ================== FONCTIONS PUBLIQUES ==================

// Fonction principale pour effectuer un emprunt
void emprunterLivre(Livre *livres, int nbLivres,
                    Utilisateur *users, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts)
{
    printf("\n--- EMPRUNTER UN LIVRE ---\n");     // affiche le titre de la section
    int idLivre, idUser;                           // variables pour les IDs

    // Saisie de l'ID du livre
    printf("ID du livre : ");                       // demande à l'utilisateur
    if (scanf("%d",&idLivre)!=1){                  // lit l'ID
        clearInput();                              // vide le buffer si entrée invalide
        printf("Entrée invalide.\n");             // message d'erreur
        return;                                    // quitte la fonction
    }
    clearInput();                                  // vide le buffer après scanf

    int iL = indexLivreParId(livres, nbLivres, idLivre); // recherche le livre
    if (iL<0){ printf(" Livre introuvable.\n"); return; } // si non trouvé, message et sortie
    if (livres[iL].disponible==0){ printf(" Livre déjà emprunté.\n"); return; } // si non dispo

    // Saisie de l'ID de l'utilisateur
    printf("ID de l'utilisateur : ");              // demande ID
    if (scanf("%d",&idUser)!=1){                   // lecture
        clearInput();                              // vider buffer
        printf("Entrée invalide.\n");             // message erreur
        return;                                    // sortie
    }
    clearInput();                                  // vider buffer

    int iU = indexUserParId(users, nbUsers, idUser); // recherche utilisateur
    if (iU<0){ printf(" Utilisateur introuvable.\n"); return; } // si non trouvé
    if (users[iU].quota >= 3){ printf(" Quota atteint (3 prêts max).\n"); return; } // quota max

    // Saisie de la date d'emprunt
    char date[11];                                 // variable pour stocker la date
    printf("Date d'emprunt (JJ/MM/AAAA) : ");      // demande la date
    lireLigne(date, sizeof(date));                 // lecture sécurisée
    if (toEpochLike(date)<0){ printf(" Date invalide.\n"); return; } // vérifie format

    // Création de l’emprunt
    Emprunt e;                                     // variable temporaire pour l'emprunt
    e.idEmprunt     = nextEmpruntId(emprunts, *nbEmprunts); // ID unique
    e.idLivre       = idLivre;                     // associe le livre
    e.idUtilisateur = idUser;                      // associe l'utilisateur
    strncpy(e.dateEmprunt, date, sizeof(e.dateEmprunt)); // copie date d'emprunt
    e.dateEmprunt[10]='\0';                        // s'assure que chaîne terminée
    e.dateRetour[0] = '\0';                        // livre pas encore rendu
    e.retard        = 0;                           // initialement pas de retard

    emprunts[*nbEmprunts] = e;                     // ajoute au tableau d'emprunts
    (*nbEmprunts)++;                               // incrémente le compteur

    // Mise à jour du livre et de l'utilisateur
    livres[iL].disponible = 0;                     // livre maintenant indisponible
    users[iU].quota++;                             // incrémente le quota utilisateur

    printf(" Emprunt enregistré (id=%d). Livre [%d] maintenant indisponible.\n",
           e.idEmprunt, idLivre);                  // message de confirmation
}

// Enregistre le retour d'un livre et calcule un retard éventuel
void retournerLivre(Emprunt *emprunts, int *nbEmprunts, int idLivre)
{
    if (*nbEmprunts==0){ printf("Aucun emprunt.\n"); return; } // aucun emprunt

    // Recherche d'un emprunt actif pour ce livre
    int idx = indexEmpruntActifParLivre(emprunts, *nbEmprunts, idLivre);
    if (idx<0){ printf(" Aucun emprunt actif pour ce livre.\n"); return; } // non trouvé

    // Saisie de la date de retour
    char dateR[11];                                 // variable pour stocker date retour
    printf("Date de retour (JJ/MM/AAAA) : ");      // demande date
    lireLigne(dateR, sizeof(dateR));               // lecture sécurisée
    if (toEpochLike(dateR)<0){ printf(" Date invalide.\n"); return; } // vérifie format

    // Mise à jour de l'emprunt
    strncpy(emprunts[idx].dateRetour, dateR, sizeof(emprunts[idx].dateRetour)); // copie date
    emprunts[idx].dateRetour[10]='\0';           // s'assure de la fin de chaîne
    int d = diffJours(emprunts[idx].dateEmprunt, dateR); // calcul différence en jours
    emprunts[idx].retard = (d > 15) ? 1 : 0;     // met retard si >15 jours

    printf(" Livre %d rendu. %s\n",               // affiche confirmation et retard
           idLivre,
           emprunts[idx].retard ? "️ Retard détecté (>15j)" : "Retour dans les temps");
}

// Vérifie tous les emprunts non rendus et signale ceux en retard
void verifierRetards(Emprunt *emprunts, int nbEmprunts)
{
    if (nbEmprunts==0){ printf("Aucun emprunt.\n"); return; } // aucun emprunt à vérifier

    char dateAujourd[11];                            // variable pour date du jour
    printf("Date du jour (JJ/MM/AAAA) : ");          // demande date
    lireLigne(dateAujourd, sizeof(dateAujourd));     // lecture sécurisée
    if (toEpochLike(dateAujourd)<0){ printf(" Date invalide.\n"); return; } // vérifie format

    int nbRetards = 0;                               // compteur de retards
    printf("\n--- RETARDS EN COURS (>30 jours) ---\n");
    for (int i=0; i<nbEmprunts; i++){              // parcours des emprunts
        if (emprunts[i].dateRetour[0] == '\0' || strcmp(emprunts[i].dateRetour,"-")==0){ // non rendus
            int d = diffJours(emprunts[i].dateEmprunt, dateAujourd); // calcul jours écoulés
            if (d > 30){                             // si plus de 30 jours
                emprunts[i].retard = 1;             // marque retard
                nbRetards++;                         // incrémente compteur
                printf("• Emprunt #%d  Livre:%d  Utilisateur:%d  Jours:%d  -> RETARD\n",
                       emprunts[i].idEmprunt,      // ID emprunt
                       emprunts[i].idLivre,       // ID livre
                       emprunts[i].idUtilisateur,// ID utilisateur
                       d);                        // nombre de jours
            }
        }
    }
    if (nbRetards==0) printf("Aucun retard.\n");    // si aucun retard
}

// ================== FONCTION GET DATE ==================
#include <time.h>  // nécessaire pour time(), localtime()

void getDateAujourdhui(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, 12, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

