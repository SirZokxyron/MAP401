#include "../interfaces/contours.h"

/* Fonctions pour determiner le contour d'une image */

    //* Renvoie le pixel de depart, le premier pixel noir trouve dans l'image masque
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

    //* Creer le nom de fichier correct pour la sauvegarde du .contours d'une image
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

    //* Affiche a l'ecran le nombre de contours et de segments totaux
    void debug_contour(Image I) {
        
        //> Recuperation du fichier .contours correspond a l'image
        string nom = get_fichier_contours(I.nom);
        FILE * f = fopen(nom, "r");

        //> Recuperation du nombre de contours
        int nb_contours;
        fscanf(f, "%d", &nb_contours);

        //> Initialisation des variables pour la somme
        int somme = 0;
        int terme;

        //> Iteration sur le nombre de contours
        for (int contour_i = 0; contour_i < nb_contours; contour_i++) {
            fscanf(f, "%d\n", &terme);
            somme += terme;

            //> On passe a travers les lignes des points
            for (int segment_i = 0; segment_i < terme; segment_i++) {
                fscanf(f, "%*[^\n]\n");
            } 
        }

        //> Affichage du nombre de contours et de segments totaux
        printf("Nombre de contours = %d\n", nb_contours);
        printf("Nombre de segments = %d\n", somme - nb_contours);

        //> Fermeture du fichier
        fclose(f);
    }

    //* Renvoie le contour d'une image passee en argument selon l'algorithme vu en cours
    void determiner_contour(Image I) {

        //> On supprime un potentiel precedent fichier .contours
        string commande = (string)malloc(128);
        sprintf(commande, "rm %s 2> /dev/null", get_fichier_contours(I.nom));
        system(commande);

        //> Creation du robot qui determine le contour
        Robot r;

        //> Tant que le masque contient au moins un pixel noir
        while (!est_blanche(I)) {
            
            //? Affichage du masque de l'image a l'ecran pour du debugging
            //? ecrire_masque(I); printf("\n");        

            //> Initialisation du robot avec les bonnes coordonnees de depart et orientation Est
            Point pos_init = init_robot(&r, I);
            
            //> Boucle tant que le contour n'est pas termine
            bool boucle = true;
            while (boucle) {
                //> On enleve les pixels par lesquelles on passe du masque si on est oriente vers l'Est
                if (get_orientation(r) == Est) set_pixel_masque(I, r.pos.x + 1, r.pos.y + 1, BLANC);
                //> Stockage de la position actuel dans la memoire
                memoriser_pos(&r);
                avancer(&r); 
                //> Actualisation de l'orientation en fonction du contexte
                update_ori(&r, I);
                //> On verifie si on a termine le contour
                if (compare_point(get_position(r), pos_init) && (get_orientation(r) == Est)) {
                    boucle = false;
                }
            }
            //> On sauvegarde le premier/dernier point une nouvelle fois
            memoriser_pos(&r);
            
            //> On sauvegarde la memoire du robot dans une fichier .contours
            save_contour(r.memoire, get_fichier_contours(I.nom));
        }
    }

    //* Sauvegarde un contour donne sous forme de liste de point dans un fichier .contours
    void save_contour(liste L, char * nom)  {

        FILE *f;
        f = fopen(nom, "r+");

        //> Si f == NULL, alors on cree le fichier contenant le premier contour
        if (!f) {
            //! fclose(f);          //! Ne pas fclose un pointeur vers un fichier NULL
            f = fopen(nom, "w");
            fprintf(f, "1                 \n\n");
        } else {
            int nb_contours;
            fscanf(f, "%d", &nb_contours);
            nb_contours++;
            fseek(f, 0, SEEK_SET);
            fprintf(f, "%d", nb_contours);
            
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