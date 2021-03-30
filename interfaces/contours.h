#ifndef _CONTOURS_H_
#define _CONTOURS_H_

#include "../interfaces/geometrie2D.h"
#include "../interfaces/image.h"
#include "../interfaces/robot.h"
#include "../interfaces/liste.h"

/* Fonctions pour determiner le contour d'une image */

    //? Renvoie le pixel de depart, le premier pixel noir trouve dans l'image masque
    /* Point pos_depart(Image I); */

    //* Creer le nom de fichier correct pour la sauvegarde du .contours d'une image
    string get_fichier_contours(string nom);

    //* Affiche a l'ecran le nombre de contours et de segments totaux
    void debug_contour(Image I);

    //* AFfiche a l'ecran le nombre de bezier2
    void debug_bezier2(Image I);

    //* Affiche a l'ecran le nombre de bezier3
    void debug_bezier3(Image I);

    //* Renvoie le contour d'une image passee en argument selon l'algorithme vu en cours
    void determiner_contour(Image I, int simplification);

    //* Sauvegarde un contour donne sous forme de liste de point dans un fichier .contours
    void save_contour(liste L, char * nom);

#endif