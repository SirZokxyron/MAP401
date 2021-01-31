#ifndef _EPS_H_
#define _EPS_H_

#include "../interfaces/robot.h"

/*
header : 
    %!PS-Adobe-3.0 EPSF-3.0
bounding box : 
    %%BoundingBox : xmin ymin xmax ymax
instructions on how to draw that crap
showpage
*/ 

/* Modifie les coordonnees d'un point pour le format .eps */
Point repare_point(Image I, Point A);

/* Renvoie la commande .eps pour le header du fichier */
string header();

/* Renvoie la commande .eps pour configurer les dimensions du fichier */
string bounding_box(int Xmin, int Ymin, int Xmax, int Ymax);

/* Renvoie la commande .eps pour ouvrir la creation d'un nouveau trace */
string nouvel_objet();

/* Renvoie la commande .eps pour fermer la creation du tracer en cours */
string finir_objet();

/* Renvoie la commande .eps pour positionner la "mine de crayon" au coordonnees de A */
string positionner(Point A);

/* Renvoie la commande .eps pour tracer une ligne depuis la position de la "mine de crayon" jusqu'au point A */
string creer_segment(Point A);

/* Renvoie la commande .eps pour tracer un point au point A de rayon r */
string creer_point(Point A, float r);

/* Renvoie la commande .eps pour initialiser les parametres de traces */
string set_graphics(int R, int G, int B, float epaisseur);

/* Renvoie la commande .eps pour tracer toutes les instructions donnees */
string tracer();

/* Renvoie la commande .eps pour remplir la forme fermee en fonction des instructions donnee */
string remplir();

/* Renvoie la commande .eps pour afficher l'image construite */
string affiche_eps();

/* Renvoie le nom d'un fichier .eps correspond a une image donnee */
string get_fichier_eps(string nom, int mode);

/* Cree le fichier .eps du contour d'une image donnee (differents modes possible) 
 * 1 - Contour avec segments
 * 2 - Contour avec segments et points
 * 3 - Contour et remplissage de la forme detouree
 */
void creer_eps(Image I, int mode);
 
#endif
