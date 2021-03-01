#include "../interfaces/geometrie2D.h"

int main () {

    reel x, y;
    printf("Point P :\n");
    printf("\tx = ");
    scanf("%lf%*c", &x);
    printf("\ty = ");
    scanf("%lf%*c", &y);
    Point P = set_point(x, y);

    printf("Point A :\n");
    printf("\tx = ");
    scanf("%lf%*c", &x);
    printf("\ty = ");
    scanf("%lf%*c", &y);
    Point A = set_point(x, y);

    printf("Point B :\n");
    printf("\tx = ");
    scanf("%lf%*c", &x);
    printf("\ty = ");
    scanf("%lf%*c", &y);
    Point B = set_point(x, y);

    //> Test du calcul de la distance segment - point
    printf("Distance [A, B] et P : %lf\n", dist_vect_point(A, B, P));

    return 0;
}