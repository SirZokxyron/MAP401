#include "geometrie2D.h"

/* Fonctions pour les points */

    /* Cree le point de coordonnees : (x, y) */
    Point set_point(reel x, reel y) {
        Point P = {x, y};
        return P;
    }

    /* Cree le point issu d'une par un scalaire : s * P */
    Point scal_point(reel s, Point P) {
        return set_point(s * P.x, s * P.y);
    }

    /* Cree le point issu de la somme de deux points : P1 + P2 */
    Point add_point(Point P1, Point P2) {
        return set_point(P1.x + P2.x, P1.y + P2.y);
    }

    /* Cree le point issu de la soustraction de deux points : P1 - P2 */
    Point sub_point(Point P1, Point P2) {
        return add_point(P1, scal_point(-1, P2));
    }

    /* Compare les deux coordonnees de deux points donnes */
    bool compare_point(Point P1, Point P2) {
        return (P1.x == P2.x) && (P1.y == P2.y);
    }

    /* Affiche les coordonnees d'un point derriere un nom specifie */
    void affiche_point(Point P, char *nom) {
        printf("%s : (%lf, %lf)\n", nom, P.x, P.y);
    }

/* Fonctions pour les vecteurs */

    /* Cree le vecteur de coordonnees : (x, y) */
    Vecteur set_vect(reel x, reel y) {
        Vecteur V = {x, y};
        return V;
    }

    /* Cree le vecteur AB */
    Vecteur vect_bipoint(Point A, Point B) {
        return set_vect(B.x - A.x, B.y - A.y);
    }

    /* Cree le point issu d'une par un scalaire : s * U */ 
    Vecteur scal_vect(reel s, Vecteur V) {
        return set_vect(s * V.x, s * V.y);
    }

    /* Cree le vecteur issu de la somme de deux autre vecteurs : V1 + V2*/
    Vecteur add_vect(Vecteur V1, Vecteur V2) {
        return set_vect(V1.x + V2.x, V1.y + V2.y);
    }

    /* Cree le vecteur issu de la soustraction de deux autre vecteurs : V1 - V2 */
    Vecteur sub_vect(Vecteur V1, Vecteur V2) {
        return add_vect(V1, scal_vect(-1, V2));
    }

    /* Affiche les coordonnees d'un vecteur derriere un nom specifie */
    void affiche_vecteur(Vecteur V, char *nom) { 
        printf("%s : (%lf, %lf)\n", nom, V.x, V.y);
    } 