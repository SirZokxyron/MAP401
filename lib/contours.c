#include "../interfaces/contours.h"

/* Fonctions pour determiner le contour d'une image */

    /* Renvoie le pixel de depart selon un algorithme de recherche des contours qui necessite un pixel noir sous-jacent a un pixel blanc */
    Point pos_depart (Image I) {
        for (int i = 1; i <= hauteur_image(I); i++) {
            for (int j = 1; j <= largeur_image(I); j++) {
                Pixel p = get_pixel_masque(I,j,i);

                if (p == NOIR) {
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

    /* Fonction debug */
    void debug_contour(Image I) {
        string nom = get_fichier_contours(I.nom);

        FILE * f = fopen(nom, "r");

        int nb_contours;
        fscanf(f, "%d", &nb_contours);

        int somme = 0;
        int terme;

        for (int contours_i = 0; contours_i < nb_contours; contours_i++) {
            fscanf(f, "%d\n", &terme);
            somme += terme;

            for (int segments_i = 0; segments_i < terme; segments_i++) {
                fscanf(f, "%*[^\n]\n");
            } 
        }

        printf("Nombre de contours = %d\n", nb_contours);
        printf("Nombre de segments = %d\n", somme-nb_contours);

        fclose(f);
    }

    /* Renvoie le contour d'une image passee en argument selon l'algorithme vu en cours */
    void determiner_contour(Image I) {
        Robot r;
        while (!est_blanche(I)) {
            Point pos_init = init_robot(&r, I);
            bool boucle = true;
            while (boucle) {
                set_pixel_masque(I, r.pos.x + 1, r.pos.y + 1, BLANC);
                memoriser_pos(&r);
                avancer(&r); 
                update_ori(&r, I);
                if (compare_point(get_position(r), pos_init) && (get_orientation(r) == Est)) {
                    boucle = false;
                }
            }
            memoriser_pos(&r);
            save_contour(r.memoire, get_fichier_contours(I.nom)); 
        }
    }

    /* Sauvegarde un contour donne sous forme de liste de point dans un fichier .contours */
    void save_contour(liste L, char * nom)  {

        FILE *f;
        f = fopen(nom, "r+");

        //> Si f == NULL, alors on cree le fichier contenant le premier contour
        if (!f) {
            fclose(f);
            f = fopen(nom, "w");
            fprintf(f, "1\n\n");
        } else {
            int nb_contours;
            fscanf(f, "%d", &nb_contours);
            nb_contours++;
            fclose(f);

            f = fopen(nom, "r+");
            fseek(f, 0, SEEK_SET);
            fprintf(f, "%d\n", nb_contours);
            
            fseek(f, 0, SEEK_END);
        }

        int tailleL = L.taille;
        fprintf(f, "%d\n", tailleL);
        cellule * cell = L.tete;
        while (cell) {
            fprintf(f, "%.1lf %.1lf\n", cell->p.x, cell->p.y);
            cell = cell->suivant;
        }
        fprintf(f, "\n");

        fclose(f);
    }