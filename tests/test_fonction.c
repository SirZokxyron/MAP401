#include "../interfaces/simplification.h"

int main () {

    liste L;
    
    //> Test fonction approx_bezier2

    //cas n = 1
    Point P0 = set_point(0, 0);
    Point P1 = set_point(1, 1);
    ajout_en_queue(&L, init_cellule(P0));
    ajout_en_queue(&L, init_cellule(P1));
    bezier2 B = approx_bezier2(L);

    affiche_point(P0, "P0");
    affiche_point(P0, "P1");

    affiche_point(B.C0, "C0");
    affiche_point(B.C1, "C1");
    affiche_point(B.C2, "C2");

    /* for(reel t = 0; t <= 1; t += 0.1) {
        printf("C(%lf) = ", t);
        affiche_point(C_deg2(B, t), "Point");
    } */

    return 0;
}