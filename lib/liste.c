#include "../interfaces/liste.h"

/* Fonctions pour gerer la structure liste chainee */

    //* Initialise une cellule avec le point donne
    cellule * init_cellule(Point p) {
        cellule * cell = (cellule *)malloc(sizeof(cellule));
        cell->p = p;
        cell->suivant = NULL;
        return cell; 
    }

    //* Initialise une liste vide
    void init_liste(liste * L) {
        L->taille = 0;
        L->tete = NULL;
        L->queue = NULL;
    }

    //* Ajoute la cellule en bout de liste donne
    void ajout_en_queue(liste * L, cellule * cell) {
        if (!L->taille) {
            L->tete = cell;
            L->queue = cell;
        } else {
            L->queue->suivant = cell;
            L->queue = cell;
        }
        L->taille++;
    }

    //* Supprime la liste chainee L
    void supprimer_liste(liste * L) {
        cellule * cell = L->tete;
        while (cell) {
            cellule * cell_suiv = cell->suivant;
            free(cell);
            cell = cell_suiv;
        }
        init_liste(L);
    }

    //* Concatene L2 a la suite de L1, renvoie L1 modifiee
    liste concat_liste(liste L1, liste L2) {
        if (L1.taille == 0) return L2; 
		if (L2.taille == 0) return L1;

        L1.queue->suivant = L2.tete;
        L1.queue = L2.queue;
        L1.taille += L2.taille;
        return L1;
    }

    //* Convertit une liste chainee en un tableau de point
    tableau liste_V_tableau(liste L) {
        tableau T;
        T.taille = L.taille;
        T.tab = malloc(sizeof(Point) * T.taille);

        int k = 0;
        cellule * cell = L.tete;
        while (cell) {
            T.tab[k] = cell->p;
            k++;
            cell = cell->suivant;
        }
        
        return T;
    }

    //* Affiche le contour d'une image a l'ecran
    void ecrire_contour(liste L) {
        tableau T = liste_V_tableau(L);
        int k;
        int nb_points = T.taille;
        Point P;

        printf("%d points : [\n", nb_points);
        for (k = 0; k < nb_points; k++) {
            P = T.tab[k];
            printf("\t(%5.1f, %5.1f)\n", P.x, P.y);
        }
        printf("]\n");

        free(T.tab);
    }