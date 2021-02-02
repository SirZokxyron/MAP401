#ifndef _CONTOURS_H_
#define _CONTOURS_H_

#include "../interfaces/geometrie2D.h"
#include "../interfaces/image.h"
#include "../interfaces/robot.h"
#include "../interfaces/liste.h"

/* Fonctions pour determiner le contour d'une image */

    /* Renvoie le pixel de depart selon un algorithme de recherche des contours qui necessite un pixel noir sous-jacent a un pixel blanc */
    Point pos_depart(Image I);

    /* Creer le nom de fichier correct pour la sauvegarde du .contours d'une image */
    string get_fichier_contours(string nom);

    /* Fonction debug */
    void debug_contour(Image I);

    /* Renvoie le contour d'une image passee en argument selon l'algorithme vu en cours */
    void determiner_contour(Image I);

    /* Sauvegarde un contour donne sous forme de liste de point dans un fichier .contours */
    void save_contour(liste L, char * nom);

#endif