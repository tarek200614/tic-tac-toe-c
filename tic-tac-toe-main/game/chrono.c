#include <stdio.h>
#include <time.h>

int main() {

    char plateau[3][3];
    char joueur = 'X';
    int ligne, colonne;
    int i, j;

    double tempsJoueurX = 0.0;
    double tempsJoueurO = 0.0;

    // Initialisation du plateau à vide
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            plateau[i][j] = ' ';
        }
    }

    int partieFinie = 0;

    while (!partieFinie) {

        // Affichage du plateau
        printf("\n");
        for (i = 0; i < 3; i++) {
            printf(" %c | %c | %c\n", plateau[i][0], plateau[i][1], plateau[i][2]);
            if (i < 2) printf("---|---|---\n");
        }
        printf("\n");

        // ----- Début du chronomètre -----
        clock_t debut = clock();

        // Saisie du coup
        printf("Joueur %c, entrez la ligne (0 à 2) : ", joueur);
        scanf("%d", &ligne);

        printf("Joueur %c, entrez la colonne (0 à 2) : ", joueur);
        scanf("%d", &colonne);

        // ----- Fin du chronomètre -----
        clock_t fin = clock();
        double tempsTour = (double)(fin - debut) / CLOCKS_PER_SEC;

        // Ajout du temps au bon joueur
        if (joueur == 'X') {
            tempsJoueurX += tempsTour;
        } else {
            tempsJoueurO += tempsTour;
        }

        // Vérification du coup valide
        if (ligne < 0 || ligne > 2 || colonne < 0 || colonne > 2 || plateau[ligne][colonne] != ' ') {
            printf("Coup invalide, veuillez recommencer.\n");
            continue;
        }

        // Placement dans le plateau
        plateau[ligne][colonne] = joueur;

        // Vérification victoire
        for (i = 0; i < 3; i++) {
            if (plateau[i][0] == joueur && plateau[i][1] == joueur && plateau[i][2] == joueur) partieFinie = 1;
            if (plateau[0][i] == joueur && plateau[1][i] == joueur && plateau[2][i] == joueur) partieFinie = 1;
        }
        if (plateau[0][0] == joueur && plateau[1][1] == joueur && plateau[2][2] == joueur) partieFinie = 1;
        if (plateau[0][2] == joueur && plateau[1][1] == joueur && plateau[2][0] == joueur) partieFinie = 1;

        // Vérification égalité
        int plein = 1;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (plateau[i][j] == ' ') plein = 0;
            }
        }
        if (plein && !partieFinie) {
            printf("Match nul !\n");
            break;
        }

        // Si victoire
        if (partieFinie) {
            printf("Le joueur %c a gagné !\n", joueur);
            break;
        }

        // Changement de joueur
        if (joueur == 'X') joueur = 'O';
        else joueur = 'X';
    }

    // Affichage des temps
    printf("\n--- Temps total utilisé ---\n");
    printf("Temps du joueur X : %.2f secondes\n", tempsJoueurX);
    printf("Temps du joueur O : %.2f secondes\n", tempsJoueurO);

    return 0;
}