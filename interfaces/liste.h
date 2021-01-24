#ifndef _LISTE_H_
#define _LISTE_H_

#include "../interfaces/geometrie2D.h"

/* Definition de la structure de donnees liste chainee */

    typedef struct cellule_ cellule;
    typedef struct liste_ liste;

  struct cellule_ {
        Point p;
        cellule * suivant;
    };

   struct liste_ {
        cellule * tete;
        cellule * queue;
    };

/* Fonctions pour gerer la structure liste chainee */

    /* Initialise une cellule avec le point donne */
    cellule * init_cellule(Point p);

    /* Initialise une liste vide */
    void init_liste(liste * L);

    /* Ajoute la cellule en bout de liste donne */
    void ajout_en_queue(liste * L, cellule * cell);

    /* Affiche les elements de la liste chainee L */
    void affiche_liste(liste L);

#endif