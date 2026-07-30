#ifndef UNTITLED18_PLATEAU_H
#define UNTITLED18_PLATEAU_H

typedef struct Joueur {

    char nom[50];
    int position_x;
    int position_y;

}Joueur;

void initBoard(char board[3][3]);
void printBoard(char board[3][3]) ;
void placement(char board[3][3], Joueur* joueur, char symbole);
int is_valid_move(char board[3][3], int x, int y);
void player_turn(char board[3][3], Joueur* J1, Joueur* J2);
int checkWin(char board[3][3]);
#endif //UNTITLED18_PLATEAU_H