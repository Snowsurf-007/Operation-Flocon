#include "biblio.h"

//Affichage de la carte
void afficher_carte(Case** carte, int taillecarte) {
    printf("    ");
    for (int i = 0; i < taillecarte; i++) { //graduation en lettre de l'axe x
        
        if (i < 26) {
            printf("%c ", 'a' + i);
        } 
        else {
            printf("%c ", 'A' + (i - 26));
        }
    }
    printf("\n    ");
    
    for (int i = 0; i < taillecarte; i++) {
        printf("__");
    }
    
    printf("\n");

    for (int i = 0; i < taillecarte; i++) {
        printf("%02d |", i + 1); //graduation en nombre de l'axe y
        
        for (int j = 0; j < taillecarte; j++) {
        
            switch (carte[i][j].type) {
                case 0:
                case 1:
                case 2:
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
                default:
                    exit(1);
            }
        }
        printf("|\n");
    }
    printf("    ");
    
    for (int i = 0; i < taillecarte; i++) {
        printf("‾‾");
    }
    
    printf("\n");
}

//Placement des defenseurs
void placement_de_defenseur(Case** carte, int taillecarte, int* flocons, Defenseur* liste_defenseur, int* nb_defenseur) {
    int placer = -1;
    
    do {
        printf("\t Souhaitez-vous placer un défenseur ?\n\t Vous avez %d %s\n\t 1 pour oui ou 0 pour non\n", *flocons, EMOJI_FLOCON);
        printf("\t Votre choix : ");
        if (scanf(" %d", &placer) != 1) {
            printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
            exit(4);
        }

        while (placer != 0 && placer != 1) {
            printf("\tValeur incorrecte. Réessayez :\n");
            printf("\t Votre choix : ");
            if (scanf(" %d", &placer) != 1) {
                printf("\tEntrée invalide (entier attendu). Fin du programme.\n");
                exit(4);
            }
        }

        if (placer == 0) {
            break;
        }

        int choix_defenseur = 0;
        Defenseur nouv_def;

        // Boucle jusqu'à ce que le joueur choisisse un défenseur qu'il peut se payer
        do {
            printf("\n\t Choisissez un défenseur à placer :\n");
            printf("\t 1 - Pingu-Patrouilleur (100 %s )\n", EMOJI_FLOCON);
            printf("\t 2 - Flocon-Perce-Ciel (200 %s )\n", EMOJI_FLOCON);
            printf("\t 3 - Garde Polaire (150 %s )\n", EMOJI_FLOCON);
            printf("\t Votre choix : ");

            if (scanf(" %d", &choix_defenseur) != 1) {
                printf("\t Entrée invalide. Fin du programme.\n");
                exit(4);
            }

            while (choix_defenseur < 1 || choix_defenseur > 3) {
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
            else {
                nouv_def = constructeur_GardePolaire(nouv_def);
                (*nb_defenseur)++;
                liste_defenseur[*nb_defenseur-1] = nouv_def;
            }

            if (*flocons < nouv_def.prix) {
                printf("\t Vous n'avez pas assez de flocons(%s ) (%d requis, %d disponibles).\n",EMOJI_FLOCON, nouv_def.prix, *flocons);
                printf("\t Souhaitez-vous choisir un autre défenseur ?\n \t 1 pour oui ou 0 pour non\n");
                printf("\t Votre choix : ");
                
                if (scanf(" %d", &placer) != 1 || (placer != 0 && placer != 1)) {
                    printf("\t Entrée invalide. Fin du programme.\n");
                    exit(4);
                }
                if (placer == 0) {
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

    } while (placer == 1);
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
    printf("\n\t Pour cette partie, la carte est de taille %d x %d\n\n", *taillecarte, *taillecarte);
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
	
	for(; *vague < 11; (*vague)++) { //Boucle des vagues
		compteur = 0;
		placement_de_defenseur(*carte, *taillecarte, flocons, *defenseurs, nbDefenseurs);
		generer_attaquant(*carte, colonneDebut, ennemis, nbEnnemis, &compteur, vague);
		
		while ((*carte)[*taillecarte-1][colonneCouronne].type == 7 && *nbEnnemis > 0) {//Boucle d'avancement pas a pas (tours)
		    usleep(400000); // Pause
			
		    deplacement_attaquant(*carte, *ennemis, *nbEnnemis, *taillecarte);
		    attaquer_defenseurs(*carte, *defenseurs, nbDefenseurs, *ennemis, nbEnnemis, score);

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
		(*flocons) += 50;
		printf("\n \tScore=%d\n", *score);
		sleep(2);
		
		do{
		    printf("\t Souhaitez-vous sauvegarder la partie ? (o/n)\n");
		    printf("\t Votre choix : ");
		    
                    if (scanf(" %c", &choix) != 1) {
                        printf("\t Entrée invalide (lettre attendue). Fin du programme.\n");
                        exit(4);
                    }
                    
                    if (choix == 'o') { //appel a la fct sauvegarde pour relancer le jeu plus tard
                        sauvegarde("sauvegarde.txt", *carte, *taillecarte, *defenseurs, *nbDefenseurs, *ennemis, *nbEnnemis, *score, *flocons, *vague);
                        printf("\t Partie sauvegardée !\n");
                        sleep(2);
                        return;
                    }
                } while (choix != 'o' && choix != 'n');
	}
	victoire(score);  
}

//Interface utilisateur qui demande a l'utilisateur de faire les choix de partie possible
int menuDemarrage(){
    int choix_menu=0; //Variable pour stocker le choix de l'utilisateur
    
    printf("\n \t=== %s%s%s OPERATION FLOCON %s %s%s === \n", EMOJI_PINGOUIN, EMOJI_BONHOMMENEIGE, EMOJI_OURS, EMOJI_SKIEUR, EMOJI_SNOWBOARDER, EMOJI_LUGISTE);

    printf("\n \t=== MENU PRINCIPAL === \n");
    printf("\n \t Nouvelle Partie (1) \t \n");
    printf("\n \t Reprendre une partie (2) \t \n");
    printf("\n \t Quitter (3) \t \n");
    printf("\n \t Votre choix : ");
    if (scanf(" %d", &choix_menu) != 1) {
        printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
        exit(4);
    }

    while (choix_menu < 1 || choix_menu > 3) {
        printf("\n \t Veuillez entrer une valeur correcte : \n");
        printf("\t 1 pour démarrer une nouvelle partie \n");
        printf("\t 2 pour reprendre une ancienne partie \n");
        printf("\t 3 pour quitter le jeu \n");
        printf("\t Votre choix : ");
        if (scanf(" %d", &choix_menu) != 1) {
                printf("\t Entrée invalide (entier attendu). Fin du programme.\n");
                exit(4);
            }
    }
    return choix_menu; // Retourne le choix de l'utilisateur
}

//Fonction appelée en cas de défaite
void defaite(int* score) {
    printf("\n \t== Vous avez perdu ! ==\n");
    printf("\n \tScore=%d\n", *score);
    sleep(2);
    printf("\n \tRetour au menu principal...\n");
    sleep(2);
}

//Fonction appelée en cas de victoire
void victoire(int* score) {
    printf("\n \t== Vous avez gagné ! ==\n");
    printf("\n \tScore=%d\n", *score);
    sleep(2);
    printf("\n \tRetour au menu principal...\n");
    sleep(2);
}
