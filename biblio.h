#ifndef BIBLIO_H
#define BIBLIO_H

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

#endif // BIBLIO_H
