#include "../interfaces/simplification.h"

int main () {

    liste L;
    
    //> Test fonction approx_bezier2

    Point Q0 = set_point(0, 0);
    Point Q1 = set_point(1, 0);
    Point Q2 = set_point(1, 1);
    Point Q3 = set_point(1, 2);
    Point Q4 = set_point(2, 2);
    Point Q5 = set_point(3, 2);
    Point Q6 = set_point(3, 3);
    Point Q7 = set_point(4, 3);
    Point Q8 = set_point(5, 3);

    ajout_en_queue(&L, init_cellule(Q0));
    ajout_en_queue(&L, init_cellule(Q1));
    ajout_en_queue(&L, init_cellule(Q2));
    ajout_en_queue(&L, init_cellule(Q3));
    ajout_en_queue(&L, init_cellule(Q4));
    ajout_en_queue(&L, init_cellule(Q5));
    ajout_en_queue(&L, init_cellule(Q6));
    ajout_en_queue(&L, init_cellule(Q7));
    ajout_en_queue(&L, init_cellule(Q8));
    bezier2 B = approx_bezier2(L, 0, 8);

  /* affiche_point(P0, "P0");
    affiche_point(P1, "P1");
    affiche_point(P2, "P2"); */

    affiche_point(B.C0, "C0");
    affiche_point(B.C1, "C1");
    affiche_point(B.C2, "C2");

    /* for(reel t = 0; t <= 1; t += 0.1) {
        printf("C(%lf) = ", t);
        affiche_point(C_deg2(B, t), "Point");
    } */

    return 0;
}