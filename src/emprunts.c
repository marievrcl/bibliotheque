#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "emprunts.h"

// ================== FONCTIONS UTILITAIRES ==================

// Lit une ligne complète depuis l'entrée standard (stdin) et supprime le '\n' final
static void lireLigne(char *buf, size_t n) {
    if (!fgets(buf, (int)n, stdin)) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n')
        buf[len-1] = '\0';
}

// --------- Fonctions de gestion des dates (format "JJ/MM/AAAA") ----------
static int estBissextile(int y){
    return (y%4==0 && y%100!=0) || (y%400==0);
}

static int joursDansMois(int m, int y){
    static const int base[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(m==2 && estBissextile(y)) return 29;
    return base[m-1];
}

static int toEpochLike(const char *d){
    int j=0, m=0, a=0;
    if (sscanf(d, "%d/%d/%d", &j, &m, &a) != 3) return -1;
    if(a<1970||m<1||m>12||j<1||j>31) return -1;
    int days = 0;
    for(int y=1970; y<a; ++y) days += estBissextile(y)?366:365;
    for(int mm=1; mm<m; ++mm) days += joursDansMois(mm,a);
    if (j > joursDansMois(m,a)) return -1;
    days += (j-1);
    return days;
}

static int diffJours(const char *d1, const char *d2){
    int a = toEpochLike(d1), b = toEpochLike(d2);
    if (a<0 || b<0) return 0;
    return b - a;
}

static int indexLivreParId(Livre *livres, int nbLivres, int id){
    for(int i=0; i<nbLivres; i++)
        if(livres[i].id==id) return i;
    return -1;
}

static int indexUserParId(Utilisateur *u, int nb, int id){
    for(int i=0; i<nb; i++)
        if(u[i].id==id) return i;
    return -1;
}

static int indexEmpruntActifParLivre(Emprunt *e, int nb, int idLivre){
    for(int i=0; i<nb; i++) {
        if(e[i].idLivre==idLivre && (e[i].dateRetour[0]=='\0' || strcmp(e[i].dateRetour,"-")==0))
            return i;
    }
    return -1;
}

static int nextEmpruntId(Emprunt *e, int nb){
    int max=0;
    for(int i=0;i<nb;i++)
        if(e[i].idEmprunt>max) max=e[i].idEmprunt;
    return max+1;
}

// ================== FONCTIONS PUBLIQUES ==================
void emprunterLivre(Livre *livres, int nbLivres,
                    Utilisateur *users, int nbUsers,
                    Emprunt *emprunts, int *nbEmprunts)
{
    printf("\n--- EMPRUNTER UN LIVRE ---\n");

    char buffer[32];
    int idLivre, idUser;

    // ID du livre
    printf("ID du livre : ");
    lireLigne(buffer, sizeof(buffer));
    if(sscanf(buffer, "%d", &idLivre) != 1){ printf("Entrée invalide.\n"); return; }

    int iL = indexLivreParId(livres, nbLivres, idLivre);
    if (iL<0){ printf("Livre introuvable.\n"); return; }
    if (livres[iL].disponible==0){ printf("Livre déjà emprunté.\n"); return; }

    // ID utilisateur
    printf("ID de l'utilisateur : ");
    lireLigne(buffer, sizeof(buffer));
    if(sscanf(buffer, "%d", &idUser) != 1){ printf("Entrée invalide.\n"); return; }

    int iU = indexUserParId(users, nbUsers, idUser);
    if (iU<0){ printf("Utilisateur introuvable.\n"); return; }
    if (users[iU].quota >= 3){ printf("Quota atteint (3 prêts max).\n"); return; }

    // Date d'emprunt
    char date[11];
    printf("Date d'emprunt (JJ/MM/AAAA) : ");
    lireLigne(date, sizeof(date));
    if(toEpochLike(date)<0){ printf("Date invalide.\n"); return; }

    // Création de l’emprunt
    Emprunt e;
    e.idEmprunt     = nextEmpruntId(emprunts, *nbEmprunts);
    e.idLivre       = idLivre;
    e.idUtilisateur = idUser;
    strncpy(e.dateEmprunt, date, sizeof(e.dateEmprunt));
    e.dateEmprunt[10]='\0';
    e.dateRetour[0]='\0';
    e.retard=0;

    emprunts[*nbEmprunts] = e;
    (*nbEmprunts)++;

    livres[iL].disponible = 0;
    users[iU].quota++;

    printf("Emprunt enregistré (id=%d). Livre [%d] maintenant indisponible.\n", e.idEmprunt, idLivre);
}

void retournerLivre(Emprunt *emprunts, int *nbEmprunts, int idLivre)
{
    if(*nbEmprunts==0){ printf("Aucun emprunt.\n"); return; }
    int idx = indexEmpruntActifParLivre(emprunts, *nbEmprunts, idLivre);
    if(idx<0){ printf("Aucun emprunt actif pour ce livre.\n"); return; }

    char dateR[11];
    printf("Date de retour (JJ/MM/AAAA) : ");
    lireLigne(dateR, sizeof(dateR));
    if(toEpochLike(dateR)<0){ printf("Date invalide.\n"); return; }

    strncpy(emprunts[idx].dateRetour, dateR, sizeof(emprunts[idx].dateRetour));
    emprunts[idx].dateRetour[10]='\0';
    int d = diffJours(emprunts[idx].dateEmprunt, dateR);
    emprunts[idx].retard = (d>15)?1:0;

    printf("Livre %d rendu. %s\n", idLivre, emprunts[idx].retard ? "Retard détecté (>15j)" : "Retour dans les temps");
}

void verifierRetards(Emprunt *emprunts, int nbEmprunts)
{
    if(nbEmprunts==0){ printf("Aucun emprunt.\n"); return; }

    char dateAujourd[11];
    printf("Date du jour (JJ/MM/AAAA) : ");
    lireLigne(dateAujourd, sizeof(dateAujourd));
    if(toEpochLike(dateAujourd)<0){ printf("Date invalide.\n"); return; }

    int nbRetards=0;
    printf("\n--- RETARDS EN COURS (>30 jours) ---\n");
    for(int i=0;i<nbEmprunts;i++){
        if(emprunts[i].dateRetour[0]=='\0' || strcmp(emprunts[i].dateRetour,"-")==0){
            int d = diffJours(emprunts[i].dateEmprunt, dateAujourd);
            if(d>30){
                emprunts[i].retard=1;
                nbRetards++;
                printf("• Emprunt #%d Livre:%d Utilisateur:%d Jours:%d -> RETARD\n",
                       emprunts[i].idEmprunt,
                       emprunts[i].idLivre,
                       emprunts[i].idUtilisateur,
                       d);
            }
        }
    }
    if(nbRetards==0) printf("Aucun retard.\n");
}

void getDateAujourdhui(char *date){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, 12, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

