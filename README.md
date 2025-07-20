# ❄️ **Opération Flocon** ❄️

*Un tower defense givré en plein cœur des montagnes !*

---

## 🎯 **Description du Projet**

**Opération Flocon** est un jeu de **tower defense** prenant place dans un univers hivernal. Le joueur doit défendre une **couronne centrale** contre des vagues d’ennemis déjantés :

* 🚶 **Randonneur Perdu**
* 🎿 **Skieurs frénétiques**
* 🏂 **Snowboarders acrobates**
* 🛷 **Lugistes barjos**
* 🚴 **Cycliste Sponsorisé**

Pour se défendre, le joueur dispose de :

* 🐧 **Pingu-patrouilleurs**
* ⛄ **Flocons perce-ciel**
* 🐻‍❄️ **Gardes polaires**
* 🐺 **Loup griffeur**
* 🐉 **Dieu des montagnes**

La carte est générée **aléatoirement** à chaque partie avec un **chemin unique** menant à la couronne. Le joueur place ses défenseurs autour de ce chemin et doit gérer au mieux ses ressources pour survivre aux vagues successives.

---

## 👥 **Auteurs**

* Maxime **MONTEIL**
* Raphaël **DUFOUR**
* Lucien **LEHEUDRE--EPSTEIN**

---

## 🚀 **Fonctionnalités principales**

* 🗺️ **Génération aléatoire** de cartes 2D
* 🛡️ **Placement stratégique** des défenseurs par l'utilisateur
* 🏃‍♂️ **Déplacement automatique** des ennemis le long du chemin
* 🎯 **Attaques automatiques** des défenseurs (avec portée et précision)
* 🏆 **Système de score** (+1 point par ennemi éliminé)
* 📀 **Sauvegarde et reprise** des parties
* 🎨 **Affichage** en terminal avec **emojis** (UTF-8)

---

## 🌟 **Nos variantes**

* 📍 **Direction du chemin** : de haut en bas
* 📏 **Taille de la carte** : aléatoire entre **30x30** et **45x45**
* 👑 **Fin de partie** : le jeu se termine dès qu’un attaquant atteint la couronne

---

## 🕹️ **Phases du jeu**

1. **Menu principal** : Démarrer / Reprendre / Quitter
2. **Génération de la carte**
3. **Placement** des défenseurs
4. **Début des vagues** ennemies
5. **Déplacement** des attaquants
6. **Phase de tir** des défenseurs (calcul de portée et esquives)
7. **Affichage** mis à jour toutes les **0.5 secondes**
8. **Fin de partie** : Victoire ou Défaite
9. **Sauvegarde** ou **reprise** de la partie

---

## 🛠️ **Compilation & Exécution**

Ouvrez votre terminal et entrez les commandes suivantes :

```bash
git clone https://github.com/Snowsurf-007/Operation-Flocon
cd Operation-Flocon
make
./operation_flocon
```

Et c’est parti pour défendre la couronne ! 👑❄️

---

## 🏔️ **Bonne chance, et que la montagne soit avec vous !**
