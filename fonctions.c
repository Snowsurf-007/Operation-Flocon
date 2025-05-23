#include "biblio.h"

//Fonctions constructrices
Defenseur constructeur_PinguPatrouilleur(Defenseur a) {
    a.portee = 4;
    a.degats = 60;
    a.prix = 100;
    return a;
}

Defenseur constructeur_FloconPerceCiel(Defenseur a) {
    a.portee = 7;
    a.degats = 40;
    a.prix = 200;
    return a;
}

Defenseur constructeur_GardePolaire(Defenseur a) {
    a.portee = 1;
    a.degats = 80;
    a.prix = 150;
    return a;
}

Attaquant constructeur_SkieurFrenetique(Attaquant a) { // Attaquant rapide et faible
    a.vie = 400;
    return a;
}

Attaquant constructeur_SnowboarderAcrobate(Attaquant a) { // Attaquant vitesse moyenne, vie moyenne
    a.vie = 800;
    return a;
}

Attaquant constructeur_LugisteBarjo(Attaquant a) { // Attaquant lent et résistant
    a.vie = 1600;
    return a;
}

//Fonctions

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

            // Calcul de la distance entre le défenseur et l'ennemi
            int distance = calculerDistance(def.coordx, def.coordy, ennemi->x, ennemi->y);
	    
            // Si l'ennemi est à portée
            if (distance <= def.portee) {
                    
                ennemi->attaquant.vie -= def.degats;
                
                // Si l'ennemi est éliminé
                if (ennemi->attaquant.vie <= 0) {
                    int x1 = ennemi->x;
                    int y1 = ennemi->y;
                    
                    carte[y1][x1].type = 6; // Remet la case à "chemin"
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
        int type_attaquant = carte[y][x].type;

        // Déplacement bas > droite > gauche
        if (y+1 < taillecarte && (carte[y+1][x].type == 6 || carte[y+1][x].type == 7)){
            carte[y+1][x].type = type_attaquant;
            carte[y][x].type = 6;
            ennemis[i].y++;
        }
        else if (x+1 < taillecarte && (carte[y][x+1].type == 6 || carte[y][x+1].type == 7)){
            carte[y][x+1].type = type_attaquant;
            carte[y][x].type = 6;
            ennemis[i].x++;
        }
        else if (x-1>=0 && (carte[y][x-1].type==6 || carte[y][x-1].type==7)){
            carte[y][x-1].type=type_attaquant;
            carte[y][x].type=6;
            ennemis[i].x--;
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
    nouveau->x = debut;
    nouveau->y = 0;

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
