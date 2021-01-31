#include "../interfaces/contours.h"

/* Fonctions pour determiner le contour d'une image */

    /* Renvoie le pixel de depart selon un algorithme de recherche des contours qui necessite un pixel noir sous-jacent a un pixel blanc */
    Point pos_depart (Image I) {
        for (int i = 1; i <= hauteur_image(I); i++) {
            for (int j = 1; j <= largeur_image(I); j++) {
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

    /* Creer le nom de fichier correct pour la sauvegarde du .contours d'une image */
    string get_fichier_contours(string nom) {
        
        //> Ajout du suffix ".contours" a la fin du nom
        string suffix = ".contours";
        string temp = (string)malloc(1 + strlen(nom) + strlen(suffix));
        sprintf(temp, "%s%s", nom, suffix);

        //> Ajout du prefix "build/" au debut du nom
        string prefix = "build/";
        string nom_f = (string)malloc(1 + strlen(prefix) + strlen(temp));
        sprintf(nom_f, "%s%s", prefix, temp);

        return nom_f;
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
        //> ecrire_contour(r.memoire);
        save_contour(r.memoire, get_fichier_contours(I.nom)); 
    }

    /* Sauvegarde un contour donne sous forme de liste de point dans un fichier .contours */
    void save_contour(liste L, char * nom)  {

        FILE *f = fopen(nom, "w");
        
        fprintf(f, "1\n\n");
        
        int tailleL = L.taille;
        fprintf(f, "%d\n", tailleL);
        cellule * cell = L.tete;
        while (cell) {
            fprintf(f, " %.1lf %.1lf\n", cell->p.x, cell->p.y);
            cell = cell->suivant;
        }

        fclose(f);
    }