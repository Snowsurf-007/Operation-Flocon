//inclusion des bibliothèques nécessaires
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

// Définitions des constantes et structures
#define EMOJI_NEIGE "\xE2\x97\xBB\xEF\xB8\x8F"
#define EMOJI_PIERRE "\xF0\x9F\xAA\xA8"
#define EMOJI_DRAPEAU "\xF0\x9F\x9A\xA9"
#define EMOJI_SAPIN "\xF0\x9F\x8C\xB2"
#define EMOJI_PINGOUIN "\xF0\x9F\x90\xA7"
#define EMOJI_BONHOMMENEIGE "\xE2\x9B\x84"
#define EMOJI_OURS "\xF0\x9F\x90\xBB"
#define EMOJI_SKIEUR "\xE2\x9B\xB7\xEF\xB8\x8F"
#define EMOJI_SNOWBOARDER "\xF0\x9F\x8F\x82"
#define EMOJI_LUGISTE "\xF0\x9F\x9B\xB7"
#define EMOJI_COURONNE "\xF0\x9F\x91\x91"
#define EMOJI_FLOCON "\xE2\x9D\x84\xEF\xB8\x8F"

//On définit les structures
typedef enum { //Enumeration pour les types de cases
    NEIGE=0,
    PIERRE=4,
    SAPIN=5,
    DRAPEAU=6,
    COURONNE=7,
    SKIEUR=8,
    SNOWBOARDER=9,
    LUGISTE=10,
    PINGOUIN=11,
    BONHOMMENEIGE=12,
    OURS=13
} TypeCase;

typedef struct {
    int portee;
    int degats;
    int prix;
    int coordx;
    int coordy;
} Defenseur;

typedef struct {
    TypeCase type;
    int x;
    int y;
    Defenseur defenseur;
} Case;

typedef struct {
    int vie;
    int gain;
    int coordx;
    int coordy;
} Attaquant;

typedef struct {
    Attaquant attaquant;
    int x;
    int y;
} EnnemiActif;

// Prototypes des fonctions
Defenseur constructeur_PinguPatrouilleur(Defenseur a);
Defenseur constructeur_FloconPerceCiel(Defenseur a);
Defenseur constructeur_GardePolaire(Defenseur a);
Attaquant constructeur_SkieurFrenetique(Attaquant a);
Attaquant constructeur_SnowboarderAcrobate(Attaquant a);
Attaquant constructeur_LugisteBarjo(Attaquant a);
int calculerDistance(int x1, int y1, int x2, int y2);
void attaquer_defenseurs(Case** carte, Defenseur* defenseurs, int* nbDefenseurs, EnnemiActif* ennemis, int* nbEnnemis, int* score);
void placement_de_defenseur(Case** carte, int taillecarte, int* flocons, Defenseur* liste_defenseur, int* nb_defenseur);
void afficher_carte(Case** carte, int taillecarte);
void creer_carte(Case*** carte, int taillecarte);
void creer_chemin(Case** carte, int taillecarte);
void deplacement_attaquant(Case** carte, EnnemiActif* ennemis, int nbEnnemis, int taillecarte);
void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis, int* compteur, int* vague);
void chargement(const char* nom_fichier, Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague);
void sauvegarde(const char* nom_fichier, Case** carte, int taillecarte, Defenseur* defenseurs, int nbDefenseurs, EnnemiActif* ennemis, int nbEnnemis, int score, int flocons, int vague);
void lancerpartie(Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague);
int menuDemarrage();
void defaite(int* score);
void victoire(int* score);
void nettoyer_cache();

//Fonctions constructrices
Defenseur constructeur_PinguPatrouilleur(Defenseur a) {
    a.portee=3;
    a.degats=60;
    a.prix=100;
    return a;
}

Defenseur constructeur_FloconPerceCiel(Defenseur a) {
    a.portee=6;
    a.degats=40;
    a.prix=200;
    return a;
}

Defenseur constructeur_GardePolaire(Defenseur a) {
    a.portee=1;
    a.degats=80;
    a.prix=150;
    return a;
}

Attaquant constructeur_SkieurFrenetique(Attaquant a) { // Attaquant rapide et faible
    a.vie=300;
    a.gain=20;
    return a;
}

Attaquant constructeur_SnowboarderAcrobate(Attaquant a) { // Attaquant vitesse moyenne, vie moyenne
    a.vie=600;
    a.gain=30;
    return a;
}

