#include "../interfaces/geometrie2D.h"

/* Fonctions pour les points */

    //* Cree le point de coordonnees : (x, y)
    Point set_point(reel x, reel y) {
        Point P = {x, y};
        return P;
    }

    //* Cree le point issu d'une par un scalaire : s * P
    Point scal_point(reel s, Point P) {
        return set_point(s * P.x, s * P.y);
    }

    //* Cree le point issu de la somme de deux points : P1 + P2
    Point add_point(Point P1, Point P2) {
        return set_point(P1.x + P2.x, P1.y + P2.y);
    }

    //* Cree le point issu de la soustraction de deux points : P1 - P2
    Point sub_point(Point P1, Point P2) {
        return add_point(P1, scal_point(-1, P2));
    }

    //* Compare les deux coordonnees de deux points donnes
    bool compare_point(Point P1, Point P2) {
        return (P1.x == P2.x) && (P1.y == P2.y);
    }

    //* Affiche les coordonnees d'un point derriere un nom specifie
    void affiche_point(Point P, char *nom) {
        printf("%s : (%lf, %lf)\n", nom, P.x, P.y);
    }

/* Fonction pour les courbes de bezier */

    //* Definie une courbe de bezier de degre 2
    bezier2 set_bezier2(Point C0, Point C1, Point C2) {
        bezier2 B = {C0, C1, C2};
        return B;
    }

    //* Definie une courbe de bezier de degre 3
    bezier3 set_bezier3(Point C0, Point C1, Point C2, Point C3) {
        bezier3 B = {C0, C1, C2, C3};
        return B;
    }

    //* Renvoie C(t) pour une courbe de degre 2
    Point C_deg2(bezier2 bezier, reel t) {
        Point C10 = add_point(scal_point(1-t, bezier.C0), scal_point(t, bezier.C1));
        Point C11 = add_point(scal_point(1-t, bezier.C1), scal_point(t, bezier.C2));
        Point Ct = add_point(scal_point(1-t, C10), scal_point(t, C11));
        return Ct;
    }

    //* Renvoie C(t) pour une courbe de degre 3
    Point C_deg3(bezier3 bezier, reel t) {
        Point C10 = add_point(scal_point(1-t, bezier.C0), scal_point(t, bezier.C1));
        Point C11 = add_point(scal_point(1-t, bezier.C1), scal_point(t, bezier.C2));
        Point C12 = add_point(scal_point(1-t, bezier.C2), scal_point(t, bezier.C3));
        Point C20 = add_point(scal_point(1-t, C10), scal_point(t, C11));
        Point C21 = add_point(scal_point(1-t, C11), scal_point(t, C12));
        Point Ct = add_point(scal_point(1-t, C20), scal_point(t, C21));
        return Ct;
    }

    //* Convertit une courbe de bezier de degre 2 en degre 3
    bezier3 deg2Vdeg3(bezier2 bezier) {
        Point C0 = bezier.C0;
        Point C1 = add_point(scal_point((1.0/3.0), bezier.C0), scal_point((2.0/3.0), bezier.C1));
        Point C2 = add_point(scal_point((2.0/3.0), bezier.C1), scal_point((1.0/3.0), bezier.C2));
        Point C3 = bezier.C2;
        bezier3 nouv_bezier = {C0, C1, C2, C3};
        return nouv_bezier;
    }

/* Fonctions pour les vecteurs */

    //* Cree le vecteur de coordonnees : (x, y)
    Vecteur set_vect(reel x, reel y) {
        Vecteur V = {x, y};
        return V;
    }

    //* Cree le vecteur AB
    Vecteur vect_bipoint(Point A, Point B) {
        return set_vect(B.x - A.x, B.y - A.y);
    }

    //* Cree le point issu d'une par un scalaire : s * U
    Vecteur scal_vect(reel s, Vecteur V) {
        return set_vect(s * V.x, s * V.y);
    }

    //* Cree le vecteur issu de la somme de deux autre vecteurs : V1 + V
    Vecteur add_vect(Vecteur V1, Vecteur V2) {
        return set_vect(V1.x + V2.x, V1.y + V2.y);
    }

    //* Cree le vecteur issu de la soustraction de deux autre vecteurs : V1 - V2
    Vecteur sub_vect(Vecteur V1, Vecteur V2) {
        return add_vect(V1, scal_vect(-1, V2));
    }

    //* Renvoie la norme du vecteur V1 
    double norme_vect(Vecteur V1) {
        return sqrt(pow(V1.x, 2) + pow(V1.y, 2));
    }

    //* Renvoie le produit scalaire de V1 et V2
    double prod_scal_vect(Vecteur V1, Vecteur V2) {
        return ((V1.x * V2.x) + (V1.y * V2.y));
    }

    //* Renvoie la distance entre le segment [P1, P2] et le point P3
    double dist_vect_point(Point A, Point B, Point P) {
    
        double norme = norme_vect(vect_bipoint(A, B));
        
        //> Cas A == B
        if (norme == 0.0) {
            return (norme_vect(vect_bipoint(A, P)));
        }

        Vecteur AP = vect_bipoint(A, P);
        Vecteur AB = vect_bipoint(A, B);
        //> Cas A != B
        double lambda = prod_scal_vect(AP, AB) / prod_scal_vect(AB, AB);
        if (lambda < 0) {
            return norme_vect(AP);
        } else if (lambda > 1) {
            return norme_vect(vect_bipoint(B, P));
        } else {
            Point Q = add_point(A, scal_point(lambda, sub_point(B, A)));
            return norme_vect(vect_bipoint(Q, P));
        }
    }

    //* Affiche les coordonnees d'un vecteur derriere un nom specifie
    void affiche_vecteur(Vecteur V, char *nom) { 
        printf("%s : (%lf, %lf)\n", nom, V.x, V.y);
    } 