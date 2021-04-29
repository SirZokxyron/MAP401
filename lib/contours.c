#include "../interfaces/contours.h"
#include "../interfaces/simplification.h"

/* Fonctions pour determiner le contour d'une image */

    //? [ANCIENNE] Renvoie le pixel de depart, le premier pixel noir trouve dans l'image masque
    /* Point pos_depart (Image I) {
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
    } */

    //* Creer le nom de fichier correct pour la sauvegarde du .contours d'une image
    string get_fichier_contours(string nom) {
        
        //> Ajout du suffixe ".contours" a la fin du nom
        string suffixe = ".contours";
        string temp = (string)malloc(1 + strlen(nom) + strlen(suffixe));
        sprintf(temp, "%s%s", nom, suffixe);

        //> Ajout du prefixe "build/" au debut du nom
        string prefixe = "build/";
        string nom_f = (string)malloc(1 + strlen(prefixe) + strlen(temp));
        sprintf(nom_f, "%s%s", prefixe, temp);

        return nom_f;
    }

    //* Affiche a l'ecran le nombre de contours et de segments totaux (pour une simpli par distance seuil)
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

    //* Affiche a l'ecran le nombre de contours et de segments totaux (pour une simpli par courbe de bezier 2)
    void debug_bezier2(Image I) {
        
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

        //> Affichage du nombre de bezier2
        printf("Nombre de bezier2 = %d\n", somme/3);

        //> Fermeture du fichier
        fclose(f);
    }

    //* Affiche a l'ecran le nombre de contours et de segments totaux (pour une simpli par courbe de bezier 3)
    void debug_bezier3(Image I) {
        
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

        //> Affichage du nombre de bezier2
        printf("Nombre de bezier3 = %d\n", somme/4);

        //> Fermeture du fichier
        fclose(f);
    }

    //* Renvoie le contour d'une image passee en argument selon l'algorithme vu en cours
    void determiner_contour(Image I, int simplification) {

        //> On supprime un potentiel precedent fichier .contours
        string commande = (string)malloc(128);
        sprintf(commande, "rm %s 2> /dev/null", get_fichier_contours(I.nom));
        system(commande);
        free(commande);

        //> Creation du robot qui determine le contour
        Robot r;

        double d;
        if (simplification) {
            printf("Distance seuil : "); scanf("%lf%*c", &d); printf("\n");
        }

        //> On parcourt chaque pixel de l'image
        for (int y = 1; y <= hauteur_image(I); y++) {
            for (int x = 1; x <= largeur_image(I); x++) {

                //> Si le pixel du masque est blanc, on evite cette boucle
                if (get_pixel_masque(I, x, y) == BLANC) continue;

                //? Affichage du masque de l'image a l'ecran pour du debugging
                //? ecrire_masque(I); printf("\n");

                //> Initialisation du robot avec les bonnes coordonnees de depart et orientation Est
                Point pos_init = init_robot(&r, set_point(x, y));
            
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
                liste L;
                init_liste(&L);
                tableau tab_memoire = liste_V_tableau(r.memoire);
                //> Passage par une simplification si argument correspondant
                switch (simplification) {
                    case 3:
                        L = simplification_douglas_peucker_bezier3(tab_memoire, 0, tab_memoire.taille - 1, d);
                        break;
                    case 2:
                        L = simplification_douglas_peucker_bezier2(tab_memoire, 0, tab_memoire.taille - 1, d);
                        break;
                    case 1:
                        L = simplification_douglas_peucker(tab_memoire, 0, tab_memoire.taille - 1, d);
                        break;
                    default:
                        L = r.memoire;
                        break;
                }

                //> On sauvegarde la memoire du robot dans une fichier .contours
                save_contour(L, get_fichier_contours(I.nom));

                free_list(&r.memoire);
                if (simplification != 0) free_list(&L);
            }
        }
    }

    //* Sauvegarde un contour donne sous forme de liste de point dans un fichier .contours
    void save_contour(liste L, char * nom)  {

        //> On ouvre le fichier .contours passe en argument
        FILE *f;
        f = fopen(nom, "r+");

        //> Si f == NULL, alors on cree le fichier qui va contenir le premier contour
        if (!f) {
            //! fclose(f);          //! Ne pas fclose un pointeur vers un fichier NULL
            f = fopen(nom, "w");
            fprintf(f, "1");
            fprintf(f, "                 ");
            fprintf(f, "\n\n");
        } 
        //> Si f existe deja, alors on le met simplement a jour l'entete du fichier
        else {
            int nb_contours;
            fscanf(f, "%d", &nb_contours);
            nb_contours++;
            fseek(f, 0, SEEK_SET);
            fprintf(f, "%d", nb_contours);
            
            fseek(f, 0, SEEK_END);
        }

        //> On ecrit le nouveau contour dans le fichier
        int tailleL = L.taille;
        fprintf(f, "%d\n", tailleL);
        cellule * cell = L.tete;
        while (cell) {
            fprintf(f, "%.1lf %.1lf\n", cell->p.x, cell->p.y);
            cell = cell->suivant;
        }
        fprintf(f, "\n");

        //> On ferme le fichier
        fclose(f);
    }