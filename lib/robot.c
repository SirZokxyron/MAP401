#include "robot.h"

/* Fonctions pour controller le robot */

    /* Met la position du robot au point (x, y) trouve par la fonction pos_depart et l'orientation EST */
    Point init_robot(Robot * r, Image I) {
        r->pos = sub_point(pos_depart(I), set_point(1, 1));
        r->ori = Est;
        init_liste(r->memoire);
        return r->pos;
    }

    /* Renvoie l'orientation du robot */
    Orientation get_orientation(Robot r) {
        return r.ori;
    }

    /* Renvoie le point correspondant a la position du robot */
    Point get_position(Robot r) {
        return r.pos;
    }

    /* Affiche les informations du robot pour le debugging */
    void debug_robot(Robot r) {
        printf("Debug Robot : \n");
        affiche_point(r.pos, "Coordonnees : ");
        affiche_ori(r);
    }

    /* Affiche l'orientation du robot */
    void affiche_ori(Robot r) {
        char * ori;
        switch (get_orientation(r)) {
            case Nord:
                ori = "Nord";
                break;
            case Est:
                ori = "Est";
                break;
            case Sud:
                ori = "Sud";
                break;
            case Ouest:
                ori = "Ouest";
                break;
        }
        printf("Orientation : %s\n", ori);
    }

    /* Affiche la position du robot */
    void affiche_pos(Robot r) { 
        affiche_point(r.pos, "Point du contour"); 
    }

    /* Fait avancer le robot */
    void avancer(Robot * r) {
        switch (r->ori) {
            case Nord:
                r->pos = add_point(r->pos, set_point(0,-1));
                break;
            
            case Sud:
                r->pos = add_point(r->pos, set_point(0, 1));
                break;

            case Est:
                r->pos = add_point(r->pos, set_point(1,0));
                break;

            case Ouest:
                r->pos = add_point(r->pos, set_point(-1,0));
                break;
        }
    }

    /* Fait tourner le robot selon la direction indiquer par le caractere d (d : droite / g : gauche) */
    void tourner(Robot * r, char d) {
        switch (d) {
            case 'd':
                r->ori = (r->ori + 1) % 4; 
                break;
            case 'g':
                r->ori = (r->ori - 1) % 4; 
                break;
            default:
                break;
        }
    }

    /* Renvoie la couleur du pixel a gauche ou a droite du robot selon le charactere d specifie (d : droite / g : gauche) */
    Pixel mesure(Robot r, Image I, char d) {
        Point pixel_mesure;
        switch (r.ori) {
            case Nord:
                if (d == 'g') pixel_mesure = set_point(0, 0);
                if (d == 'd') pixel_mesure = set_point(1, 0);
                break;
            case Est:
                if (d == 'g') pixel_mesure = set_point(1, 0);
                if (d == 'd') pixel_mesure = set_point(1, 1);
                break;
            case Sud:
                if (d == 'g') pixel_mesure = set_point(1, 1);
                if (d == 'd') pixel_mesure = set_point(0, 1);
                break;
            case Ouest:
                if (d == 'g') pixel_mesure = set_point(0, 1);
                if (d == 'd') pixel_mesure = set_point(0, 0);
                break;
        }
        pixel_mesure = add_point(pixel_mesure, r.pos);
        return get_pixel_image(I, pixel_mesure.x, pixel_mesure.y);
    }

    /* Met a jour l'orientation du robot en fonction des cases a sa gauche et sa droite */
    void update_ori(Robot * r, Image I) {
        if (mesure(*r, I, 'g') == NOIR) {
            tourner(r, 'g');
        } else {
            if (mesure(*r, I, 'd') == BLANC) {
                tourner(r, 'd');
            }
        }
    }

    /* Stock la position actuelle du robot dans sa memoire */
    void memoriser_pos(Robot * r) {
        cellule * cell = init_cellule(r->pos);
        ajout_en_queue(&r->memoire, cell);
    }