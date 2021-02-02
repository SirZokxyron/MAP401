/****************************************************************************** 
  Implementation du module image_pbm
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../interfaces/types_macros.h"
#include"../interfaces/image.h"

//* Macro donnant l'indice d'un pixel de coordonnees (_x,_y) de l'image _I
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).L*((_y)-1)

//* Creation d'une image PBM de dimensions L x H avec tous les pixels blancs
Image creer_image(UINT L, UINT H) {
	Image I;
	UINT i;
	
	I.L = L;
	I.H = H;
	
	// Alloctaion dynamique d'un tableau de L* H Pixel
	I.tab = (Pixel *)malloc(sizeof(Pixel)*L*H);
	I.masque = (Pixel *)malloc(sizeof(Pixel)*L*H);

	// Test si le tableau a ete correctement alloue
	if (I.tab == (Pixel *)NULL) {
		ERREUR_FATALE("[Erreur]\tcreer_image\tImpossible de creer une image.");
	}
	
	// remplir le tableau avec des pixels blancs
	for (i=0; i<L*H; i++) I.tab[i] = BLANC;
	for (i=0; i<L*H; i++) I.masque[i] = BLANC;

	return I;
}

//* Suppression de l'image I = *p_I
void supprimer_image(Image *p_I) {
	free(p_I->tab);
	free(p_I->masque);
	p_I->L = 0;
	p_I->H = 0;
}

//* Renvoie la valeur du pixel (x,y) de l'image I : si (x,y) est hors de l'image, la fonction renvoie BLANC
Pixel get_pixel_image(Image I, int x, int y) {
	if (x<1 || x>I.L || y<1 || y>I.H) return BLANC;
	return I.tab[INDICE_PIXEL(I,x,y)];
}

//* Renvoie la valeur du pixel (x,y) du masque de l'image I
Pixel get_pixel_masque(Image I, int x, int y) {
	if (x<1 || x>I.L || y<1 || y>I.H) return BLANC;
	return I.masque[INDICE_PIXEL(I,x,y)];
}

//* Change la valeur du pixel (x,y) de l'image I avec la valeur v : si (x,y) est hors de l'image, la fonction ne fait rien
void set_pixel_image(Image I, int x, int y, Pixel v) {
	if (x<1 || x>I.L || y<1 || y>I.H) return;
	I.tab[INDICE_PIXEL(I,x,y)] = v;
}

//* Change la valeur du pixel (x,y) du masque de l'image I avec la valeur v
void set_pixel_masque(Image I, int x, int y, Pixel v) {
	if (x<1 || x>I.L || y<1 || y>I.H) return;
	I.masque[INDICE_PIXEL(I,x,y)] = v;
}

//* Renvoie la largeur de l'image I
UINT largeur_image(Image I) {
	return I.L;
}

//* Renvoie la hauteur de l'image I
UINT hauteur_image(Image I) {
	return I.H;
}

//* Renvoie l'aire de l'image I
UINT aire (Image I) {
	return (hauteur_image(I)*largeur_image(I));
}

//* Teste si le fichier d'identificateur f debute par un en-tete valide pour un fichier PBM :
//* 	- ligne 1 : P1
//*		- suivie de zero, une ou plusieurs lignes commencant toutes par #
   
//* La fonction se termine correctement si le fichier est correct, et le pointeur de fichier se trouve a la suite l'entete.
//*	Sinon, l'execution du programme est arretee avec l'affichage d'un message d'erreur (appel a ERREUR_FATALE).
void entete_fichier_pbm(FILE *f) {
	char *ligne;
	size_t n;
	ssize_t l_ligne;

	// Position en debut de fichier
	fseek(f, 0, SEEK_SET);
	
	// Lecture et test de la ligne 1
	ligne = (char *)NULL;
	n = 0;
	l_ligne = getline(&ligne, &n, f);
	
	// La ligne est correcte ssi ligne = {'P','1',0} est une chaine de 3 caracteres (le dernier est le caractere nul)
	if (l_ligne != 3) {
		ERREUR_FATALE("[Erreur]\tentete_fichier_pbm\tLigne 1 incorrecte.");
	}
	if ((ligne[0] != 'P') || (ligne[1] != '1')) {
		ERREUR_FATALE("[Erreur]\tentete_fichier_pbm\tLigne 1 incorrecte.");
	}
	free(ligne);
	
	/* Lecture des eventuelles lignes commencant par # */
	bool boucle_ligne_commentaire = true;
	do {
		// Test de la fin de fichier
		if (feof(f)) {
			ERREUR_FATALE("[Erreur]\tentete_fichier_pbm\tFin fichier inattendue.");
		} 
		
		// Lecture d'un caractere et test par rapport a '#'
		char c;
		fscanf(f, "%c", &c);
		if (c=='#') {
			// Lecture du reste de la ligne
			ligne = (char *)NULL;
			n = 0;
			l_ligne = getline(&ligne, &n, f);
			free(ligne);
		}
		else {
			// Reculer d'un caractere dans f 
			fseek(f, -1, SEEK_CUR);
			boucle_ligne_commentaire = false;
		}
	} while (boucle_ligne_commentaire);
}
  
