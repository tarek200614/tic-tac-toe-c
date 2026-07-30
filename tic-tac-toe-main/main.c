#include <stdio.h>

/*void initBoard(char board[3][3]) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[3][3]) {
    printf("\n");
    printf("  0   1   2\n");
    for(int i = 0; i < 3; i++){
        printf("%d ", i);
        for(int j = 0; j < 3; j++){
            printf(" %c ", board[i][j]);
            if(j < 2) printf("|");
        }
        if(i < 2) printf("\n  ---|---|---\n");
    }
    printf("\n\n");
}*/

// Victoire ?
if (checkWin(board)) {
    printBoard(board);
    printf("Victoire du joueur %c !\n", player);
    break;
}

// Match nul ?
if (isFull(board)) {
    printBoard(board);
    printf("Match nul !\n");
    break;
}

// Vérifie victoire
int checkWin(char board[3][3]) {
    for(int i = 0; i < 3; i++){
        if(board[i][0] != ' ' &&board[i][0] == board[i][1]&&board[i][1] == board[i][2])

            return 1;

    }
    for(int j = 0; j < 3; j++){
        if(board[0][j] != ' ' && board[0][j] == board[1][j] &&board[1][j] == board[2][j])

            return 1;

    }//premiere diagonale
    if(board[0][0] != ' ' && board[0][0] == board[1][1] &&board[1][1] == board[2][2])

        return 1;

    //deuxieme diagonle
    if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])

        return 1;

    return 0;
}