e#include "Plateau.h"
#include <stdio.h>
#include <time.h>

// Fonction pour initialiser le plateau avec les chiffres 1 à 9
void initBoard(char board[3][3]) {

    board[0][0] = '1'; board[0][1] = '2'; board[0][2] = '3';// Initialisation de la première ligne avec '1', '2', '3'
    board[1][0] = '4'; board[1][1] = '5'; board[1][2] = '6';// Initialisation de la deuxième ligne avec '4', '5', '6'
    board[2][0] = '7'; board[2][1] = '8'; board[2][2] = '9';// Initialisation de la troisième ligne avec '7', '8', '9'
}

// Fonction pour afficher le plateau de jeu
void printBoard(char board[3][3]) {

    // Boucle qui parcourt les 3 lignes du plateau
    for (int i = 0; i < 3; i++) {
        printf("%c   |  %c  |   %c\n", board[i][0], board[i][1], board[i][2]);// Si ce n'est pas la dernière ligne (i != 2)
        if (i != 2) {// Affiche une ligne de séparation horizontale
            printf("----|-----|----\n");
        }
    }
}

int is_valid_move(char board[3][3], int x, int y) {// Fonction qui vérifie si un coup est valide
    // Vérifier que les coordonnées sont dans les limites du plateau
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        printf("Erreur : Pas ce carré. Veuillez entrer des valeurs entre 1 et 3.\n");// Message d'erreur
        return 0;// Retourne 0 (faux) car le coup n'est pas valide
    }

    // Vérifier que la case n'est pas déjà occupée par 'X' ou 'O'
    if (board[x][y] == 'X' || board[x][y] == 'O') {
        printf("Erreur : deja pris \n");// Message d'erreur si la case est déjà prise
        return 0;
    }
    return 1;
}

void placement(char board[3][3], Joueur* joueur, char cygne) {// Fonction pour gérer le placement d'un symbole sur le plateau
    int x, y; // Déclaration de variables pour les coordonnées converties

    clock_t debut = clock();// Variables pour mesurer le temps

    do {// Boucle qui continue tant que le coup n'est pas valide avec le do while
        printf("\n%s (%c), veuillez entrer la coordonnee x ( La Ligne )  : ", joueur->nom, cygne);// Demande au joueur d'entrer la coordonnée x

        scanf("%i", &joueur->position_x);// Lit la coordonnée x entrée par le joueur

        printf("%s (%c), veuillez entrer la coordonnee y (La Colone )  : ", joueur->nom, cygne);// Demande au joueur d'entrer la coordonnée y

        scanf("%i", &joueur->position_y);// Lit la coordonnée y entrée par le joueur

        // Convertit les coordonnées de 1-3 à 0-2 (indices du tableau)
        x = joueur->position_x - 1;
        y = joueur->position_y - 1;

        // Si le coup n'est pas valide
        if (!is_valid_move(board, x, y)) {
            printf("\nErreur : deja pris ou alors pas dans la bonne case \n\n");// Affiche un message d'erreur
            printBoard(board); // Réaffiche le plateau pour que le joueur puisse voir l'état actuel
        }

    } while (!is_valid_move(board, x, y));// Continue la boucle tant que le coup n'est pas valide
    // Enregistre le temps a la fin du tour
    clock_t fin = clock();
    double tempsTour = (double)(fin - debut) / CLOCKS_PER_SEC;// Calcule le temps écouler pendant ce tour en secondes
    joueur->temps_total += tempsTour;// Ajoute le temps de ce tour au temps total du joueur

    board[x][y] = cygne;// Place le symbole du joueur ('X' ou 'O') sur le plateau
    printf("\n");// Affiche une ligne vide pour l'espacement
    printBoard(board);// Affiche le plateau mis à jour
}

void logMove(FILE *f, int tour, char joueur, int ligne, int colonne) {// Fonction pour enregistrer un coup dans un fichier log
    if (f != NULL) { // Vérifie que le pointeur de fichier n'est pas NULL
        fprintf(f, "Tour %d : Joueur %c joue (%d,%d)\n", tour, joueur, ligne, colonne);// Écrit dans le fichier : numéro du tour, symbole du joueur et coordonnées
    }
}