//* Lit l'image dans le fichier nom_f : s'il y a une erreur dans le fichier, le programme s'arrete en affichant un message */
Image lire_fichier_image(char *nom_f) {
	FILE *f;
	UINT L,H;
	UINT x,y;
	int res_fscanf;
	Image I;
	
	// Ouverture du fichier nom_f en lecture
	f = fopen(nom_f, "r");
	if (f == (FILE *)NULL)
	{
		ERREUR_FATALE("[Erreur]\tlire_fichier_image\tOuverture du fichier impossible."); 
	} 
	
	// Traitement de l'en-tete et arret en cas d'erreur
	entete_fichier_pbm(f);
	
	// Lecture des dimensions - lecture de 2 entiers
	res_fscanf = fscanf(f, "%d", &L);
	if (res_fscanf != 1) {
		ERREUR_FATALE("[Erreur]\tlire_fichier_image\tLargeur invalide.");
	}
	res_fscanf = fscanf(f, "%d", &H);
	if (res_fscanf != 1) {
		ERREUR_FATALE("[Erreur]\tlire_fichier_image\tHauteur invalide.");
	}
	
	// Creation de l'image I de dimensions L x H
	I = creer_image(L, H);

	// Ajout du nom a l'image
	nom_f[strlen(nom_f) - 4] = '\0';
	I.nom = (string)malloc(1 + strlen(nom_f+7));
	strcpy(I.nom, nom_f+7);

	// Lecture des pixels du fichier - lecture caractere par caractere seuls les caracteres '0' (BLANC) ou '1' (NOIR) doivent etre pris en compte
	x = 1;
	y = 1;
	Pixel masque;
	Pixel pix;
	char c;
	
	while (!feof(f)) {
		fscanf(f, "%c", &c);

		if (c == '0' || c == '1') {

			masque = BLANC;
			if (c == '0') {
				pix = BLANC;
			} else {
				if (get_pixel_image(I, x, y - 1) == BLANC) masque = NOIR;
				pix = NOIR;
			}

			set_pixel_masque(I, x, y, masque);
			set_pixel_image(I, x, y, pix);
			x++;
			if (x > L) {
				x = 1;
				y++;
				if (y > H) {
					break;
				}
			}
		} 
	}
	
	// Verification que l'image soit bien remplie
	if (y != H+1) {
		ERREUR_FATALE("[Erreur]\tlire_fichier_image\tPas assez de caractere dans le fichier pbm.");
	}

	// Fermeture du fichier
	fclose(f);
	
	return I;
}

//* Affichage de l'image I a l'ecran
void ecrire_image(Image I) {
	for (int i = 1; i <= hauteur_image(I); i++) {
		for (int j = 1; j <= largeur_image(I); j++) {
			switch (get_pixel_image(I,j,i)) {
			case BLANC:
				printf(".");
				break;
			case NOIR:
				printf("x");
				break;
			default:
				ERREUR_FATALE("[Erreur]\tecrire_image\tPixel ayant une valeur autre que 0 ou 1.");
				break;
			}
		}
		printf("\n");
	}
}

//* AFficher le masque de l'image I a l'ecran
void ecrire_masque(Image I) {
	for (int i = 1; i <= hauteur_image(I); i++) {
		for (int j = 1; j <= largeur_image(I); j++) {
			switch (get_pixel_masque(I,j,i)) {
			case BLANC:
				printf(".");
				break;
			case NOIR:
				printf("x");
				break;
			default:
				ERREUR_FATALE("[Erreur]\tecrire_masque\tPixel ayant une valeur autre que 0 ou 1.");
				break;
			}
		}
		printf("\n");
	}
}

//* Renvoie true si l'image masque est blanche, false sinon
bool est_blanche(Image I) {
	for (int i = 1; i <= hauteur_image(I); i++) {
		for (int j = 1; j <= largeur_image(I); j++) {
			if(get_pixel_masque(I,j,i) == NOIR) return false;
		}
	}
	return true;
}