#ifndef _CONTOURS_H_
#define _CONTOURS_H_

#include "geometrie2D.h"
#include "image.h"
#include "robot.h"

/* Fonctions pour determiner le contour d'une image */

    /* Renvoie le pixel de depart selon un algorithme de recherche des contours qui necessite un pixel noir sous-jacent a un pixel blanc */
    Point pos_depart(Image I);

    /* Renvoie le contour d'une image passee en argument selon l'algorithme vu en cours */
    void determiner_contour(Image I);

#endif