## Projet ALGO C ING3 
## RÉSUMÉ – Quel est le contexte et la problématique du projet ? 
Ce projet est une application de gestion de bibliothèque réalisée en C, intégrant une interface graphique.
L’objectif est de permettre à un utilisateur de gérer :

- Les livres 
- Les adhérents 
- Les emprunts

Le tout via une interface intuitive avec boutons, menus
## Quels sont les objectifs techniques ? 
Sur le plan technique, il s'agissait de concevoir un modèle relationnel avec MCD et MLD, de développer une application C modulaire en manipulant structures, pointeurs et fichiers, et de gérer toutes les entités du système. L’équipe a aussi ajouté des fonctionnalités avancées, comme des statistiques sur les emprunts, pour rendre l’application plus complète. Pour le développement, CLion a été utilisé pour le code et MySQL pour la base de données

## Structure du projet

```
bibliothequeconsole/
│── CMakeLists.txt
│── README.md
│
├── include/
│   ├── livres.h
│   ├── utilisateurs.h
│   ├── emprunts.h
│   ├── fichiers.h
│   ├── stats.h
│   └── utils.h
│
├── src/
│   ├── main.c
│   ├── livres.c
│   ├── utilisateurs.c
│   ├── emprunts.c
│   ├── fichiers.c
│   ├── stats.c
│   └── utils.c
│
└── data/
    ├── livres.txt
    ├── utilisateurs.txt
    └── emprunts.txt
```


include/ → contient tous les fichiers .h (déclarations, structures, prototypes)

src/ → contient les implémentations .c

data/ → contient les fichiers textes

## Fonctionnalités
### Gestion des livres

- Ajouter un livre 
- Supprimer un livre

### Gestion des membres

- Ajouter un membre 
- Supprimer un membre

### Gestion des emprunts

- Voir tous les emprunts en cours

### Interface graphique

- Menus visuels 
- Boutons d’action 
- Champs de saisie validés 
- Fenêtres dédiées pour chaque opération

## Améliorations futures

- Ajouter/supprimer un emprunt
- Mettre fonctionnalités optionnelles

## Auteurs
### Marie VIRICEL
### Eloise PIERRON
### James FOTSO