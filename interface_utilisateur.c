#include "biblio.h"


void statistiques() {
    char quitter = 'a';
    do {
        quitter = 'a';
        system("clear");
        // Affichage des informations des défenseurs
        printf("\t =====================DEFENSEURS=====================\n");
        printf("\t +--------------------+---------+----------+--------+\n");
        printf("\t |        Nom         | Portée  |  Dégats  |  Prix  |\n");
        printf("\t +--------------------+---------+----------+--------+\n");
        printf("\t | Pingu-Patrouilleur |    4    |   100    |    50  |\n");
        printf("\t | Flocon  Perce-Ciel |    7    |    60    |   100  |\n");
        printf("\t |   Garde  Polaire   |    1    |   130    |    75  |\n");
        printf("\t |   Loup  Griffeur   |    3    |    25    |    25  |\n");
        printf("\t | Dieu Des Montagnes |   50    |   250    |   750  |\n");
        printf("\t +--------------------+---------+----------+--------+\n\n");

        // Affichage des informations des attaquants
        printf("\t =====================ATTAQUANTS=====================\n");
        printf("\t +--------------------+---------+----------+--------+\n");
        printf("\t |        Nom         |   Vie   | Esquive  |  Gain  |\n");
        printf("\t +--------------------+---------+----------+--------+\n");
        printf("\t | Skieur Frénétique  |    4    |   15%%    |    5   |\n");
        printf("\t |Snowboarder Acrobate|    7    |   30%%    |    7   |\n");
        printf("\t |   Lugiste Barjo    |    1    |    1%%    |   10   |\n");
        printf("\t +--------------------+---------+----------+--------+\n\n");
        printf("\t q pour quitter : ");
        
        if (scanf(" %c", &quitter) != 1) {
            printf("\t Entrée invalide (lettre attendue). Fin du programme.\n");
            exit(4);
        }
        system("clear");
    } while (quitter != 'q');
}


//Affichage de la carte
void afficher_carte(Case** carte, int taillecarte) {
    printf("\t     ");
    for (int i = 0; i < taillecarte; i++) { //graduation en lettre de l'axe x
        
        if (i < 26) {
            printf("%c ", 'a' + i);
        } 
        else {
            printf("%c ", 'A' + (i - 26));
        }
    }
    printf("\n\t     ");
    
    for (int i = 0; i < taillecarte; i++) {
        printf("__");
    }
    
    printf("\n");

    for (int i = 0; i < taillecarte; i++) {
        printf("\t %02d |", i + 1); //graduation en nombre de l'axe y
        
        for (int j = 0; j < taillecarte; j++) {
        
            switch (carte[i][j].type) {
                case 3:
                    printf("%s ", EMOJI_NEIGE);
                    break;
                case 4:
                    printf("%s", EMOJI_PIERRE);
                    break;
                case 5:
                    printf("%s", EMOJI_SAPIN);
                    break;
                case 6:
                    printf("%s", EMOJI_DRAPEAU);
                    break;
                case 7:
                    printf("%s", EMOJI_COURONNE);
                    break;
                case 8:
                    printf("%s ", EMOJI_SKIEUR);
                    break;
                case 9:
                    printf("%s", EMOJI_SNOWBOARDER);
                    break;
                case 10:
                    printf("%s", EMOJI_LUGISTE);
                    break;
                case 11:
                    printf("%s", EMOJI_PINGOUIN);
                    break;
                case 12:
                    printf("%s", EMOJI_BONHOMMENEIGE);
                    break;
                case 13:
                    printf("%s", EMOJI_OURS);
                    break;
                case 14:
                    printf("%s", EMOJI_LOUP);
                    break;
                case 15:
                    printf("%s", EMOJI_DRAGON);
                    break;
                default:
                    exit(1);
            }
        }
        printf("|\n");
    }
    printf("\t     ");
    
    for (int i = 0; i < taillecarte; i++) {
        printf("‾‾");
    }
    
    printf("\n");
}


