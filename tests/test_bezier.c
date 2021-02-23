#include "../interfaces/simplification.h"
#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {
    
    //> Verification du nombre d'arguments
    if (argc != 1) {
        //? une image, un mode (1-3) et une simplification (0-1)
        ERREUR_FATALE("[Erreur]\ttest_bezier/main\tNombre d'argument incorrect, aucun attendus.");
    }

    Point C0 = set_point(0, 0);
    Point C1 = set_point(1, 0);
    Point C2 = set_point(1, 1);
    bezier2 b2 = {C0, C1, C2};

    printf("Bezier de deg2 : \n");
    for(double t = 0; t <= 1; t += 0.1) {
        printf("C(%lf) = ", t);
        affiche_point(C_deg2(b2, t), "Point");
    }

    printf("Bezier de deg3 : \n");
    bezier3 b3 = deg2Vdeg3(b2);
    for(double t = 0; t <= 1; t += 0.1) {
        printf("C(%lf) = ", t);
        affiche_point(C_deg3(b3, t), "Point");
    }

    return 0;
}