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
bezier2 approx_bezier2(liste L) {
    tableau t = liste_V_tableau(L);
    bezier2 B;
    Point C0;
    Point C1;
    Point C2;
    Point numerateur;
    reel denominateur;
    reel Ti;
    reel Wi;
    int n;
    switch (t.taille) {
        case 1:
            C0 = t.tab[0];
            C2 = t.tab[2];
            C1 = scal_point(1.0/2.0, add_point(C0, C2));
            B = set_bezier2(C0, C1, C2);
            return B;
        default:
            n = t.taille - 1;
            C0 = t.tab[0];
            C2 = t.tab[n];
            numerateur = set_point(0, 0);
            denominateur = 0;
            for(int i = 1; i <= (reel)n - 1; i++) {
                Ti = (reel)i / (reel)n;
                Wi = 2 * Ti * (1 - Ti);
                numerateur = add_point(numerateur, (sub_point(t.tab[i], scal_point(pow((1 - Ti), 2), C0)), scal_point(pow(Ti, 2), C2)));
                denominateur += Wi;
            }
            C1 = scal_point(1 / denominateur, numerateur);
            B = set_bezier2(C0, C1, C2);
            return B;
    }
}