#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/// ================= STRUCTURES ================= ///

typedef struct Joueur {
    char nom[50];
    int position_x;
    int position_y;
    float temps_total;
} Joueur;

/// ================= FONCTIONS ET PROCEDURES  ================= ///

int debut();
int menu();

void clearText();
void initBoard(char board[3][3]);
void printBoard(char board[3][3]);
int is_valid_move(char board[3][3], int x, int y);
void placement(char board[3][3], Joueur* joueur, char symbole);
int checkWin(char board[3][3]);
void logMove(FILE *f, int tour, char joueur, int ligne, int colonne);
void afficherHistorique(const char *filename);
void player_turn(char board[3][3], Joueur* J1, Joueur* J2);
void choix2(Joueur* J1, Joueur* J2);

/// ================= MAIN ================= ///

int main() {
    debut();// Appelle la fonction debut() qui affiche le message de bienvenue
    menu();// Appelle la fonction menu() qui affiche le menu et gère les choix de l'utilisateur
    return 0;
}

/// ================= OUTILS ================= ///

void clearText() {//Procdure qui permet de vider les charactere a vide pour resaisire le a fin de completer (reinsilatie le string a vide)
    int c;// declration du computer
    while ((c = getchar()) != '\n' && c != EOF);//boucle while qui permet de lire le nombre de charactere jusqu'a nouvelle line ou bien la fin du fichier
}

/// ================= PLATEAU ================= ///

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
        printf(" %c | %c | %c\n", board[i][0], board[i][1], board[i][2]);// Si ce n'est pas la dernière ligne (i != 2)
        if (i < 2) printf("---|---|---\n");// Affiche une ligne de séparation horizontale
    }
}

int is_valid_move(char board[3][3], int x, int y) {// Fonction qui vérifie si un coup est valide
    // Vérifier que les coordonnées sont dans les limites du plateau
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        printf("Erreur : coordonnees hors limites.\n");
        return 0;
    }
    if (board[x][y] == 'O'||board[x][y] == 'X') {
        printf("Erreur : case deja occupee.\n");// Message d'erreur
        return 0;// Retourne 0 (faux) car le coup n'est pas valide
    }
    return 1;
}

/// ================= JEU ================= ///

void placement(char board[3][3], Joueur* joueur, char symbole) {// Fonction pour gérer le placement d'un symbole sur le plateau
    int x, y;// Déclaration de variables pour les coordonnées converties

    clock_t debut = clock();// Variables pour mesurer le temps

    do {// Boucle qui continue tant que le coup n'est pas valide avec le do while
        printf("%s (%c) Veuillez Enter la cordonne x Ligne (entre 1 et 3) : ", joueur->nom, symbole);// Demande au joueur d'entrer la coordonnée x
        if (scanf("%d", &joueur->position_x) != 1) { // Lit la coordonnée x entrée par le joueur et assurer qu elle est juste
            clearText();// utiliser l'outile de netoyage
            continue;
        }

        printf("%s (%c)  Veuillez Enter la cordonne y Colone (entre 1 et 3)  : ", joueur->nom, symbole);// Demande au joueur d'entrer la coordonnée y
        if (scanf("%d", &joueur->position_y) != 1) {// Lit la coordonnée y entrée par le joueur et assurer qu elle est juste
            clearText();// utiliser l'outile de netoyage
            continue;
        }
// Convertit les coordonnées de 1-3 à 0-2 (indices du tableau)
        x = joueur->position_x - 1;
        y = joueur->position_y - 1;
  // Si le coup n'est pas valide
    } while (!is_valid_move(board, x, y));// Continue la boucle tant que le coup n'est pas valide
    // Enregistre le temps a la fin du tour

    clock_t fin = clock();
      double tempsTour = (double)(fin - debut) / CLOCKS_PER_SEC;// Calcule le temps écouler pendant ce tour en secondes
    joueur->temps_total += tempsTour;// Ajoute le temps de ce tour au temps total du joueur
    board[x][y] = symbole;// Place le symbole du joueur ('X' ou 'O') sur le plateau
    printf("\n");// Affiche une ligne vide pour l'espacement
    printBoard(board);// Affiche le plateau mis à jour
}

int checkWin(char board[3][3]) {//Fonction Vérifie s'il y a un gagnant
    for (int i = 0; i < 3; i++) {
             // Boucle sur les 3 lignes
        if (board[i][0] != ' ' && // Si la première case de la ligne n'est pas vide
            board[i][0] == board[i][1] &&// ET que les 3 cases de la ligne sont identiques
            board[i][1] == board[i][2])
            return board[i][0];// Retourne le symbole gagnant ('X' ou 'O')
// Il réalise la même chose que dans le code au dessus mais vérifie les colonnes
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return board[0][i];// Retourne le symbole gagnant ('X' ou 'O')
    }
// CES codes vont vérifier les diagonales
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return board[0][0];
// Deuxième diagonale
    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return board[0][2];

    return 0;
}

/// ================= HISTORIQUE ================= ///

