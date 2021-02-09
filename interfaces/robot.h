#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "../interfaces/contours.h"
#include "../interfaces/liste.h"

/* Structure de donnees */

    typedef enum orientation_ {
        Nord, Est, Sud, Ouest
    } Orientation;

    typedef struct robot_ {
            Point pos;
            Orientation ori;
            liste memoire;
        } Robot;

/* Fonctions pour gerer le robot */

    //* Met la position du robot au point (x, y) trouve par la fonction pos_depart et l'orientation EST
    Point init_robot(Robot * r, Point Depart);

    //* Renvoie l'orientation du robot
    Orientation get_orientation(Robot r);

    //* Renvoie le point correspondant a la position du robot
    Point get_position(Robot r);

    //* Affiche les informations du robot pour le debugging
    void debug_robot(Robot r);

    //* Affiche l'orientation du robot
    void affiche_ori(Robot r);

    //* Affiche la position du robot
    void affiche_pos(Robot r);  

    //* Fait avancer le robot
    void avancer(Robot * r);

    //* Fait tourner le robot selon la direction indiquer par le caractere d (d : droite / g : gauche)
    void tourner(Robot * r, char d);

    //* Renvoie la couleur du pixel a gauche ou a droite du robot selon le charactere d specifie (d : droite / g : gauche)
    Pixel mesure(Robot r, Image I, char d);

    //* Met a jour l'orientation du robot en fonction des cases a sa gauche et sa droite
    void update_ori(Robot * r, Image I);

    //* Stock la position actuelle du robot dans sa memoire
    void memoriser_pos(Robot * r);

#endif