Attaquant constructeur_LugisteBarjo(Attaquant a) { // Attaquant lent et résistant
    a.vie=2000;
    a.gain=50;
    return a;
}

//Fonctions

//Fonction nettoyage cache 
void nettoyer_cache() {
    int ch;
    
    while ((ch = getchar()) != '\n' && ch != EOF); // Nettoyer le buffer
    // Cela consommera tous les caractères jusqu'à ce qu'une nouvelle ligne ou une fin de fichier (EOF) soit trouvée.
}

// Fonction pour calculer la distance euclidienne entre deux unités
int calculerDistance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int euclide = sqrt(pow(dx, 2) + pow(dy, 2));
    return euclide;
}

//Fonction permettant au défenseurs de mettre des dégâts aux attaquants
void attaquer_defenseurs(Case** carte, Defenseur* defenseurs, int* nbDefenseurs, EnnemiActif* ennemis, int* nbEnnemis, int* score) {

    for (int i = 0; i < *nbDefenseurs; i++) {
       	Defenseur def = defenseurs[i]; // Pointeur vers le défenseur actuel
        for (int j = 0; j < *nbEnnemis; j++) {
            EnnemiActif* ennemi = &ennemis[j]; // Ennemi actuel

            if (ennemi->attaquant.vie <= 0) {
                continue;
            }
            
            printf("def.coordx = %d, def.coordy = %d, ennemi->x = %d, ennemi->y = %d \n", def.coordx, def.coordy, ennemi->x, ennemi->y);

            // Calcul de la distance entre le défenseur et l'ennemi
            int distance = calculerDistance(def.coordx, def.coordy, ennemi->x, ennemi->y);
		
						printf("portée = %d, distance = %d, \n", def.portee, distance);
		
            // Si l'ennemi est à portée
            if (distance <= def.portee) {
                    
                ennemi->attaquant.vie -= def.degats;
                
                // Si l'ennemi est éliminé
                if (ennemi->attaquant.vie <= 0) {
                    int x1 = ennemi->x;
                    int y1 = ennemi->y;
                    
                    carte[x1][y1].type = 6; // Remet la case à "chemin"
                    (*score)++; // Incrémente le score

                    // Supprime l'ennemi de la liste
                    for (int k = j; k < *nbEnnemis - 1; k++) {
                        ennemis[k] = ennemis[k + 1];
                    }
                    
                    (*nbEnnemis)--; // Réduit le nombre d'ennemis
                    j--; // Réajuste l'indice pour ne pas sauter un ennemi
                }
            } 
        }
    }
}

void creer_carte(Case*** carte, int taillecarte) {
    *carte = (Case**)malloc(taillecarte * sizeof(Case*));
    
    for (int i = 0; i < taillecarte; i++) {
        (*carte)[i] = (Case*)malloc(taillecarte * sizeof(Case));
        
        if ((*carte)[i] == NULL) { //Si problème de malloc
            printf("\t Erreur d'allocation mémoire\n");
            exit(2);
        }
        
        for (int j = 0; j < taillecarte; j++) {
            (*carte)[i][j].type = rand() % 6;
            
	    if (((*carte)[i][j].type == 0) || ((*carte)[i][j].type == 1) || ((*carte)[i][j].type == 2)){
	        (*carte)[i][j].type = 3;
	    }
        }
    }
}

void creer_chemin(Case** carte, int taillecarte) {
    int j = rand() % (taillecarte - 6) + 3;
    int direction, directionprecedente = 0;

    carte[0][j].type = 6; //première et deuxième case = drapeau pour éviter de partir sur le cote des le début
    carte[1][j].type = 6; 

    for (int i = 2; i < taillecarte - 1; i++) {
    
        do {
            direction = rand() % 3 - 1;
        } while (directionprecedente == -direction);

        directionprecedente = direction;
        int nouvellecolonne = j + direction;

        if (nouvellecolonne < 0) { //Si ça dépasse a gauche
            nouvellecolonne = 0;
        }
        
        if (nouvellecolonne >= taillecarte) { //Si ça dépasse a droite
            nouvellecolonne = taillecarte - 1;
        }

        if (direction != 0 && i > 0) {
            carte[i - 1][nouvellecolonne].type = 6;
        }

        j = nouvellecolonne;
        carte[i][j].type = 6;
    }
    carte[taillecarte - 1][j].type = 7; //Couronne sur la case d'arrivée
}

