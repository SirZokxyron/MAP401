#ifndef _SIMPLIFICATION_H_
#define _SIMPLIFICATION_H_

#include "geometrie2D.h"
#include "image.h"
#include "liste.h"

//* Renvoie la liste contenant les points d'une forme simplifiee par l'algorithme de Douglas Peucker avec une distance seuil d
liste simplification_douglas_peucker(liste C, int j1, int j2, double d);

#endif