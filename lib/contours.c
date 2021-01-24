#include "contours.h"



/* Fonctions pour determiner le contour d'une image */

    /* Renvoie le pixel de depart selon un algorithme de recherche des contours qui necessite un pixel noir sous-jacent a un pixel blanc */
    Point pos_depart (Image I) {
        for (int i = 0; i < hauteur_image(I); i++) {
            for (int j = 0; j < largeur_image(I); j++) {
                Pixel p_up = get_pixel_image(I,j,i-1);
                Pixel p = get_pixel_image(I,j,i);

                if ((p == NOIR) && (p_up == BLANC)) {
                    Point pt = set_point(j,i);
                    return pt;
                }
            }
        }
        ERREUR_FATALE("Tous les pixels sont blancs.");
    }

    /* Renvoie le contour d'une image passee en argument selon l'algorithme vu en cours */
    void determiner_contour(Image I) {
        Robot r;
        Point pos_init = init_robot(&r, I);
        bool boucle = true;
        while (boucle) {
            memoriser_pos(&r);
            avancer(&r);
            update_ori(&r, I);
            if (compare_point(get_position(r), pos_init) && (get_orientation(r) == Est)) {
                boucle = false;
            }
        }
        memoriser_pos(&r);
    }