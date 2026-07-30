#include "Menu.h"
#include <stdio.h>
#include "Plateau.h"


int debut() {
    char nb; // Déclaration d'une variable caractère pour stocker la réponse de l'utilisateur

    printf("Bienvenue pour commencer une partie de TIC TAC TOE veuillez appuyer sur a\n");// Affiche le message de bienvenue et les instructions
    scanf(" %c", &nb);// Lit le caractère entré par l'utilisateur (l'espace avant %c ignore les espaces blancs)

    if (nb != 'a') {// Vérifie si l'utilisateur n'a pas appuyé sur 'a'
        printf("Erreur");// Affiche un message d'erreur
    }
    return 0;
}



void choix2(Joueur* J1, Joueur* J2) {// Fonction pour demander les noms des deux joueurs


    printf("Entrer votre prenom J1 : ");// Affiche le message demandant le prénom du joueur 1
    scanf("%s", J1->nom);// Lit et stocke le prénom du joueur 1 dans la structure J1
    printf("J1 : %s\n", J1->nom);// Affiche le nom du joueur 1

    printf("Entrer votre prenom J2: ");// C'est la même chose mais pour le Joueur 2
    scanf("%s", J2->nom);// Lit et stocke l'information pour le Joueur 2
    printf("J2 : %s\n", J2->nom);// Affiche le nom du joueur 2

}


int menu() { // Fonction principale qui affiche le menu et gère les choix de l'utilisateur

    int choix; // Variable pour stocker le choix de l'utilisateur

    char board[3][3];// Déclaration du plateau de jeu 3x3

    Joueur J1, J2; // Déclaration des deux structures Joueur

    // Cela permet d'afficher les option des menus

    printf("1. Lancer une partie\n");
    printf("2. Quittez le jeu tappez\n");
    scanf("%i", &choix);


    switch (choix) {
        // Si l'utilisateur choisie l'option 1 pour jouer
        case 1 :

            choix2(&J1, &J2); // Appelle la fonction pour demander les noms des joueurs

            J1.temps_total = 0.0f; // Initialise le temps total du joueur 1 à 0.0
            J2.temps_total = 0.0f; // Initialise le temps total du joueur 2 à 0.0


            initBoard(board);// Initialise le plateau de jeu avec les numéros 1-9
            printBoard(board);// Affiche le plateau initial
            player_turn(board, &J1, &J2);// Lance la boucle de jeu avec alternance des tours
            checkWin(board);// Vérifie s'il y a un gagnant


            printf("Temps total joueur %s (X) = %.2f secondes\n", J1.nom, J1.temps_total);// Affiche le temps total du joueur 1 avec 2 décimales
            printf("Temps total joueur %s (O) = %.2f secondes\n", J2.nom, J2.temps_total);// Même chose pour le joueur 2
            break;// sort de l'option 1
        case 2 :
            return 1; // retoruner 1 pour indiquier que lee programme est terminèe
            // sort de l'option 2
        default :
        printf("Veuillez Saisire Uniquement Les 2 Chiffres Mentionèes\n); // Par Default si l'utilisateur tap un numero heros de 1 et 2.
        }
            

    }


