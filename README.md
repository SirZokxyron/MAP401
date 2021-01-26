    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    #       //    //      //      //////     //    //   ////////       ////   #
    #      ///  ///    //  //    //    //   //    //   //    //      // //    #
    #     // // //   //    //   //    //   ////////   //    //     //  //     #
    #    //    //   ////////   //////           //   //    //         //      #
    #   //    //   //    //   //               //   ////////         //       #
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

**Auteurs :** Hugo Bensbia ; Naomi Rousselle

**Groupe :** MIN-4      

# Que contient cette archive ?

Les fichiers d'un projet logiciel visant a l'extraction des contours d'une image bitmap.

# Comment sont organises les fichiers ?

## Repertoire "build"

Ce repertoire contient les fichier `.contours` crees par le programme `test_contours` de la tache 3.
Il sert de zone de reception de ces fichiers.

## Repertoire "images"

Ce repertoire contient les images utilisees par les differents programmes de tests.

Les images ayant le pre-fixe *[valide]* sont syntaxiquement correcte.
Les images ayant le pre-fixe *[erreur]* sont volontairement syntaxiquement fausses pour mettre en avant la gestion d'une erreur particuliere par un programme de test. L'erreur est indiquee dans le titre.

## Repertoire "tests"

Ce repertoire contient les programmes visant a tester les fonctions implementees dans les differents paquetages utilises.

## Repertoire "interfaces"

Ce repertoire contient les fichiers interfaces (.h) des differents paquetages utilises pour le projet.

## Repertoire "lib"

Ce repertoire contient les fichiers d'implementations (.c) des differents paquetages utilises pour le projet.

## Repertoire "scripts"

Ce repertoire contient des scripts qui compilent et effectuent automatiquement differents tests pour chacune des taches.
Commande : `./scripts/[tache_x]_nom.sh`

## Repertoire du projet

### format.md

Specifie nos regles d'ecriture pour nos fonctions, structures, et autre indications notables pour comprendre notre syntaxe.

### Makefile

Sert a compiler les programmes selon des regles definies. 
Liste des commandes : 
- `make` : Compile tous les executables.
- `make clean` : Supprime tous les fichiers *.o*
- `make clear` : Supprime tous les executables

### SuiviProjet.xls

Contient notre journal de bord et le suivi de notre projet que ce soit en terme d'objectifs, de taches accomplies ou de gestion du temps.