void deplacement_attaquant(Case** carte, EnnemiActif* ennemis, int nbEnnemis, int taillecarte) {
    for (int i = 0; i < nbEnnemis; i++){
        int x = ennemis[i].x;
        int y = ennemis[i].y;

        // Sauvegarde le type pour pouvoir déplacer
        int type_attaquant = carte[x][y].type;

        // Déplacement bas > droite > gauche
        if (x+1 < taillecarte && (carte[x+1][y].type == 6 || carte[x+1][y].type == 7)){
            carte[x+1][y].type = type_attaquant;
            carte[x][y].type = 6;
            ennemis[i].x++;
        }
        else if (y+1 < taillecarte && (carte[x][y+1].type == 6 || carte[x][y+1].type == 7)){
            carte[x][y+1].type = type_attaquant;
            carte[x][y].type = 6;
            ennemis[i].y++;
        }
        else if (y-1>=0 && (carte[x][y-1].type==6 || carte[x][y-1].type==7)){
            carte[x][y-1].type=type_attaquant;
            carte[x][y].type=6;
            ennemis[i].y--;
        }
    }
}

void generer_attaquant(Case** carte, int debut, EnnemiActif** ennemis, int* nbEnnemis, int* compteur, int* vague) {
    // Ne pas dépasser 8 ennemis par vague
    if (*compteur >= 8 || *nbEnnemis >= 80) {
        return;
    }

    int attaquant;
    Attaquant nouv_ennemi;

    // Choisir le type d'ennemi selon la vague
    if (*vague <= 2) {
        attaquant = 0;
    } else if (*vague <= 4) {
        attaquant = rand() % 2;
    } else {
        attaquant = rand() % 3;
    }

    // Construire l'ennemi correspondant et affecter le type de case
    switch (attaquant) {
        case 0:
            nouv_ennemi = constructeur_SkieurFrenetique(nouv_ennemi);
            carte[0][debut].type = 8;
            break;
        case 1:
            nouv_ennemi = constructeur_SnowboarderAcrobate(nouv_ennemi);
            carte[0][debut].type = 9;
            break;
        case 2:
            nouv_ennemi = constructeur_LugisteBarjo(nouv_ennemi);
            carte[0][debut].type = 10;
            break;
    }

    // Référence vers un ennemi actif dans le tableau prédéfini
    static EnnemiActif pool[80]; // Zone mémoire statique (si appelée plusieurs fois)
    EnnemiActif* nouveau = &pool[*nbEnnemis];

    nouveau->attaquant = nouv_ennemi;
    nouveau->x = 0;
    nouveau->y = debut;

    ennemis[*nbEnnemis] = nouveau;

    (*nbEnnemis)++;
    (*compteur)++;
}


//Reprise d'une partie
void chargement(const char* nom_fichier, Case*** carte, int* taillecarte, Defenseur** defenseurs, int* nbDefenseurs, EnnemiActif** ennemis, int* nbEnnemis, int* score, int* flocons, int* vague) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("\t Erreur : le fichier %s n'existe pas \n", nom_fichier);    
        exit(3);
    }

    fscanf(fichier, "%d", taillecarte);

    *carte = (Case**)malloc(*taillecarte * sizeof(Case*));
    for (int i = 0; i < *taillecarte; i++) {
        (*carte)[i] = (Case*)malloc(*taillecarte * sizeof(Case));
    }

    for (int i = 0; i < *taillecarte; i++) {
        for (int j = 0; j < *taillecarte; j++) {
            fscanf(fichier, "%d", &((*carte)[i][j].type));
        }
    }

    fscanf(fichier, "%d", nbDefenseurs);
    *defenseurs = (Defenseur*)malloc(*nbDefenseurs * sizeof(Defenseur));
    for (int i = 0; i < *nbDefenseurs; i++) {
        fscanf(fichier, "%d %d %d %d %d", &(*defenseurs)[i].portee, &(*defenseurs)[i].degats, &(*defenseurs)[i].prix, &(*defenseurs)[i].coordx, &(*defenseurs)[i].coordy);
    }

    fscanf(fichier, "%d", nbEnnemis);
    *ennemis = (EnnemiActif*)malloc(*nbEnnemis * sizeof(EnnemiActif));
    for (int i = 0; i < *nbEnnemis; i++) {
        fscanf(fichier, "%d %d %d", &(*ennemis)[i].attaquant.vie, &(*ennemis)[i].x, &(*ennemis)[i].y);
    }

    fscanf(fichier, "%d", score);
    fscanf(fichier, "%d", flocons);
    fscanf(fichier, "%d", vague);

    fclose(fichier);
}

