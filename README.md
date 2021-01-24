    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    #       //    //      //      //////     //    //   ////////       ////   #
    #      ///  ///    //  //    //    //   //    //   //    //      // //    #
    #     // // //   //    //   //    //   ////////   //    //     //  //     #
    #    //    //   ////////   //////           //   //    //         //      #
    #   //    //   //    //   //               //   ////////         //       #
    # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

**Autheurs :** Hugo Bensbia ; Naomi Rousselle

**Groupe :** MIN-4

# Que contient cette archive ?

Les fichiers d'une projet logiciel visant a l'extraction des contours d'une image bitmap.

# Comment sont organises les fichiers ?

## Repertoire "images"

Ce repertoire contient les images utilisees avec les differents programmes de tests.

Les images ayant le pre-fixe *[valide]* sont syntaxiquement correcte.
Les images ayant le pre-fixe *[erreur]* sont volontairement syntaxiquement fausse pour mettre en avant la gestion d'une erreur particuliere par une programme de test. L'erreur est indiquee dans le titre.

## Repertoire "executables"

Ce repertoire contient les programmes visant a tester les fonctions implementees dans les differentes paquetages utilises.

## Repertoire "interfaces"

Ce repertoire contient les fichiers interfaces (.h) des differents paquetages utilises pour le projet.

## Repertoire "librairies"

Ce repertoire contient les fichiers d'implementations (.c) des differents paquetages utilises pour le projet.

## Repertoire du projet

### format.md

Specifie nos regles d'ecriture pour nos fonctions, structures, et autre indications notables pour comprendre notre syntax.

### Makefile

Sert a compiler les programmes selon des regles definiees. 
Liste des commandes : 
- *make* : Compile tous les executables.
- *clean* : Supprime tous les fichiers *.o*
- *clear* : Supprime tous les executables

### SuiviProjet.xls

Contient notre journal de bord et le suivi de notre projet que ce soit en terme d'objectifs, de taches accomplies ou de gestion dans le temps.