# Projet Runner 3D – Apprentissage des bases du Gameplay 3D

## Installation et génération de la solution

1. Aller dans le dossier `bin/`.
2. Exécuter `make.bat`.  
3. Le script génère un dossier `ide/` contenant `[SOLUTION_NAME].sln`.
4. Ouvrir la solution Visual Studio.

Projet réalisé dans un cadre scolaire avec une **version simplifiée du GCE (Game Engine du Gaming Campus)**.  
Objectif principal : **continuer la prise en main du développement 3D** en se concentrant sur les **3C** :

- **Camera**
- **Controller**
- **Character**

Le jeu est un **runner 3D**, centré sur le déplacement du personnage, la gestion de la caméra et les interactions en temps réel.

---

### 1. Character
- Gestion des déplacements latéraux
- Saut et états au sol
- Déplacement vertical contrôlé (jetpack)
- Système de tir
- Gestion de la vélocité

### 2. Controller
- Lecture des entrées clavier / souris
- Lien direct entre inputs et actions du personnage
- Séparation logique entre :
  - contrôles **gameplay**
  - contrôles **menus / scènes**

### 3. Camera
- Caméra liée au personnage
- Déplacement dynamique vers le curseur
- Retour automatique à la position par défaut

---

## Principe du jeu

Le joueur contrôle un personnage dans un environnement 3D de type **runner**.  
L’objectif est de progresser en évitant les obstacles et en utilisant :

- le déplacement latéral
- le saut
- le jetpack
- le tir

Le gameplay repose fortement sur la réactivité des contrôles et la lisibilité de la caméra.

---

## 🎮 Contrôles – Gameplay (en jeu)

| Touche / Souris | Action |
|-----------------|--------|
| **Q** | Déplacement à gauche |
| **D** | Déplacement à droite |
| *(aucune touche latérale)* | Le personnage regarde vers l’avant |
| **SPACE** | Saut (uniquement si au sol) |
| **Z** | Jetpack vers le haut |
| **S** | Jetpack vers le bas |
| **Clic gauche** | Tir vers l’avant |
| **Clic droit (maintenu)** | Déplace la caméra vers le curseur |
| *(relâcher clic droit)* | Reset de la caméra |

---

## Contrôles – Menus & Gestion des scènes

Le jeu utilise un **SceneManager** pour gérer les états :

- MENU  
- GAMEPLAY  
- PAUSE  
- SETTINGS  
- GAMEOVER  

| Touche | Fonction |
|--------|----------|
| **A** | Lancer la partie depuis le menu |
| **P** | Mettre le jeu en pause (depuis le gameplay) |
| **C** | Reprendre la partie (depuis pause) |
| **R** | Recommencer une partie (depuis pause ou game over) |
| **S** | Aller aux paramètres (depuis menu ou pause) |
| **B** | Retour à la scène précédente (depuis settings) |
| **Q** | Retour au menu (depuis pause ou game over) |
| **SPACE** | Quitter le jeu (depuis menu, pause ou game over) |

Projet orienté **apprentissage technique**, pas production finale.
