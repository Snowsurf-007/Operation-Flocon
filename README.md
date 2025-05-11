== Operation Flocon ==

1.Description du projet

Opération Flocon est un jeu de tower defense se déroulant dans un univers hivernal. Le joueur doit défendre une couronne centrale contre des vagues d’ennemis composées de skieurs frénétiques, snowboarders acrobates et lugistes barjos. 
        Pour se défendre, il peut compter sur des pingu-patrouilleurs, des flocons perce-ciel et des garde polaires positionnés stratégiquement sur la carte.
        La carte de jeu est générée aléatoirement à chaque partie, avec un chemin unique menant à la couronne, que les ennemis empruntent automatiquement. Le joueur peut placer ses défenseurs autour de celui-ci, en tenant compte des contraintes de positionnement.
        L’objectif principal est de repousser les vagues successives d’ennemis en optimisant la position et le type des défenseurs, tout en gérant les ressources disponibles.


2.Auteurs

- Maxime MONTEIL
- Raphaël DUFOUR
- Lucien LEHEUDRE--EPSTEIN

3.Fonctionnalités principales

- Génération de carte 2D
- Placement des défenseurs par l'utilisateur
- Déplacement des attaquants sur le chemin automatiquement
- Attaque automatique des defenseurs (en fonction de la portée de ceux-ci)
- Système de score (1 par ennemi tué)
- Sauvegarde et reprise de parties chargés
- Affichage avec des emojis en terminal (UTF-8)

4.Nos Variantes

- Direction du chemin : de haut en bas
- Taille de la carte : aléatoire entre 25 et 40 (matrice carrée)
- Fin de partie : 
        - fin du jeu des qu'un attaquant touche la couronne
 
5.Phases du jeu

- Menu principal : démarrer / reprendre / quitter
- Génération de la carte
- Placement des singes
- Vagues d'attaque
   - Déplacement des attaquants
   - Phase de tir des defenseurs (distance euclidienne et possibilité d'esquive des defenseurs)
   - Affichage du jeu (toutes les 0.5 secondes)
- Fin de jeu : victoire/défaite selon la variante
- Sauvegarde/reprise (optionnelle)

6.Compilation & Exécution

dans le terminal :

git clone https://github.com/Snowsurf-007/Computer-Sciences-Project_Operation-Flocon
cd Computer-Sciences-Project_Operation-Flocon
make
