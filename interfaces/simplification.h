#ifndef _SIMPLIFICATION_H_
#define _SIMPLIFICATION_H_

#include "geometrie2D.h"
#include "image.h"
#include "liste.h"

//* Renvoie la liste contenant les points d'une forme simplifiee par l'algorithme de Douglas Peucker avec une distance seuil d
liste simplification_douglas_peucker(liste C, int j1, int j2, double d);

//* Renvoie d'une courbe de bezier de degre 2 approchant une liste de point
bezier2 approx_bezier2(liste L, int j1, int j2);

//* Renvoie de la simplification d'une liste de point par courbe de bezier2
liste simplification_douglas_peucker_bezier2(liste C, int j1, int j2, reel d);

//* Fonction gamma(k) (cf fonction approx bezier 3)
reel gammaK (reel k, reel n);

//* Renvoie une courbe de bezier de degre 3 approchant une liste de point
bezier3 approx_bezier3(liste L, int j1, int j2);

//* Renvoie de la simplification d'une liste de point par courbe de bezier3
liste simplification_douglas_peucker_bezier3(liste C, int j1, int j2, reel d);


#endif