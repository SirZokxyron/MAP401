#ifndef _LISTE_H_
#define _LISTE_H_

#include "../interfaces/geometrie2D.h"

/* Differentes structures de donnees */

    /* Definition de la structure de liste chainee */

    typedef struct cellule_ cellule;
    typedef struct liste_ liste;

    struct cellule_ {
        Point p;
        cellule * suivant;
    };

    struct liste_ {
        unsigned int taille;
        cellule * tete;
        cellule * queue;
    };

    /* Definition de la structure du tableau de point */

    typedef struct tableau_ {
		unsigned int taille;
		Point *tab;
	} tableau;

/* Fonctions pour gerer la structure liste chainee */

    /* Initialise une cellule avec le point donne */
    cellule * init_cellule(Point p);

    /* Initialise une liste vide */
    void init_liste(liste * L);

    /* Ajoute la cellule en bout de liste donne */
    void ajout_en_queue(liste * L, cellule * cell);

    /* Supprime la liste chainee L */
    void supprimer_liste(liste * L);

    /* Concatene L2 a la suite de L1, renvoie L1 modifiee */
    liste concat_liste(liste L1, liste L2);

    /* Convertit une liste chainee en un tableau de point */
    tableau liste_V_tableau(liste L);

    /* Affiche le contour d'une image a l'ecran */
    void ecrire_contour(liste L);

#endif