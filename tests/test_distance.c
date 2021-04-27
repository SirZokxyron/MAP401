#include "../interfaces/geometrie2D.h"

int main () {

    reel x, y;

    //> Initialisation du point P
    printf("Point P :\n");
    printf("\tx = ");
    scanf("%lf%*c", &x);
    printf("\ty = ");
    scanf("%lf%*c", &y);
    Point P = set_point(x, y);

    //> Initialisation du point A
    printf("Point A :\n");
    printf("\tx = ");
    scanf("%lf%*c", &x);
    printf("\ty = ");
    scanf("%lf%*c", &y);
    Point A = set_point(x, y);

    //> Initialisation du point B
    printf("Point B :\n");
    printf("\tx = ");
    scanf("%lf%*c", &x);
    printf("\ty = ");
    scanf("%lf%*c", &y);
    Point B = set_point(x, y);

    //> Test du calcul de la distance [A, B] et P
    printf("Distance [A, B] et P : %lf\n", dist_vect_point(A, B, P));

    return 0;
}