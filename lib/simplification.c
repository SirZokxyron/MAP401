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