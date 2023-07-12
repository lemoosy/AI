# Réseau de neurones & Programmation génétique



Dans ce projet, je vous présente plusieurs IA (Intelligence Artificielle) utilisé sur différents jeux vidéo.



**Jeux**

- Puissance 4 (Connect4)
- Jeu du serpent (Snake)



**IA**

- Minimax (Puissance 4)
- Réseau de neurones (Puissance 4)
- LISP (Jeu du serpent)



# Puissance 4 (Connect4)



L'objectif du projet est de créer un réseau de neurones capable de copier un [Minimax](https://fr.wikipedia.org/wiki/Algorithme_minimax) de profondeur N.



## Modèle du réseau de neurones (Perceptron)



Le réseau de neurones possède 5 couches, 1 couche d'entrée, 3 couches cachées et 1 couche de sortie :



### Couche d'entrée

La première couche prend en entrées la grille du jeu, **84 entrées**, 7 x 6 x 2.

Les 42 premières entrées correspondent au joueur, les 42 autres entrées correspondent à l'adversaire.

1 pour dire que la pièce est présente et 0 pour dire qu'elle n'est pas présente ([OHE](https://fr.wikipedia.org/wiki/Encodage_one-hot)).



### Couches cachées

Chaque couche cachée est composée de **256 neurones**, avec comme fonction d'activation [sigmoid](https://fr.wikipedia.org/wiki/Sigmo%C3%AFde_(math%C3%A9matiques)).



### Couche de sortie

La dernière couche possède **7 sorties**, avec comme fonction d'activation [softmax](https://fr.wikipedia.org/wiki/Fonction_softmax).

Chaque sortie correspond à une colonne, une valeur entre 0 et 1, la plus grande valeur est sélectionnée.



## Entraînement



Chaque fois que le réseau de neurones choisit une colonne, il réalise une back-propagation avec le résultat d'un minimax.

Pour la back-propagation j'utilise la méthode de descente de gradient.

La fonction de coût est la Cross-Entropie.



***Pour aller plus loin**: Au lieu que le réseau de neurones renvoie une colonne, il pourrait renvoyer un score, selon le même principe qu'un minimax. Une fois qu'il aurait appris pour une profondeur N, on pourrait combiner un minimax et un réseau de neurones pour doubler la profondeur du minimax. On pourrait faire cela de manière récursive jusqu'à obtenir un réseau de neurones capable d'anticiper tous les coups d'un jeu (ce qui est impossible avec un minimax car cela demanderais beaucoup de ressources).*



## Résultat



Voici un graphe représentant la différence des parties gagnées entre un minimax et un réseau de neurones sur 1 million de parties.



Sur l'axe des abscisses: 1 unité = 100 parties

Sur l'axe des ordonnées: [Minimax_Win - NN_Win]



<img src="C:\Users\Lemoosy\OneDrive\Bureau\Basecode_AI\Readme\Minimax VS NN.png" style="zoom:80%;" />



# Jeu du serpent (Snake)



Pour le jeu du serpent, j'ai fais de la [Programmation Génétique](https://fr.wikipedia.org/wiki/Programmation_g%C3%A9n%C3%A9tique).

Le principe est simple, je crée plusieurs programmes aléatoires (qui sont des arbres à N enfants, [LISP](https://fr.wikipedia.org/wiki/Lisp)), chaque nœud interne est une fonction, chaque feuille est une variable, chaque arbre à un nombre limité de nœuds (dans ce projet, j'ai limité à **100 nœuds**).

J'évalue chaque programme avec ce qu'on appelle une fonction de fitness (par exemple le nombre de nourritures récoltées par un serpent), je sélectionne les meilleurs, je génère des enfants (je mix des programmes entre eux), puis je recommence le processus jusqu'à obtenir la meilleur solution, c'est-à-dire un programme capable de récolter N pommes (**100 pommes**).



## Variables



**Snake_HeadBodyN** : Renvoie vrai s'il y a son corps à la case au-dessus de sa tête, sinon renvoie faux.

**Snake_HeadBodyS** : Renvoie vrai s'il y a son corps à la case en-dessous de sa tête, sinon renvoie faux.

**Snake_HeadBodyW** : Renvoie vrai s'il y a son corps à la case à gauche de sa tête, sinon renvoie faux.

**Snake_HeadBodyE** : Renvoie vrai s'il y a son corps à la case à droite de sa tête, sinon renvoie faux.



**Snake_HeadWallN** : Renvoie vrai s'il y a un mur à la case au-dessus de sa tête, sinon renvoie faux.

**Snake_HeadWallS** : Renvoie vrai s'il y a un mur à la case en-dessous de sa tête, sinon renvoie faux.

**Snake_HeadWallW** : Renvoie vrai s'il y a un mur à la case à gauche de sa tête, sinon renvoie faux.

**Snake_HeadWallE** : Renvoie vrai s'il y a un mur à la case à droite de sa tête, sinon renvoie faux.



**Snake_DirectionHeadIsN** : Renvoie vrai si la direction de la tête est vers le nord, sinon renvoie faux.

**Snake_DirectionHeadIsS** : Renvoie vrai si la direction de la tête est vers le sud, sinon renvoie faux.

**Snake_DirectionHeadIsW** : Renvoie vrai si la direction de la tête est vers le gauche, sinon renvoie faux.

**Snake_DirectionHeadIsE** : Renvoie vrai si la direction de la tête est vers le droite, sinon renvoie faux.



**Snake_AheadFood** : Renvoie vrai si il y a de la nourriture droit devant le serpent (selon la direction de la tête), sinon renvoie faux.

**Snake_AheadBody** : Renvoie vrai si il y a un corps droit devant le serpent (selon la direction de la tête), sinon renvoie faux.

**Snake_AheadWall2** : Renvoie vrai s'il y a à 2 cases après sa tête (selon la direction de la tête) un mur, sinon renvoie faux.



## Fonctions



**Snake_SetDirectionN** : Modifie la direction de la tête du serpent vers le Nord.

**Snake_SetDirectionS** : Modifie la direction de la tête du serpent vers le Sud.

**Snake_SetDirectionW** : Modifie la direction de la tête du serpent vers l'Ouest.

**Snake_SetDirectionE** : Modifie la direction de la tête du serpent vers l'Est.



## Tableau



| Name                  | Description                                                  |
| :-------------------- | ------------------------------------------------------------ |
| Objective:            | Trouver un programme capable de manger le plus de nourriture possible. |
| Terminal set:         | Snake_HeadBody**N**/**S**/**W**/**E** - Snake_HeadWall**N**/**S**/**W**/**E** - Snake_DirectionHeadIs**N**/**S**/**W**/**E** - Snake_AheadFood - Snake_AheadBody - Snake_AheadWall2 - Snake_SetDirection**N**/**S**/**W**/**E**. |
| Function set:         | PROGN2 - NOT - AND - OR - IF.                                |
| Fitness cases:        | 3 cas.                                                       |
| Raw fitness:          | La taille maximum du serpent parmi les 3 parties.            |
| Standardized fitness: | La taille maximum du serpent = 100.                          |
| Wrapper:              | Aucun.                                                       |
| Parameters:           | Nombre de générations = 100, Taille de la population = 5000, Taille de la sélection = 500, Crossover = 500, Mutation = 500, Nombre maximum de nœuds = 100. |
| Success predicate:    | Taille du serpent = 100.                                     |



## Résultat



<img src="C:\Users\Lemoosy\OneDrive\Bureau\Basecode_AI\Readme\Snake.gif" style="zoom: 67%;" />



```
PROGN2
        PROGN2
                PROGN2
                        PROGN2
                                Snake_SetDirectionS
                                IF
                                        AND
                                                Snake_HeadWallS
                                                Snake_DirectionHeadIsN
                                        Snake_SetDirectionS
                                        Snake_SetDirectionW
                        IF
                                Snake_HeadWallE
                                IF
                                        OR
                                                Snake_DirectionHeadIsN
                                                AND
                                                        Snake_HeadBodyN
                                                        Snake_DirectionHeadIsN
                                        Snake_SetDirectionW
                                        Snake_SetDirectionS
                                IF
                                        Snake_DirectionHeadIsE
                                        IF
                                                Snake_AheadFood
                                                Snake_SetDirectionN
                                                PROGN2
                                                        PROGN2
                                                                Snake_SetDirectionN
                                                                Snake_SetDirectionN
                                                        Snake_SetDirectionS
                                        PROGN2
                                                Snake_SetDirectionE
                                                Snake_SetDirectionW
                Snake_SetDirectionW
        IF
                OR
                        AND
                                Snake_HeadWallW
                                Snake_HeadWallS
                        AND
                                Snake_AheadWall2
                                Snake_AheadBody
                Snake_SetDirectionW
                IF
                        OR
                                AND
                                        NOT
                                                Snake_HeadWallE
                                        Snake_HeadWallS
                                Snake_AheadFood
                        Snake_SetDirectionW
                        PROGN2
                                Snake_SetDirectionS
                                IF
                                        NOT
                                                Snake_HeadWallE
                                        IF
                                                OR
                                                        NOT
                                                                OR
                                                                        Snake_HeadWallS
                                                                        Snake_HeadWallW
                                                        Snake_HeadWallN
                                                PROGN2
                                                        PROGN2
                                                                Snake_SetDirectionW
                                                                PROGN2
                                                                        Snake_SetDirectionE
                                                                        PROGN2
                                                                                Snake_SetDirectionN
                                                                                IF
                                                                                        Snake_DirectionHeadIsE
                                                                                        Snake_SetDirectionW
                                                                                        Snake_SetDirectionS
                                                        Snake_SetDirectionE
                                                PROGN2
                                                        IF
                                                                AND
                                                                        AND
                                                                                Snake_HeadWallW
                                                                                Snake_DirectionHeadIsN
                                                                        Snake_DirectionHeadIsN
                                                                IF
                                                                        Snake_HeadBodyN
                                                                        Snake_SetDirectionW
                                                                        Snake_SetDirectionN
                                                                Snake_SetDirectionW
                                                        Snake_SetDirectionN
                                        IF
                                                NOT
                                                        Snake_AheadBody
                                                Snake_SetDirectionS
                                                PROGN2
                                                        IF
                                                                Snake_HeadWallS
                                                                Snake_SetDirectionW
                                                                Snake_SetDirectionW
                                                        __Snake_SetDirectionW
```