//Placement des defenseurs
void placement_de_defenseur(Case** carte, int taillecarte, int* flocons, Defenseur* liste_defenseur, int* nb_defenseur) {
    char placer = 'a';
    
    if (*flocons < 25) {
        printf("\t Vous n'avez pas assez de flocons (il faut 100 %s au minimum) (vous avez %d %s ).\n",EMOJI_FLOCON, *flocons, EMOJI_FLOCON);
        sleep(2);
    }
    else { 
        do {
            printf("\t Souhaitez-vous placer un défenseur ?\n\t Vous avez %d %s\n\t o pour oui ou n pour non\n", *flocons, EMOJI_FLOCON);
            printf("\t Votre choix : ");
            
            if (scanf(" %c", &placer) != 1) {
                printf("\t Entrée invalide (lettre attendue). Fin du programme.\n");
                exit(4);
            }

            while (placer != 'o' && placer != 'n') {
                printf("\tValeur incorrecte. Réessayez :\n");
                printf("\t Votre choix : ");
                
                if (scanf(" %c", &placer) != 1) {
                printf("\t Entrée invalide (lettre attendue). Fin du programme.\n");
                exit(4);
                }
            }

            if (placer == 'n') {
                break;
            }

            int choix_defenseur = 0;
            Defenseur nouv_def;

            // Boucle jusqu'à ce que le joueur choisisse un défenseur qu'il peut se payer
            do {
                printf("\n\t Choisissez un défenseur à placer :\n");
                printf("\t 1 - %s Pingu-Patrouilleur (50 %s )\n", EMOJI_PINGOUIN, EMOJI_FLOCON);
                printf("\t 2 - %s Flocon-Perce-Ciel (100 %s )\n",EMOJI_BONHOMMENEIGE, EMOJI_FLOCON);
                printf("\t 3 - %s Garde Polaire (75 %s )\n",EMOJI_OURS, EMOJI_FLOCON);
                printf("\t 4 - %s Loup Griffeur (25 %s )\n",EMOJI_LOUP, EMOJI_FLOCON);
                printf("\t 5 - %s Dieu Des Montagnes (750 %s )\n",EMOJI_DRAGON, EMOJI_FLOCON);
                printf("\t Votre choix : ");

                if (scanf(" %d", &choix_defenseur) != 1) {
                    printf("\t Entrée invalide. Fin du programme.\n");
                    exit(4);
                }

                while (choix_defenseur < 1 || choix_defenseur > 5) {
                    printf("\t Choix invalide. Réessayez :\n");
                    printf("\t Votre choix : ");
                    if (scanf(" %d", &choix_defenseur) != 1) {
                        printf("\t Entrée invalide. Fin du programme.\n");
                        exit(4);
                    }
                }

                // Crée le défenseur selon le choix
                if (choix_defenseur == 1) {
                    nouv_def = constructeur_PinguPatrouilleur(nouv_def);
                    (*nb_defenseur)++;
                    liste_defenseur[*nb_defenseur-1] = nouv_def;
                } 
                else if (choix_defenseur == 2) {
                    nouv_def = constructeur_FloconPerceCiel(nouv_def);
                    (*nb_defenseur)++;
                    liste_defenseur[*nb_defenseur-1] = nouv_def;
                } 
                else if (choix_defenseur == 3) {
                    nouv_def = constructeur_GardePolaire(nouv_def);
                    (*nb_defenseur)++;
                    liste_defenseur[*nb_defenseur-1] = nouv_def;
                }
                else if (choix_defenseur == 4) {
                    nouv_def = constructeur_LoupGriffeur(nouv_def);
                    (*nb_defenseur)++;
                    liste_defenseur[*nb_defenseur-1] = nouv_def;
                }
                else {
                    nouv_def = constructeur_DieuDesMontagnes(nouv_def);
                    (*nb_defenseur)++;
                    liste_defenseur[*nb_defenseur-1] = nouv_def;
                }

                if (*flocons < nouv_def.prix) {
                    printf("\t Vous n'avez pas assez de flocons(%s ) (%d requis, %d disponibles).\n",EMOJI_FLOCON, nouv_def.prix, *flocons);
                    printf("\t Souhaitez-vous choisir un autre défenseur ?\n \t o pour oui ou n pour non\n");
                    printf("\t Votre choix : ");
                    
                    if (scanf(" %c", &placer) != 1) {
                        printf("\t Entrée invalide (lettre attendue). Fin du programme.\n");
                        exit(4);
                    }
                    if (placer == 'n') {
                        return;
                    }
                }

            } while (*flocons < nouv_def.prix);

            // Lecture coordonnées de placement
            int coord_x_index = 0, coord_y = 0;
            char coord_x_char;
            do {
                printf("\n\t Choisissez une coordonnée x (lettre a-%c) :\n", 'A' + taillecarte - 27);
                printf("\t Votre choix : ");
                
                if (scanf(" %c", &coord_x_char) != 1) {
                    printf("\t Entrée invalide. Fin du programme.");
                    exit(4);
                }
                
                if (coord_x_char >= 'a' && coord_x_char <= 'z') {
                    coord_x_index = coord_x_char - 'a';
                }
                else if (coord_x_char >= 'A' && coord_x_char <= 'Z') {
                    coord_x_index = coord_x_char - 'A' + 26;
                }
                else {
                    coord_x_index = -1;
                }
            } while (coord_x_index < 0 || coord_x_index >= taillecarte);
            
            nouv_def.coordx = coord_x_index;
            
            liste_defenseur[*nb_defenseur-1].coordx = coord_x_index;
            
            do {
                printf("\t Choisissez une coordonnée y (entre 1 et %d) :\n", taillecarte);
                printf("\t Votre choix : ");
                
                if (scanf(" %d", &coord_y) != 1) {
                    printf("\t Entrée invalide. Fin du programme.\n");
                    exit(4);
                }
                coord_y -= 1;
            } while (coord_y < 0 || coord_y >= taillecarte);
            
            nouv_def.coordy = coord_y;
            
            liste_defenseur[*nb_defenseur-1].coordy = coord_y;
            
            if (carte[coord_y][coord_x_index].type != 0 && carte[coord_y][coord_x_index].type != 1 && carte[coord_y][coord_x_index].type != 2 && carte[coord_y][coord_x_index].type != 3) {
                printf("\t Cette case n'est pas de la neige. Recommencez.\n\n");
                continue;
            }

            // Placement du défenseur
            carte[coord_y][coord_x_index].type = choix_defenseur + 10;
            carte[coord_y][coord_x_index].defenseur = nouv_def;
            *flocons -= nouv_def.prix;
            
            afficher_carte(carte, taillecarte);
            
            printf("\n\t Défenseur placé. Il vous reste %d %s .\n", *flocons, EMOJI_FLOCON);

        } while (placer != 'n' && *flocons >= 50);
    }
}


