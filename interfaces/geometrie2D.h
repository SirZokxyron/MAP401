#ifndef _GEOMETRIE2D_H_
#define _GEOMETRIE2D_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../interfaces/types_macros.h"

/* Structures de donnees */

    //* Definition d'un nombre reel
    typedef double reel;

    //* Definition point a deux coordonnees reelles
    typedef struct Point_ {
        reel x, y;
    } Point;

    //* Definition bezier2 definie par 3 points
    typedef struct bezier2_ {
        Point C0;
        Point C1;
        Point C2;
    } bezier2;

    //* Definition bezier3 definie par 4 points
    typedef struct bezier3_ {
        Point C0;
        Point C1;
        Point C2;
        Point C3;
    } bezier3;

    //* Definition vecteur a deux coordonnees reelles
    typedef struct Vecteur_ {
        reel x, y;
    } Vecteur;

/* Fonctions pour les points */

    //* Cree le point de coordonnees : (x, y)
    Point set_point(reel x, reel y);

    //* Cree le point issu d'une par un scalaire : s * P
    Point scal_point(reel s, Point P); 

    //* Cree le point issu de la somme de deux points : P1 + P2
    Point add_point(Point P1, Point P2);

    //* Cree le point issu de la soustraction de deux points : P1 - P2
    Point sub_point(Point P1, Point P2);

    //* Compare les deux coordonnees de deux points donnes
    bool compare_point(Point P1, Point P2);

    //* Affiche les coordonnees d'un point derriere un nom specifie
    void affiche_point(Point P, char *nom);

/* Fonction pour les courbes de bezier */

    //* Renvoie C(t) pour une courbe de degre 2
    Point C_deg2(bezier2 bezier, reel t);

    //* Renvoie C(t) pour une courbe de degre 3
    Point C_deg3(bezier3 bezier, reel t);

    //* Convertit une courbe de bezier de degre 2 en degre 3
    bezier3 deg2Vdeg3(bezier2 bezier);

/* Fonctions pour les vecteurs */

    //* Cree le vecteur de coordonnees : (x, y)
    Vecteur set_vect(reel x, reel y);

    //* Cree le vecteur AB
    Vecteur vect_bipoint(Point A, Point B);

    //* Cree le point issu d'une par un scalaire : s * U
    Vecteur scal_vect(reel s, Vecteur V);

    //* Cree le vecteur issu de la somme de deux autre vecteurs : V1 + V
    Vecteur add_vect(Vecteur V1, Vecteur V2);

    //* Cree le vecteur issu de la soustraction de deux autre vecteurs : V1 - V2
    Vecteur sub_vect(Vecteur V1, Vecteur V2);

    //* Renvoie la norme du vecteur V1 
    double norme_vect(Vecteur V1);

    //* Renvoie le produit scalaire de V1 et V2
    double prod_scal_vect(Vecteur V1, Vecteur V2);

    //* Renvoie la distance entre le segment [P1, P2] et le point P3
    double dist_vect_point(Point P1, Point P2, Point P3);

    //* Affiche les coordonnees d'un vecteur derriere un nom specifie
    void affiche_vecteur(Vecteur V, char *nom);

#endif