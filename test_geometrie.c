#include "geometrie2D.h"

int main () {

    // Creation des points A et B de coordonnees particulieres
    Point A = set_point(0, 1);
    Point B = set_point(1, 0);

    // Affichage des points A et B
    affiche_point(A, "Point A");
    affiche_point(B, "Point B");
    
    // Affichage des points resultant respectivement de la somme puis de deux soustractions des points A et B
    affiche_point(add_point(A, B), "Point A + B");
    affiche_point(sub_point(A, B), "Point A - B");
    affiche_point(sub_point(B, A), "Point B - A");

    // Creation des vecteurs BA et AB
    Vecteur U = vect_bipoint(B, A);
    Vecteur V = vect_bipoint(A, B);

    // Affichage des vecteurs resultant respectivement de la somme puis de la soustraction de BA et AB
    affiche_vecteur(add_vect(U, V), "Vecteur AB + BA");
    affiche_vecteur(sub_vect(U, V), "Vecteur BA - AB");

    return 0;
}