//Fonction de partie
void lancerpartie(Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague) {
    
    int colonneCouronne, colonneDebut;
    int compteur = 0;
    char choix;

    if(*taillecarte == 0) {
        // Génération de la carte (entre 30 et 45) et du chemin
        *taillecarte = rand() % 16 + 30;
        creer_carte(carte, *taillecarte);
        creer_chemin(*carte, *taillecarte);
    }
    printf("\n\t Pour cette partie, la carte est de taille %d x %d\n\n\n", *taillecarte, *taillecarte);
    afficher_carte(*carte, *taillecarte);

    for (int i = 0; i < *taillecarte; i++) {
        if ((*carte)[0][i].type == 6) {
            colonneDebut = i;
            break;
        }
    }
    for (int j = 0; j < *taillecarte; j++) {
        if ((*carte)[*taillecarte - 1][j].type == 7) {
            colonneCouronne = j;
            break;
        }
    }
	
	for(; *vague <= 8; (*vague)++) { //Boucle des vagues
		compteur = 0;
		placement_de_defenseur(*carte, *taillecarte, flocons, *defenseurs, nbDefenseurs);
		generer_attaquant(*carte, colonneDebut, ennemis, nbEnnemis, &compteur, vague);
		
		while ((*carte)[*taillecarte-1][colonneCouronne].type == 7 && *nbEnnemis > 0) {//Boucle d'avancement pas a pas (tours)
		    usleep(400000); // Pause
			
		    deplacement_attaquant(*carte, *ennemis, *nbEnnemis, *taillecarte);
		    attaquer_defenseurs(*carte, *defenseurs, nbDefenseurs, *ennemis, nbEnnemis, score, flocons);

		    // Vérifier si un ennemi atteint la couronne
		    for (int i = 0; i < *nbEnnemis; i++) {
		    
                        if ((*ennemis)[i].y == *taillecarte - 1){
		            defaite(score);
        		    return;
		        }
		    }

		    // Génère un nouvel attaquant seulement si la case est vide
		    if ((*carte)[0][colonneDebut].type == 6 && compteur<=8){
		        generer_attaquant(*carte, colonneDebut, ennemis, nbEnnemis, &compteur, vague);
		    }
		    
		    system("clear");
		    afficher_carte(*carte, *taillecarte);
		}
		printf("\n \t Score = %d %s \n", *score, EMOJI_TROPHEE);
		sleep(2);
		
		do{
		    printf("\t Souhaitez-vous sauvegarder la partie et retourner au menu principal ? (o pour oui ou n pour non)\n");
		    printf("\t Votre choix : ");
		    
                    if (scanf(" %c", &choix) != 1) {
                        printf("\t Entrée invalide (lettre attendue). Fin du programme.\n");
                        exit(4);
                    }
                    
                    if (choix == 'o') { //appel a la fct sauvegarde pour relancer le jeu plus tard
                        sauvegarde("sauvegarde.txt", *carte, *taillecarte, *defenseurs, *nbDefenseurs, *ennemis, *nbEnnemis, *score, *flocons, *vague);
                        printf("\t Partie sauvegardée !\n");
                        sleep(1);
                        printf(" \t Retour menu principal.\n");
                        usleep(333333);
                        printf(".");
                        usleep(333333);
                        printf(".\n");
                        usleep(333333);
                        return;
                    }
                } while (choix != 'o' && choix != 'n');
	}
	victoire(score);  
}