//Sauvegarde d'une partie
void sauvegarde(const char* nom_fichier, Case** carte, int taillecarte, Defenseur* defenseurs, int nbDefenseurs, EnnemiActif* ennemis, int nbEnnemis, int score, int flocons, int vague) {
    // Ouverture du fichier en mode écriture
    FILE* fichier = fopen(nom_fichier, "w");

    // Vérification du bon déroulement de l'ouverture
    if (fichier == NULL) {
        printf("\t Erreur : le fichier %s n'a pas pu être ouvert \n", nom_fichier);
        exit(3);
    }

    // Sauvegarde des dimensions de la carte
    fprintf(fichier, "%d\n", taillecarte);

    // Sauvegarde de la carte
    for (int i = 0; i < taillecarte; i++) {
        for (int j = 0; j < taillecarte; j++) {
            fprintf(fichier, "%d ", carte[i][j].type);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarde des défenseurs
    fprintf(fichier, "%d\n", nbDefenseurs); // Nombre de défenseurs
    for (int i = 0; i < nbDefenseurs; i++) {
        fprintf(fichier, "%d %d %d %d %d\n", defenseurs[i].portee, defenseurs[i].degats, defenseurs[i].prix, defenseurs[i].coordx, defenseurs[i].coordy);
    }

    // Sauvegarde des ennemis actifs
    fprintf(fichier, "%d\n", nbEnnemis); // Nombre d'ennemis
    for (int i = 0; i < nbEnnemis; i++) {
        fprintf(fichier, "%d %d %d\n", ennemis[i].attaquant.vie, ennemis[i].x, ennemis[i].y);
    }

    // Sauvegarde des autres variables importantes
    fprintf(fichier, "%d\n", score);   // Score
    fprintf(fichier, "%d\n", flocons); // Monnaie
    fprintf(fichier, "%d\n", vague);   // Numéro de la vague

    fclose(fichier); // Fermeture du fichier
}

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
                printf("\t Souhaitez-vous choisir un autre défenseur ?\n1 pour oui ou 0 pour non\n");
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
        liste_defenseur[*nb_defenseur] = nouv_def;
        (*nb_defenseur)++;
        
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
		    
                        if ((*ennemis)[i].x == *taillecarte - 1 && (*ennemis)[i].y == colonneCouronne){
		            defaite(score);
        		    return;
		        }
		    }

		    // Génère un nouvel attaquant seulement si la case est vide
		    if ((*carte)[0][colonneDebut].type == 6 && compteur<=8){
		        generer_attaquant(*carte, colonneDebut, ennemis, nbEnnemis, &compteur, vague);
		    }
		    
		    //system("clear");
		    afficher_carte(*carte, *taillecarte);
		}
		(*flocons) += 75;
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
    // Libération de la mémoire
    
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

//main
int main() {
    system("clear");
    // Initialisation des variables
    int jeu_en_cours = 1; // Variable pour contrôler la boucle principale
    srand(time(NULL));   
    Case** carte = NULL; 
    int taillecarte = 0;
    int* ptrtaillecarte = &taillecarte;
    int nbDefenseurs = 0;
    EnnemiActif* ennemis[80];
    int nbEnnemis = 0;
    int score = 0;
    int flocons = 250;
    int vague = 0;
    Defenseur* defenseurs = (Defenseur*)malloc(100 * sizeof(Defenseur)); // Pre-allocation d'espace pour 100 defenseurs
    if (defenseurs == NULL) {
        printf("\t Erreur d'allocation mémoire pour les défenseurs\n");
        exit(2);
    }

    while (jeu_en_cours == 1){
        int choix_menu=menuDemarrage(); // Affiche le menu principal et récupère le choix

        switch (choix_menu) {
            case 1:
            	remove("sauvegarde.txt");
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, ennemis, &nbEnnemis, &score, &flocons, &vague); // Lance une nouvelle partie
                system("make");
                break;
            case 2:
                chargement("sauvegarde.txt", &carte, &taillecarte, &defenseurs, &nbDefenseurs, ennemis, &nbEnnemis, &score, &flocons, &vague);
                lancerpartie(&carte, &taillecarte, &defenseurs, &nbDefenseurs, ennemis, &nbEnnemis, &score, &flocons, &vague); // Reprend la partie chargée
                system("make");
                break;
            case 3:
                printf("\n\t A plus 👋😊\n\n");
                jeu_en_cours=0; // Quitte la boucle principale
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
