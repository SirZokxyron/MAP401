#include "../interfaces/simplification.h"

//* Renvoie la liste contenant les points d'une forme simplifiee par l'algorithme de Douglas Peucker avec une distance seuil d
liste simplification_douglas_peucker(tableau C, int j1, int j2, double d) {
    
    //> On cherche la distance max entre un point de notre contour et le segment
    double dmax = 0;
    int k = j1;
    for (int j = j1 + 1; j < j2; j++) {
        double dj = dist_vect_point(C.tab[j1], C.tab[j2], C.tab[j]);
        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    liste L;
    init_liste(&L);
    //> Si la distance max est en dessous de la distance seuil alors on simplifie par le premier et dernier point
    if (dmax <= d) {
        ajout_en_queue(&L, init_cellule(C.tab[j1]));
        ajout_en_queue(&L, init_cellule(C.tab[j2]));
    } 
    //> Si la distance max est au dessus de la distance seuil alors on divise le problème en deux
    else {
        liste L1 = simplification_douglas_peucker(C, j1, k, d);
        liste L2 = simplification_douglas_peucker(C, k, j2, d); 
        //> On evite la duplication de points dans notre fichier .contours
        L2.tete = L2.tete->suivant;
        L2.taille--;
        L = concat_liste(L1, L2);
    }

    return L;
}

//* Renvoie une courbe de bezier de degre 2 approchant une liste de point
bezier2 approx_bezier2(tableau L, int j1, int j2) {
    
    bezier2 B;
    Point C0;
    Point C1;
    Point C2;
    reel n = j2 - j1;
    reel alpha;
    reel beta; 
    //> Cas ou il n'y a que deux point -> simplification par bezier de degre 1
    if (n == 1) {
        C0 = L.tab[j1];
        C2 = L.tab[j2];
        //> Calcul de C1 qui est le milieu de [C0, C2]
        C1 = scal_point(1.0/2.0, add_point(C0, C2));
        //> On initialise la courbe de bezier finale
        B = set_bezier2(C0, C1, C2);
    } 
    //> Cas ou il y a plus que 2 points -> simplification par bezier de degre 2
    else {
        //> Calcul des constantes alpha et beta
        alpha = (3.0 * n) / ((n * n) - 1.0);            
        beta = (1.0 - (2.0 * n)) / (2.0 * (n + 1.0));   
        C0 = L.tab[j1];
        C2 = L.tab[j2];
        Point C_tmp = set_point(0.0, 0.0);
        for(int i = 1; i <= n - 1; i++) {
            C_tmp = add_point(C_tmp, L.tab[j1 + i]);
        }
        //> Calcul de C1 en utilisant alpha et beta
        C1 = add_point(scal_point(alpha, C_tmp), scal_point(beta, add_point(C0, C2)));
        //> On initialise la courbe de bezier finale
        B = set_bezier2(C0, C1, C2);
    }

    return B;
}

//* Fonction gamma(k) (cf fonction approx bezier 3)
reel gammaK (reel k, reel n) {
    return 6 * pow(k,4) - 8 * n * pow(k,3) + 6 * pow(k,2) - 4 * n * k + pow(n,4) - pow(n,2);
}

//* Renvoie une courbe de bezier de degre 3 approchant une liste de point
bezier3 approx_bezier3(tableau L, int j1, int j2) {
    bezier3 B;
    Point C0, C1, C2, C3;
    reel n = j2 - j1;
    reel alpha, beta, lambda;

    //> Si le nombre de point est inferieur a 4 -> on se ramene a une simplification de degre 2
    if (n < 3) {
        B = deg2Vdeg3(approx_bezier2(L, j1, j2));
    } 
    //> Si le nombre de point est egal ou superieur a 4 -> on simplifie par courbe de bezier de degre 3
    else {
        //> Calcul des constantes alpha, beta et lambda
        alpha = (-15*pow(n,3) + 5*pow(n,2) + 2*n + 4)/(3*(n+2)*(3*pow(n,2)+1));
        beta = (10*pow(n,3)-15*pow(n,2)+n+2)/(3*(n+2)*(3*pow(n,2)+1));
        lambda = (70*n)/(3*(pow(n,2)-1)*(pow(n,2)-4)*(3*pow(n,2)+1));

        //> Initialisation des points C0 et C3
        C0 = L.tab[j1];
        C3 = L.tab[j2];
        Point C_tmp1 = set_point(0.0, 0.0);
        Point C_tmp2 = set_point(0.0, 0.0);

        for (int i = 1; i <= n-1; i++) {
            C_tmp1 = add_point(C_tmp1, scal_point(gammaK(i,n), L.tab[j1+i]));
            C_tmp2 = add_point(C_tmp2, scal_point(gammaK(n-i,n), L.tab[j1+i]));
        }

        //> Calcul de C1 et C2 en utilisant les formules donnees
        C1 = add_point(scal_point(alpha, L.tab[j1]), add_point(scal_point(lambda, C_tmp1), scal_point(beta,L.tab[j2]))); 
        C2 = add_point(scal_point(beta, L.tab[j1]), add_point(scal_point(lambda, C_tmp2), scal_point(alpha,L.tab[j2]))); 
        
        //> On initialise la courbe de bezier finale
        B = set_bezier3(C0, C1, C2, C3);
    }

    return B;
}

liste simplification_douglas_peucker_bezier2(tableau C, int j1, int j2, reel d) {

    liste L;
    init_liste(&L);

    int n = j2 - j1;
    reel n_r = (reel)n;
    int i;
    reel t_i;
    reel d_j;

    bezier2 B = approx_bezier2(C, j1, j2);

    //> On cherche la distance max entre un point de notre contour et l'approximation de la courbe de bezier 2
    reel dmax = 0.0; 
    int k = j1;
    for (int j = j1 + 1; j <= j2; j++) {
        i = j - j1;
        t_i = (reel)i/n_r;
        d_j = distance_point_bezier2(C.tab[j], B, t_i);
        if (dmax < d_j) {
            dmax = d_j;
            k = j;
        }
    }

    //> Si la distance max est en dessous de la distance seuil alors on simplifie par une courbe de bezier de degre 2
    if (dmax <= d) {
        ajout_en_queue(&L, init_cellule(B.C0));
        ajout_en_queue(&L, init_cellule(B.C1));
        ajout_en_queue(&L, init_cellule(B.C2));
    } 
    //> Si la distance max est au dessus de la distance seuil alors on divise le problème en deux
    else {
        liste L1;
        init_liste(&L1);
        L1 = simplification_douglas_peucker_bezier2(C, j1, k, d);
        liste L2;
        init_liste(&L2);
        L2 = simplification_douglas_peucker_bezier2(C, k, j2, d);
        L = concat_liste(L1, L2);
    }

    return L;
}

liste simplification_douglas_peucker_bezier3(tableau C, int j1, int j2, reel d) {

    liste L;
    init_liste(&L);

    int n = j2 - j1;
    reel n_r = (reel)n;
    int i;
    reel t_i;
    reel d_j;

    bezier3 B = approx_bezier3(C, j1, j2);

    //> On cherche la distance max entre un point de notre contour et l'approximation de la courbe de bezier 2
    reel dmax = 0.0; 
    int k = j1;
    for (int j = j1 + 1; j <= j2; j++) {
        i = j - j1;
        t_i = (reel)i/n_r;
        d_j = distance_point_bezier3(C.tab[j], B, t_i);
        if (dmax < d_j) {
            dmax = d_j;
            k = j;
        }
    }

    //> Si la distance max est en dessous de la distance seuil alors on simplifie par une courbe de bezier de degre 3
    if (dmax <= d) {
        ajout_en_queue(&L, init_cellule(B.C0));
        ajout_en_queue(&L, init_cellule(B.C1));
        ajout_en_queue(&L, init_cellule(B.C2));
        ajout_en_queue(&L, init_cellule(B.C3));
    } 
    //> Si la distance max est au dessus de la distance seuil alors on divise le problème en deux
    else {
        liste L1;
        init_liste(&L1);
        L1 = simplification_douglas_peucker_bezier3(C, j1, k, d);
        liste L2;
        init_liste(&L2);
        L2 = simplification_douglas_peucker_bezier3(C, k, j2, d);
        L = concat_liste(L1, L2);
    }

    return L;
}