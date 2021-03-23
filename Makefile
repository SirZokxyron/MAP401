#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond a toutes les dependances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################

#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = ./interfaces/

# chemin d'acces aux librairies (binaires)
LIBDIR = ./lib/

# chemin d'acces aux executables (binaires)
EXEDIR = ./tests/

# options pour l'edition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image test_geometrie test_contours test_eps test_multiples_contours test_distance test_simplification test_bezier test_fonction

#############################################################################
# definition des regles
#############################################################################

########################################################
# la regle par defaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : $(LIBDIR)%.c
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

%.o : $(EXEDIR)%.c
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

% : %.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

image.o : $(LIBDIR)image.c $(INCDIR)image.h $(INCDIR)types_macros.h
test_image.o : $(EXEDIR)test_image.c $(INCDIR)image.h 

geometrie2D.o : $(LIBDIR)geometrie2D.c $(INCDIR)geometrie2D.h $(INCDIR)types_macros.h
test_geometrie.o : $(EXEDIR)test_geometrie.c $(INCDIR)geometrie2D.h 

contours.o : $(LIBDIR)contours.c $(INCDIR)contours.h $(INCDIR)geometrie2D.h $(INCDIR)liste.h $(INCDIR)image.h $(INCDIR)robot.h $(INCDIR)types_macros.h
liste.o : $(LIBDIR)liste.c $(INCDIR)liste.h $(INCDIR)geometrie2D.h $(INCDIR)types_macros.h
robot.o : $(LIBDIR)robot.c $(INCDIR)robot.h $(INCDIR)contours.h $(INCDIR)types_macros.h $(INCDIR)liste.h
test_contours.o : $(EXEDIR)test_contours.c $(INCDIR)robot.h $(INCDIR)contours.h

eps.o : $(LIBDIR)eps.c $(INCDIR)eps.h $(INCDIR)robot.h $(INCDIR)contours.h $(INCDIR)types_macros.h $(INCDIR)liste.h
test_eps.o : $(EXEDIR)test_eps.c $(INCDIR)eps.h $(INCDIR)robot.h

test_multiples_contours.o : $(EXEDIR)test_multiples_contours.c $(INCDIR)robot.h $(INCDIR)contours.h

simplification.o : $(LIBDIR)simplification.c $(INCDIR)simplification.h $(INCDIR)eps.h $(INCDIR)robot.h $(INCDIR)contours.h $(INCDIR)types_macros.h $(INCDIR)liste.h

test_distance.o : $(EXEDIR)test_distance.c 

test_simplification.o : $(EXEDIR)test_simplification.c simplification.o

test_bezier.o : $(EXEDIR)test_bezier.c simplification.o

test_fonction.o : $(EXEDIR)test_fonction.c simplification.o

########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 

test_geometrie : test_geometrie.o geometrie2D.o

test_distance : test_distance.o geometrie2D.o

test_contours : test_contours.o contours.o robot.o geometrie2D.o image.o liste.o simplification.o

test_eps : test_eps.o eps.o robot.o geometrie2D.o image.o liste.o contours.o simplification.o

test_multiples_contours : test_multiples_contours.o eps.o contours.o robot.o geometrie2D.o image.o liste.o simplification.o

test_simplification : test_simplification.o simplification.o eps.o contours.o robot.o geometrie2D.o image.o liste.o

test_bezier : test_bezier.o simplification.o eps.o contours.o robot.o geometrie2D.o image.o liste.o

test_fonction : test_fonction.o simplification.o eps.o contours.o robot.o geometrie2D.o image.o liste.o

########################################################
# regle pour "nettoyer" le repertoire

clean:
	@echo ""
	@echo "---------------------------------------------"
	@echo "Suppression des fichiers .o "
	@echo "---------------------------------------------"
	rm -fR *.o

########################################################
# regle pour supprimer les executables

clear:
	@echo ""
	@echo "---------------------------------------------"
	@echo "Suppression des executables"
	@echo "---------------------------------------------"
	rm -fR $(EXECUTABLES)