#include "../interfaces/geometrie2D.h"

int main () {

    //> Creation des points A et B de coordonnees particulieres
    Point A = set_point(0, 1);
    Point B = set_point(1, 0);

    //> Affichage des points A et B
    affiche_point(A, "Point A");
    affiche_point(B, "Point B");
    
    //> Affichage des points resultant respectivement de la somme puis de deux soustractions des points A et B
    affiche_point(add_point(A, B), "Point A + B");
    affiche_point(sub_point(A, B), "Point A - B");
    affiche_point(sub_point(B, A), "Point B - A");

    //> Creation des vecteurs BA et AB
    Vecteur V1 = vect_bipoint(B, A);
    Vecteur V2 = vect_bipoint(A, B);

    //> Affichage des vecteurs BA et AB
    affiche_vecteur(V1, "Vecteur BA");
    affiche_vecteur(V2, "Vecteur AB");

    //> Affichage des vecteurs resultant respectivement de la somme puis de la soustraction de BA et AB
    affiche_vecteur(add_vect(V1, V2), "Vecteur AB + BA");
    affiche_vecteur(sub_vect(V1, V2), "Vecteur BA - AB");

    //> Affiche de la norme des vecteurs AB et BA
    printf("Norme de AB : %lf\n", norme_vect(V1));
    printf("Norme de BA : %lf\n", norme_vect(V2));
    
    //> Test du calcul de la distance segment - point
    Point A2 = set_point(0, 0);
    Point B2 = set_point(1, 0);
    Point P1 = set_point(-1, 1);
    Point P2 = set_point(0, 1);
    Point P3 = set_point(0.5, 1);
    Point P4 = set_point(1, 1);
    Point P5 = set_point(2, 1);
    Point P6 = set_point(1, 0);
    printf("Distance [A2, B2] et P1 : %lf\n", dist_vect_point(A2, B2, P1));     //> Nous renvoie bien : Racine de 2
    printf("Distance [A2, B2] et P2 : %lf\n", dist_vect_point(A2, B2, P2));     //> Nous renvoie bien : 1
    printf("Distance [A2, B2] et P3 : %lf\n", dist_vect_point(A2, B2, P3));     //> Nous renvoie bien : 1
    printf("Distance [A2, B2] et P4 : %lf\n", dist_vect_point(A2, B2, P4));     //> Nous renvoie bien : 1
    printf("Distance [A2, B2] et P5 : %lf\n", dist_vect_point(A2, B2, P5));     //> Nous renvoie bien : Racine de 2
    printf("Distance [A2, B2] et P6 : %lf\n", dist_vect_point(A2, B2, P6));     //> Nous renvoie bien : 0
    printf("Distance [A2, A2] et P1 : %lf\n", dist_vect_point(A2, A2, P1));     //> Nous renvoie bien : Racine de 2
    return 0;
}