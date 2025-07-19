#include "biblio.h"
#include <unistd.h> //Pour éviter les warnings a la compilation

int main() {
    system("clear");
    srand(time(NULL));

    // Initialisation des variables
    int jeu_en_cours = 1; // Variable pour contrôler la boucle principale
    int taillecarte = 0;
    int nbDefenseurs = 0;
    int nbEnnemis = 0;
    int score = 0;
    int flocons = 0;
    int vague = 1;
    int* ptrtaillecarte = &taillecarte;
    Case** carte = NULL;
    EnnemiActif* ennemis[80];
    Defenseur* defenseurs = (Defenseur*)malloc(100 * sizeof(Defenseur)); // Pre-allocation d'espace pour 100 defenseurs
    if (defenseurs == NULL) {
        printf("\t Erreur d'allocation mémoire pour les défenseurs\n");
        exit(2);
    }

    while (jeu_en_cours == 1) {
        int choix_menu = menuDemarrage(); // Affiche le menu principal et récupère le choix

        switch (choix_menu) {
            case 1:
                remove("sauvegarde.txt");
                // Réinitialiser les variables
                taillecarte = 0;
                nbDefenseurs = 0;
                nbEnnemis = 0;
                score = 0;
                flocons = 75;
                vague = 1;
                // Libérer la mémoire allouée pour la carte et les ennemis si nécessaire
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, ennemis, &nbEnnemis, &score, &flocons, &vague); // Lance une nouvelle partie
                system("make");
                system("clear");
                break;
            case 2:
                chargement("sauvegarde.txt", &carte, &taillecarte, &defenseurs, &nbDefenseurs, ennemis, &nbEnnemis, &score, &flocons, &vague);
                vague += 1;
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, ennemis, &nbEnnemis, &score, &flocons, &vague); // Reprend la partie chargée
                system("make");
                system("clear");
                break;
            case 3:
                statistiques();
                system("make");
                system("clear");
                break;
            case 4:
                printf("\n\t A plus 👋😊\n\n");
                jeu_en_cours = 0; // Quitte la boucle principale
                free(defenseurs);
                defenseurs = NULL;
                return 0;
            default:
                printf("\t Choix invalide. Veuillez réessayer.\n");
        }
    }
    // Libération de la mémoire
    free(defenseurs);
    defenseurs = NULL;

    free(*ennemis);
    *ennemis = NULL;

    for (int i = 0; i < *ptrtaillecarte; i++) {
        free(*(carte + i));
    }

    free(*carte);
    *carte = NULL;

    return 0;
}
