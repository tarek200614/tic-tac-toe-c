#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/// Procedure Initialize the Board
void intiBoard(char board[3][3]){
int i=0,j=0;
for(i=0;i<2;i++){
 for(j=0;j<2;j++){
   board[i][j]=' ';
 }
}
}
/// Procedure Print the Board
void printBoard(char board[3[3]){
int i=0,j=0;
for(i=0;i<2;i++){
 for(j=0;j<2;j++){
    printf("Case[%d][%d] = %c\n",i+1,j+1,board[i][j]);
 }
}
}
/// Fonction check if the Board is Full
int isFull(char board[3][3]){
int i=0,j=0;
for(i=0;i<2;i++){
 for(j=0;j<2;j++){
   if(board[i][j]==' '){
    return printf("The Board Is not full complete the Case[%d][%d]=\n",i+1,j+1);
   }else;
 }
}
return printf("The Board is Full\n");
}
/// Fonction check of win
int checkWin(char board[3][3]){
int i=0,j=0,score=0;
  if((board[i][j]==board[i+1][j]==board[i+2][j])||(board[i][j]==board[i][j+1]==board[j+2])||(board[i][j]==board[i+1][j+1]==board[i+2][j+2])||(board[i][j+2]==board[i+1][j+1]==board[i+2][j])){
    printf("The player is wining \n");
  }else;
   return ++score;
}







int main()
{
    printf("Hello world!\n");

    return 0;
}
