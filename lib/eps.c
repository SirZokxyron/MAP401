#include "../interfaces/eps.h"

//* Modifie les coordonnees d'un point pour le format .eps
Point repare_point(Image I, Point A) {
    //> On inverse le sens des ordonnees
    Point nouveau_A = set_point(A.x, ((double)hauteur_image(I) - A.y));
    return nouveau_A;
}

//* Renvoie la commande .eps pour le header du fichier
string header() {
    string commande = "%!PS-Adobe-3.0 EPSF-3.0\n";
    return commande;
}

//* Renvoie la commande .eps pour configurer les dimensions du fichier
string bounding_box(int Xmin, int Ymin, int Xmax, int Ymax) {
    string commande = (string)malloc(64);
    sprintf(commande, "%%%%BoundingBox: %d %d %d %d\n\n", Xmin, Ymin, Xmax, Ymax);
    return commande;
}

//* Renvoie la commande .eps pour ouvrir la creation d'un nouveau trace
string nouvel_objet() {
    string commande = "newpath\n";
    return commande;
}

//* Renvoie la commande .eps pour fermer la creation du tracer en cours
string finir_objet() {
    string commande = "closepath\n";
    return commande;
}

//* Renvoie la commande .eps pour positionner la "mine de crayon" au coordonnees de A
string positionner(Point A) {
    string commande = (string)malloc(64);
    int x = (int)A.x;
    int y = (int)A.y;
    sprintf(commande, "%d %d moveto\n", x, y);
    return commande;
}

//* Renvoie la commande .eps pour tracer une ligne depuis la position de la "mine de crayon" jusqu'au point A
string creer_segment(Point A) {
    string commande = (string)malloc(64);
    int x = (int)A.x;
    int y = (int)A.y;
    sprintf(commande, "%d %d lineto\n", x, y);
    return commande;
}

//* Renvoie la commande .eps pour tracer un point au point A de rayon r
string creer_point(Point A, float r) {
    string commande = (string)malloc(128);
    int x = (int)A.x;
    int y = (int)A.y;
    sprintf(commande, "%s%d %d %f 0 360 arc\n%s%s%s", nouvel_objet(), x, y, r, finir_objet(), set_graphics(255, 0, 255, 0.1), remplir());
    return commande;
}

//* Renvoie la commande .eps pour tracer une courbe de bezier
string creer_bezier(bezier3 B) {
    string commande = (string)malloc(128);
    sprintf(commande, "%lf %lf %lf %lf %lf %lf curveto\n", B.C1.x, B.C1.y, B.C2.x, B.C2.y, B.C3.x, B.C3.y);
    return commande;
}

//* Renvoie la commande .eps pour initialiser les parametres de traces
string set_graphics(int R, int G, int B, float epaisseur) {
    string commande = (string)malloc(64);
    sprintf(commande, "%d %d %d setrgbcolor %.1f setlinewidth\n", R, G, B, epaisseur);
    return commande;
}

//* Renvoie la commande .eps pour tracer toutes les instructions donnees
string tracer() {
    string commande = "stroke\n\n";
    return commande;
}

//* Renvoie la commande .eps pour remplir la forme fermee en fonction des instructions donnee
string remplir() {
    string commande = "fill\n\n";
    return commande;
}

//* Renvoie la commande .eps pour afficher l'image construite
string affiche_eps() {
    string commande = "showpage\n";
    return commande;
}

//* Renvoie le nom d'un fichier .eps correspondant a une image donnee
string get_fichier_eps(string nom, int mode) {
    
    //> Ajout du e ".eps" a la fin du nom
    string suffixe = ".eps";
    string temp = (string)malloc(3 + strlen(nom) + strlen(suffixe));
    sprintf(temp, "%s_%d%s", nom, mode, suffixe);

    //> Ajout du prefixe "build/" au debut du nom
    string prefixe = "build/";
    string nom_f = (string)malloc(1 + strlen(prefixe) + strlen(temp));
    sprintf(nom_f, "%s%s", prefixe, temp);

    return nom_f;
}

