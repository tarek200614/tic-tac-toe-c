#include "Menu.h"
#include <stdio.h>
#include "Plateau.h"


int debut() {
    char nb;

    printf("Bienvenue pour commencer une partie de TIC TAC TOE veuillez appuyer sur a\n");
    scanf(" %c", &nb);

    if (nb != 'a') {
        printf("Erreur");
    }
    return 0;
}



void choix2(Joueur* J1, Joueur* J2) {


    printf("Entrer votre prenom J1 : ");
    scanf("%s", J1->nom);
    printf("J1 : %s\n", J1->nom);

    printf("Entrer votre prenom J2: ");
    scanf("%s", J2->nom);
    printf("J2 : %s\n", J2->nom);

}


int menu() {
    int choix;
    char board[3][3];
    Joueur J1, J2;
    char symbole;

    printf("1. Lancer une partie\n");
    printf("2. Choix des joueurs\n");
    printf("3. Acceder aux fichiers contenant les logs\n");
    printf("4. Quittez le jeu tappez\n");
    scanf("%i", &choix);


    switch (choix) {
        case 1 :
            choix2(&J1, &J2);
            initBoard(board);
            printBoard(board);
            player_turn(board, &J1, &J2);
            checkWin(board);
            break;
        case 2 :
            printf("Choix des joueurs");
            break;
        case 3 :
            printf("Acceder aux fichiers contenant les logs");
            break;
        case 4 :
            return 0;
        }
            return 0;
    }