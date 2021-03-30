#include "../interfaces/simplification.h"

//* Renvoie la liste contenant les points d'une forme simplifiee par l'algorithme de Douglas Peucker avec une distance seuil d
liste simplification_douglas_peucker(liste C, int j1, int j2, double d) {
    
    tableau P = liste_V_tableau(C);
    
    double dmax = 0;
    int k = j1;
    for (int j = j1 + 1; j < j2; j++) {
        double dj = dist_vect_point(P.tab[j1], P.tab[j2], P.tab[j]);
        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    liste L;
    init_liste(&L);
    if (dmax <= d) {
        ajout_en_queue(&L, init_cellule(P.tab[j1]));
        ajout_en_queue(&L, init_cellule(P.tab[j2]));
    } else {
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
bezier2 approx_bezier2(liste L, int j1, int j2) {
    tableau t = liste_V_tableau(L);
    bezier2 B;
    Point C0;
    Point C1;
    Point C2;
    reel n = j2 - j1;
    reel alpha;
    reel beta; 
    if (n == 1) {
        C0 = t.tab[j1];
        C2 = t.tab[j2];
        C1 = scal_point(1.0/2.0, add_point(C0, C2));
        B = set_bezier2(C0, C1, C2);
    } else {
        alpha = (3.0 * n) / ((n * n) - 1.0);            
        beta = (1.0 - (2.0 * n)) / (2.0 * (n + 1.0));   
        C0 = t.tab[j1];
        C2 = t.tab[j2];
        Point C_tmp = set_point(0.0, 0.0);
        for(int i = 1; i <= n - 1; i++) {
            C_tmp = add_point(C_tmp, t.tab[j1 + i]);
        }
        C1 = add_point(scal_point(alpha, C_tmp), scal_point(beta, add_point(C0, C2)));
        B = set_bezier2(C0, C1, C2);
    } 
    
    return B;
}

liste simplification_douglas_peucker_bezier2(liste C, int j1, int j2, reel d) {

    liste L;
    init_liste(&L);

    tableau t = liste_V_tableau(C);

    int n = j2 - j1;
    reel n_r = (reel)n;
    int i;
    reel t_i;
    reel d_j;

    bezier2 B = approx_bezier2(C, j1, j2);

    reel dmax = 0.0; 
    int k = j1;
    for (int j = j1 + 1; j <= j2; j++) {
        i = j - j1;
        t_i = (reel)i/n_r;
        d_j = distance_point_bezier2(t.tab[j], B, t_i);
        if (dmax < d_j) {
            dmax = d_j;
            k = j;
        }
    }

    if (dmax <= d) {
        ajout_en_queue(&L, init_cellule(B.C0));
        ajout_en_queue(&L, init_cellule(B.C1));
        ajout_en_queue(&L, init_cellule(B.C2));
    } else {
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