void player_turn(char board[3][3], Joueur* J1, Joueur* J2) {// Fonction principale qui gère l'alternance des tours entre les joueurs

    char joueur_mtn = 'X';// Variable qui indique quel joueur doit jouer ('X' commence)
    int tour = 0;// Compteur de tours initialisé à 0

    FILE *fichier = fopen("historique_morpio_dateXXX.txt", "w");// Ouvre un fichier en mode écriture pour enregistrer l'historique
    fprintf(fichier, "historique du jeu \n\n");// Écrit l'en-tête du fichier d'historique
    void afficherHistorique(const char *filename) {//Procdure pour afficher l'historique a la fin du jeu (outile)
    FILE *f = fopen(filename, "r");//ouvirer le fichier avec le droit de lecture r
    char ligne[256];// reserver 256 ligne une espace assie pour affichier au moin 29 parites jouées

    printf("\n===== HISTORIQUE DE LA PARTIE =====\n"); // affiche le nom indique de l'historique
    while (fgets(ligne, sizeof(ligne), f)) //boucle while pour plusiure itiration avec lire en utilisant la fonction fgets qui permet de sasire avec les espaces
        printf("%s", ligne); // afficher les lingns enregistrer
    printf("=================================\n");// fin de l'historique

    fclose(f);//fermuture de fichier
}
    while (tour < 9) {// Boucle qui continue tant qu'il reste des cases vides, maximum 9 tours
        if (joueur_mtn == 'X') {// Si c'est le tour du joueur X
            placement(board, J1, 'X');// Le joueur 1 place son symbole 'X'
            logMove(f,tour +1,'X',J1->position_x,J1->position_y); //enregistre la position et le tour du joueur 1 avec le symbole 'X'
            joueur_mtn = 'O';// Change pour le prochain joueur 'O'
        } else {// Sinon c'est le tour du joueur O
            placement(board, J2, 'O');// Le joueur 2 place son symbole 'O'
            logMove(f,tour +1,'O',J2->position_x,J2->position_y); //enregistre la position et le tour du joueur 2 avec le symbole 'O'
             joueur_mtn = 'X';// Change pour le prochain joueur 'X'
        } 

        tour++;// Incrémente le compteur tours donc cela fait tour = 0 + 1 = 1

        int winner = checkWin(board);// Vérifie s'il y a un gagnant
        if (winner == 'X') {// Si le joueur X a gagné
            printf("\n Bravo %s ! Tu as gagner avec X \n", J1->nom);// Affiche un message de victoire pour le joueur 1
            fprintf(fichier, "\nGagnant : %s (X)\n", J1->nom);// Il va enregistrer le nom du joueur et aller chercher le nom dans la structure du joueur
            fclose(fichier);// fermer le fichier
            return;// Sort de la fonction
        }  else if (winner == 'O') {// SI c'est le joueur qui a le 0 et qu'il gagne
            printf("\n Bravo %s ! Tu as gagner avec O \n", J2->nom);// On va afficher le message comme quoi il a gagné
            fprintf(fichier, "\nGagnant : %s (O)\n", J2->nom);// Ensuite on va prendre le nom du joueur dans ça structure et le marquer dans le fichier
            fclose(fichier);// ferme ensuite le fichier
            return;
        }
        // Si on atteint 9 tours
        if (tour == 9) {
            printf("\n match nul on ne peut pu jouer le tableau est rempli \n");// On va afficher un message comme quoi les joueurs on réalisé un match nul
            fprintf(fichier, "\nMatch nul\n");// et entrer dans le fichier Match nul
            fclose(fichier);// fermer le fichier pour finir
            return;
        }
    }
 fcolse(f);// fermer le fichier 
 afficherHistorique(filename);// pour afficher a la fin du jeu ce qui ecrit de dont du fichier filename (historique du jeu ,le nombre de tour, nom du joueur ) 
}


int checkWin(char board[3][3]) {// Fonction qui vérifie s'il y a un gagnant

    for(int i = 0; i < 3; i++){// Vérifie les lignes horizontales
        // Boucle sur les 3 lignes
        if((board[i][0] == 'X' || board[i][0] == 'O') &&// Si la première case de la ligne contient 'X' ou 'O'
           board[i][0] == board[i][1] &&// ET que les 3 cases de la ligne sont identiques
           board[i][1] == board[i][2])
            return board[i][0];// Retourne le symbole gagnant ('X' ou 'O')
    }

    // Il réalise la même chose que dans le code au dessus mais vérifie les colonnes
    for(int j = 0; j < 3; j++){
        if((board[0][j] == 'X' || board[0][j] == 'O') &&
           board[0][j] == board[1][j] &&
           board[1][j] == board[2][j])
            return board[0][j];// Retourne le symbole gagnant ('X' ou 'O')
    }
// CES codes vont vérifier les diagonales
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