//* Cree le fichier .eps du contour d'une image donnee (differents modes possible) 
//* 1 - Contour avec segments
//* 2 - Contour avec segments et points
//* 3 - Contour et remplissage de la forme detouree
void creer_eps(Image I, int mode) {
    
    //> Recuperation du fichier .contours
    string fichier_contour = get_fichier_contours(I.nom);
    FILE * fichierContour = fopen(fichier_contour, "r");
    if (!fichierContour) ERREUR_FATALE("[Erreur]\tcreer_eps\tFichier .contours non trouve.");

    //> Creation du fichier .eps
    string fichier_eps = get_fichier_eps(I.nom, mode);
    FILE * fichierEps = fopen(fichier_eps, "w");

    fprintf(fichierEps, "%s", header());
    fprintf(fichierEps, "%s", bounding_box(-1, -1, largeur_image(I) + 1, hauteur_image(I) + 1));

    //> false - en attente du start pos, true - start pos trouve
    bool flag_start = false;

    Point prev;     //? Mode 2 : On creer un point precedent

    //> On recupere le nombre de contours
    int nb_contours;
    fscanf(fichierContour, "%d", &nb_contours);
    //> On itere sur chaque contour
    for (int contours_i = 0; contours_i < nb_contours; contours_i++) {
        //? Mode 1 : On cree un nouvel objet, pour terminer proprement la jonction entre le premier et dernier segment
        if (mode == 1) fprintf(fichierEps, "%s", nouvel_objet());
        
        //> On recupere le nombre de points
        int nb_points;
        fscanf(fichierContour, "%d", &nb_points);
        //> On itere sur chaque point
        for (int point_i = 0; point_i < nb_points; point_i++) {

            //> On recupere les coordonnees du prochains point
            double x = 0.0; 
            double y = 0.0;
            fscanf(fichierContour, "%lf %lf", &x, &y);

            //> On inverse l'axe des ordonnee pour ce point
            Point A = repare_point(I, set_point(x, y));

            //> Si c'est le premier point :
            if (!flag_start) {
                //> Alors on donne une instruction de deplacement
                fprintf(fichierEps, "%s", positionner(A));
                flag_start = true;
            } else {
                //> Sinon, on donne une instruction de creer un segment
                fprintf(fichierEps, "%s", creer_segment(A));
                if (mode == 2) {
                    //? Mode 2 : On trace le trait tout de suite
                    fprintf(fichierEps, "%s", set_graphics(0, 0, 0, 0.1));
                    fprintf(fichierEps, "%s", tracer());
                    //? Mode 2 : On dessine un cercle au point precedent
                    fprintf(fichierEps, "%s", creer_point(prev, 0.2));
                    //? On re-deplace le curseur au point actuel
                    fprintf(fichierEps, "%s", positionner(A));
                }
            }
            //> On actualise le point precedemment
            prev = A;
        }
       
        if (mode == 1) {
            //? Mode 1 : On trace tout le contour
            fprintf(fichierEps, "%s", finir_objet());
            fprintf(fichierEps, "%s", set_graphics(0, 0, 0, 0.1));
            fprintf(fichierEps, "%s", tracer());
        } else if (mode == 2) {
            //? Mode 2 : On cree le dernier cercle
            fprintf(fichierEps, "%s", creer_point(prev, 0.2));
        }       
    
        //> On change qu'on est plus au premier point
        flag_start = false;
    } 

    if (mode == 3) { 
        //? Mode 3 : On rempli les formes
        fprintf(fichierEps, "%s", set_graphics(0, 0, 0, 0.1));
        fprintf(fichierEps, "%s", remplir());
    }

    //> On termine le formet .eps et on ferme les fichiers
    fprintf(fichierEps, "%s", affiche_eps());
    fclose(fichierEps);
    fclose(fichierContour);
}

//* Cree le fichier .eps du contour d'une image simplifiee par Bezier
void creer_eps_bezier(Image I, int deg, int mode) {

    bool flag_start = false;
    
    //> Recuperation du fichier .contours
    string fichier_contour = get_fichier_contours(I.nom);
    FILE * fichierContour = fopen(fichier_contour, "r");
    if (!fichierContour) ERREUR_FATALE("[Erreur]\tcreer_eps_bezier\tFichier .contours non trouve.");

    //> Creation du fichier .eps
    string fichier_eps = get_fichier_eps(I.nom, mode);
    FILE * fichierEps = fopen(fichier_eps, "w");

    fprintf(fichierEps, "%s", header());
    fprintf(fichierEps, "%s", bounding_box(-5, -5, largeur_image(I) + 5, hauteur_image(I) + 5));

    //> On recupere le nombre de contours
    int nb_contours;
    fscanf(fichierContour, "%d", &nb_contours);
    for (int contours_i = 0; contours_i < nb_contours; contours_i++) {
        //> On cree un nouvel objet
        //fprintf(fichierEps, "%s", nouvel_objet());
        //> On recupere le nombre de points
        int nb_points;
        fscanf(fichierContour, "%d", &nb_points);
        //> On itere sur chaque bezier
        for (int point_i = 0; point_i < nb_points/(deg + 1); point_i++) {

            //> On recupere les coordonnees des 3 prochains points
            double x0 = 0.0; double y0 = 0.0; fscanf(fichierContour, "%lf %lf", &x0, &y0); Point P0 = repare_point(I, set_point(x0, y0));
            double x1 = 0.0; double y1 = 0.0; fscanf(fichierContour, "%lf %lf", &x1, &y1); Point P1 = repare_point(I, set_point(x1, y1));
            double x2 = 0.0; double y2 = 0.0; fscanf(fichierContour, "%lf %lf", &x2, &y2); Point P2 = repare_point(I, set_point(x2, y2));
            double x3, y3; Point P3; bezier2 B2; bezier3 B3;
            if (deg == 3) {
                x3 = 0.0; y3 = 0.0; fscanf(fichierContour, "%lf %lf", &x3, &y3); P3 = repare_point(I, set_point(x3, y3));
                B3 = set_bezier3(P0, P1, P2, P3);
            } else {
                B2 = set_bezier2(P0, P1, P2);
                B3 = deg2Vdeg3(B2);
            }

            //> On positionne a C0
            if (flag_start == false) {
                fprintf(fichierEps, "%s", positionner(B3.C0));
                flag_start = true;
            }

            //> On trace la courbe de bezier
            fprintf(fichierEps, "%s", creer_bezier(B3));
        }
        //fprintf(fichierEps, "%s", finir_objet());
        flag_start = false;
    }
    
    if (mode == 1) {
        //? Mode 1 : On trace tout le contour
        fprintf(fichierEps, "%s", set_graphics(0, 0, 0, 0.1));
        fprintf(fichierEps, "%s", tracer());
    }

    if (mode == 3) { 
        //? Mode 3 : On remplit les formes
        fprintf(fichierEps, "%s", set_graphics(0, 0, 0, 0.1));
        fprintf(fichierEps, "%s", remplir());
    }

    //> On termine le formet .eps et on ferme les fichiers
    fprintf(fichierEps, "%s", affiche_eps());
    fclose(fichierEps);
    fclose(fichierContour);
}