//Interface utilisateur qui demande a l'utilisateur de faire les choix de partie possible
int menuDemarrage(){
    int choix_menu=0; //Variable pour stocker le choix de l'utilisateur
    
    printf("\n \t === %s%s%s OPERATION FLOCON %s %s%s === \n", EMOJI_PINGOUIN, EMOJI_BONHOMMENEIGE, EMOJI_OURS, EMOJI_SKIEUR, EMOJI_SNOWBOARDER, EMOJI_LUGISTE);
    printf("\n \t =============== KESAKO ? ============= \n");
    printf("\n \t ❄️ Opération Flocon❄️  est un jeu de tower defense se déroulant dans un univers hivernal. \n \t Le joueur doit défendre une couronne centrale contre des vagues d’ennemis composées de skieurs \n \t frénétiques⛷️, snowboarders acrobates🏂 et lugistes barjos🛷. Pour se défendre, il peut compter sur \n \t des pingu-patrouilleurs🐧, des flocons perce-ciel⛄, des gardes polaires🐻, des loups griffeurs🐺 \n \t et le dieu des montagnes🐉 qu’il peut positionner stratégiquement sur la carte. La carte de jeu est \n \t générée aléatoirement à chaque partie, avec un chemin unique menant à la couronne👑, que les \n \t ennemis empruntent automatiquement. Le joueur peut placer ses défenseurs autour de celui-ci, \n \t en tenant compte des contraintes de positionnement (les défenseurs peuvent être posés \n \t uniquement sur des cases de neige◻️, mais pas sur les sapins🌲et les rochers🪨). \n \t L’objectif principal est de repousser les vagues successives d’ennemis en optimisant la position et le \n \t type des défenseurs, tout en gérant les ressources disponibles. Le joueur commence avec 75❄️ (flocons) \n \t pour positionner ses défenseurs et avec 0🏆(points), À chaque ennemi éliminé, il gagne un🏆. \n \t A chaque vague, il gagne des❄️  en fonction du nombres d’attaquants battus et de leur type (⛷️,🏂,🛷). \n");
    printf("\n \t =========== MENU PRINCIPAL =========== \n");
    printf("\n \t 1 - ✨ Nouvelle Partie \t \n");
    printf("\n \t 2 - ♻️  Reprendre une partie \t \n");
    printf("\n \t 3 - 📊 Menu des statistiques des personnages \t \n");
    printf("\n \t 4 - 👋 Quitter \t \n");
    printf("\n \t Votre choix : ");
    if (scanf(" %d", &choix_menu) != 1) {
        printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
        exit(4);
    }

    while (choix_menu < 1 || choix_menu > 4) {
        printf("\n \t Veuillez entrer une valeur correcte : \n");
        printf("\n \t 1 - ✨ Nouvelle Partie \t \n");
        printf("\n \t 2 - ♻️  Reprendre une partie \t \n");
        printf("\n \t 3 - 📊 Menu des statistiques des personnages \t \n");
        printf("\n \t 4 - 👋 Quitter \t \n");
        printf("\n \t Votre choix : ");
        if (scanf(" %d", &choix_menu) != 1) {
                printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
                exit(4);
            }
    }
    return choix_menu; // Retourne le choix de l'utilisateur
}


//Fonction appelée en cas de défaite
void defaite(int* score) {
    printf("\n \t 😢 Vous avez perdu ! 😢\n");
    printf("\n \t Score = %d %s \n", *score, EMOJI_TROPHEE);
    sleep(2);
    printf(" \t Retour menu principal.\n");
    usleep(333333);
    printf(".");
    usleep(333333);
    printf(".\n");
    usleep(333333);
}


//Fonction appelée en cas de victoire
void victoire(int* score) {
    printf("\n \t 🥳 Vous avez gagné ! 🥳\n");
    printf("\n \t Score = %d %s \n", *score, EMOJI_TROPHEE);
    sleep(2);
    printf(" \t Retour menu principal.\n");
    usleep(333333);
    printf(".");
    usleep(333333);
    printf(".\n");
    usleep(333333);
}
