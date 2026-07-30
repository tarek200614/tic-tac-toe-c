#include "Plateau.h"
#include <stdio.h>
#include <stdbool.h>

void initBoard(char board[3][3]) {

    board[0][0] = '1'; board[0][1] = '2'; board[0][2] = '3';
    board[1][0] = '4'; board[1][1] = '5'; board[1][2] = '6';
    board[2][0] = '7'; board[2][1] = '8'; board[2][2] = '9';
}

void printBoard(char board[3][3]) {

    for (int i = 0; i < 3; i++) {
        printf("%c   |  %c  |   %c\n", board[i][0], board[i][1], board[i][2]);
        if (i != 2) {
            printf("----|-----|----\n");
        }
    }
}
int is_valid_move(char board[3][3], int x, int y) {
    // Vérifier que les coordonnées sont dans les limites du plateau
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        printf("Erreur : Coordonnees hors limites ! Veuillez entrer des valeurs entre 1 et 3.\n");
        return 0;
    }

    // Vérifier que la case n'est pas déjà occupée par 'X' ou 'O'
    if (board[x][y] == 'X' || board[x][y] == 'O') {
        printf("Erreur : Cette case est deja occupee !\n");
        return 0;
    }

    return 1;
}
void placement(char board[3][3], Joueur* joueur, char cygne) {
    int x, y;

    do {
        printf("\n%s (%c), veuillez entrer la coordonnee x (1-3) : ", joueur->nom, cygne);

        scanf("%i", &joueur->position_x);

        printf("%s (%c), veuillez entrer la coordonnee y (1-3) : ", joueur->nom, cygne);

        scanf("%i", &joueur->position_y);

        x = joueur->position_x - 1;
        y = joueur->position_y - 1;

        if (!is_valid_move(board, x, y)) {
            printf("\nErreur : Case invalide ou deja prise !\n\n");
            printBoard(board);
        }

    } while (!is_valid_move(board, x, y));

    board[x][y] = cygne;
    printf("\n");
    printBoard(board);
}

void player_turn(char board[3][3], Joueur* J1, Joueur* J2) {
    char joueur_mtn = 'X';
    int tour = 0;

    while (tour < 9) {
        if (joueur_mtn == 'X') {
            placement(board, J1, 'X');
            joueur_mtn = 'O';
        } else {
            placement(board, J2, 'O');
            joueur_mtn = 'X';
        }

        tour++;

        int winner = checkWin(board);
        if (winner == 'X') {
            printf("\n Felicitations %s ! Tu as gagne avec X !\n", J1->nom);
            return;
        } else if (winner == 'O') {
            printf("\n Felicitations %s ! Tu as gagne avec O !\n", J2->nom);
            return;
        }

        if (tour == 9) {
            printf("\nMatch nul ! Le plateau est rempli.\n");
            return;
        }
    }
}


int checkWin(char board[3][3]) {

    for(int i = 0; i < 3; i++){
        if((board[i][0] == 'X' || board[i][0] == 'O') &&
           board[i][0] == board[i][1] &&
           board[i][1] == board[i][2])
            return board[i][0];
    }

    for(int j = 0; j < 3; j++){
        if((board[0][j] == 'X' || board[0][j] == 'O') &&
           board[0][j] == board[1][j] &&
           board[1][j] == board[2][j])
            return board[0][j];
    }

    if((board[0][0] == 'X' || board[0][0] == 'O') &&
       board[0][0] == board[1][1] &&
       board[1][1] == board[2][2])
        return board[0][0];

    // Deuxième diagonale
    if((board[0][2] == 'X' || board[0][2] == 'O') &&
       board[0][2] == board[1][1] &&
       board[1][1] == board[2][0])
        return board[0][2];

    return 0;
}