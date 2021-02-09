/****************************************************************************** 
  Interface du module image
******************************************************************************/

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "../interfaces/types_macros.h"

/* Structures de donnees */

   //* Type enumere Pixel avec BLANC = 0 et NOIR = 1
   typedef enum {BLANC=0,NOIR=1} Pixel;

   //* Type Image
   typedef struct Image_ {
      string nom;
      UINT L,H; /* largeur et hauteur de l'image */
      Pixel* tab; /*  tableau de pixels */
      /* le pixel d'abscisse x et d'ordonnee y avec 1<=x<=L et 1<=y<=H 
         est tab[x-1+L*(y-1)] */
      Pixel* masque;
   } Image;

/* Fonctions pour gerer les structures de donnees */    

   //* Creation d'une image PBM de dimensions L x H avec tous les pixels blancs
   Image creer_image(UINT L, UINT H);

   //* Suppression de l'image I = *p_I
   void supprimer_image(Image *p_I);

   //* Renvoie la valeur du pixel (x,y) de l'image I : si (x,y) est hors de l'image, la fonction renvoie BLANC
   Pixel get_pixel_image(Image I, int x, int y);

   //* Renvoie la valeur du pixel (x,y) du masque de l'image I
   Pixel get_pixel_masque(Image I, int x, int y);

   //* Change la valeur du pixel (x,y) de l'image I avec la valeur v : si (x,y) est hors de l'image, la fonction ne fait rien
   void set_pixel_image(Image I, int x, int y, Pixel v);

   //* Change la valeur du pixel (x,y) du masque de l'image I avec la valeur v
   void set_pixel_masque(Image I, int x, int y, Pixel v);

   //* Renvoie la largeur de l'image I
   UINT largeur_image(Image I);

   //* Renvoie la hauteur de l'image I
   UINT hauteur_image(Image I);

   //* Renvoie l'aire de l'image I
   UINT aire(Image I);

   //* Calculer l'image-masque de l'image I
   Image calculer_masque_image(Image I);

   //* Lire l'image dans le fichier nomme nom_f s'il y a une erreur dans le fichier le programme s'arrete en affichant un message
   Image lire_fichier_image(char *nom_f);

   //* Afficher l'image I a l'ecran
   void ecrire_image(Image I);

   //* AFficher le masque de l'image I a l'ecran
   void ecrire_masque(Image I);

#endif /* _IMAGE_H_ */ 
