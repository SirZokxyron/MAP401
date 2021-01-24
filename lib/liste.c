#include "../interfaces/liste.h"

/* Fonctions pour gerer la structure liste chainee */

    /* Initialise une cellule avec le point donne */
    cellule * init_cellule(Point p) {
        cellule * cell = (cellule *)malloc(sizeof(cellule));
        cell->p = p;
        return cell; 
    }

    /* Initialise une liste vide */
    void init_liste(liste * L) {
        L->tete = NULL;
        L->queue = NULL;
    }

    /* Ajoute la cellule en bout de liste donne */
    void ajout_en_queue(liste * L, cellule * cell) {
        if (!L->tete) {
            L->tete = cell;
            L->queue = cell;
        } else {
            L->queue->suivant = cell;
            L->queue = cell;
        }
    }

    /*Affiche les elements de la liste chainee L */
    void affiche_liste(liste L) {
        if (L.tete) {
            cellule * cell = L.tete;
            affiche_point(cell->p, "Point : ");
            while (cell->suivant) {
                affiche_point(cell->suivant->p, "Point : ");
                cell = cell->suivant;
            }
        }
    }