void logMove(FILE *f, int tour, char joueur, int ligne, int colonne) {// Procudure pour enregistrer un coup dans un fichier log
 if (f != NULL) { // Vérifie que le pointeur de fichier n'est pas NULL
    fprintf(f, "Tour %d : Joueur %c joue (%d,%d)\n",tour, joueur, ligne, colonne);// Écrit dans le fichier : numéro du tour, symbole du joueur et coordonnées
}
}
void afficherHistorique(const char *filename) {// Procedure qui il s'affiche les tours avec les coups jouee par les joueur se form de ligne ainsi que le temp
    FILE *f = fopen(filename, "r");// ouvrire le fichier avec le droit de lecture
    char ligne[256];// reserver 256 ligne ce qui assie de remplire 29 partie complete

    printf("\n===== HISTORIQUE DE LA PARTIE =====\n");//afficher la phrase de l'historique au niveau du console
    while (fgets(ligne, sizeof(ligne), f))//boucle while avec la fonction fgets pour saisire son tombee dans le problem de les espaces
        printf("%s", ligne);//afficher les phrases saisies containt le nombre de tour et le coup jouee et le joueur
    printf("=================================\n");// la fin du l'historique

    fclose(f);//fermuture du ficher
}

/// ================= TOUR PAR TOUR ================= ///

void player_turn(char board[3][3], Joueur* J1, Joueur* J2) {// Procudure principale qui gère l'alternance des tours entre les joueurs

    char joueur_mtn = 'X';// Variable qui indique quel joueur doit jouer ('X' commence)
    int tour = 0;// Compteur de tours initialisé à 0

    char filename[100];

    FILE *f = fopen(filename, "w");
    fprintf(f, "Historique De La Partie\n");
  int win=0;
    while (tour < 9&& win==0) {// Boucle qui continue tant qu'il reste des cases vides, maximum 9 tours
        if (joueur_mtn == 'X') {// Si c'est le tour du joueur X
            placement(board, J1, 'X');// Le joueur 1 place son symbole 'X'
            logMove(f, tour + 1, 'X', J1->position_x, J1->position_y); //enregistre la position et le tour du joueur 1 avec le symbole 'X'
            joueur_mtn = 'O';// Change pour le prochain joueur 'O'
        } else {// Sinon c'est le tour du joueur O
            placement(board, J2, 'O');// Le joueur 2 place son symbole 'O'
            logMove(f, tour + 1, 'O', J2->position_x, J2->position_y);//enregistre la position et le tour du joueur 2 avec le symbole 'O'
            joueur_mtn = 'X';// Change pour le prochain joueur 'X'
        }

        tour++;// Incrémente le compteur tours donc cela fait tour = 0 + 1 = 1
          win= checkWin(board);// Vérifie s'il y a un gagnant
    }

   if (win == 'X') {// Si le joueur X a gagné
    printf("\n Bravo %s ! Tu as gagner avec X \n", J1->nom);// Affiche un message de victoire pour le joueur 1
    fprintf(f, "\nGagnant : %s (X)\n", J1->nom);// Il va enregistrer le nom du joueur et aller chercher le nom dans la structure du joueur
}
else if (win == 'O') {// SI c'est le joueur qui a le 0 et qu'il gagne
    printf("\n Le joueur gagnant est : %s (O)\n", J2->nom);// On va afficher le message comme quoi il a gagné
    fprintf(f, "\nGagnant : %s (O)\n", J2->nom);// Ensuite on va prendre le nom du joueur dans ça structure et le marquer dans le fichier
            fclose(filename);// ferme ensuite le fichier
} else{
            printf("\n match nul on ne peut pu jouer le tableau est rempli \n");// On va afficher un message comme quoi les joueurs on réalisé un match nul
            fprintf(f, "\nMatch nul\n");// et entrer dans le fichier Match nul
            fclose(f);// ferme ensuite le fichier
}

 // Si on atteint 9 tours

         fclose(f);// fermer le fichier
    afficherHistorique(filename);// pour afficher a la fin du jeu ce qui ecrit de dont du fichier filename (historique du jeu ,le nombre de tour, nom du joueur )
}

/// ================= MENU ================= ///

int debut() {
    char nb;// Déclaration d'une variable caractère pour stocker la réponse de l'utilisateur
    printf("Bienvenue au TIC TAC TOE\nAppuyez sur 'a' pour commencer : ");// Affiche le message de bienvenue et les instructions
    do{
    scanf(" %c", &nb);// Lit le caractère entré par l'utilisateur (l'espace avant %c ignore les espaces blancs)
    if(nb!='a'||nb!='A'){
    printf("Veuillez entrez la lettre 'a' pour lancer le MORPION\n");//condition pour assurer que nb = a ou A
    }
    }while(nb!='a'&&nb!='A');// boucle do while pour blinder la saisie du char nb
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
    Joueur J1, J2;// Déclaration des deux structures Joueur

    // Cela permet d'afficher les option des menus

    printf("1. Lancer une partie\n");
    printf("2. Quitter\n");
    do{
    scanf("%d", &choix);
    if(choix!=1 && choix!=2){
    printf("Error de saisie veiullez respectez les nombres 1 ou 2\n");//message d'error de saisie
    }
  }while(choix!=1 && choix!=2);// blinder la saisie du choix avec boucle do while

    if (choix == 1) {
        choix2(&J1, &J2);
        J1.temps_total = 0;// Initialise le temps total du joueur 1 à 0.0
        J2.temps_total = 0;// Initialise le temps total du joueur 2 à 0.0

        initBoard(board);// Initialise le plateau de jeu avec les numéros 1-9
        printBoard(board);// Affiche le plateau initial
        player_turn(board, &J1, &J2);// Lance la boucle de jeu avec alternance des tours

        printf("Temps total joueur %s (X) = %.2f secondes\n", J1.nom, J1.temps_total);// Affiche le temps total du joueur 1 avec 2 décimales
        printf("Temps total joueur %s (O) = %.2f secondes\n", J2.nom, J2.temps_total);// Même chose pour le joueur 2

    }

    return 0;
}
