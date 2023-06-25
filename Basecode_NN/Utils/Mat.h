#pragma once

#include "../Settings.h"
#include "Data.h"

// Structure représentant une matrice.
typedef struct sMat
{
	// Largeur.
	int w;

	// Hauteur.
	int h;

	// Valeurs.
	data* values;
}Mat;

// Crée une matrice (toutes les valeurs sont initialisées à 0).
Mat* Mat_New(int w, int h);

// Copie une matrice.
Mat* Mat_Copy(Mat* m);

// Copie une matrice, initialise le résultat dans res.
void Mat_Copy2(Mat* m, Mat* res);

// Détruit une matrice.
void Mat_Destroy(Mat* m);

// Renvoie la valeur d'une matrice à la position (i, j).
data Mat_Get(Mat* m, int i, int j);

// Modifie la valeur d'une matrice à la position (i, j).
void Mat_Set(Mat* m, int i, int j, data value);

// Affiche une matrice.
void Mat_Print(Mat* m);

// Réalise une opération sur 2 matrices (m1 ¤= m2).
void Mat_Operation(Mat* m1, Mat* m2, data (*funcOperation)(data, data));

// Multiplie toutes les composantes d'une matrice par un scalaire (m *= s).
void Mat_Scale(Mat* m, data s);

// Renvoie le produit matriciel de 2 matrices.
Mat* Mat_Multiply(Mat* m1, Mat* m2);

// Réalise le produit matriciel de 2 matrices, initialise le résultat dans res.
void Mat_Multiply2(Mat* m1, Mat* m2, Mat* res);

// Compose une matrice (m = f[m]).
void Mat_Compose(Mat* m, data (*funcCompose)(data));

// Compose une matrice, initialise le résultat dans res (res = f[m]).
void Mat_Compose2(Mat* m, data (*funcCompose)(data), Mat* res);

// Renvoie la transposée d'une matrice.
Mat* Mat_Transpose(Mat* m);

// Initialise chaque composante d'une matrice aléatoirement entre a et b.
void Mat_Randomize(Mat* m, data a, data b);

// Vérifie si 2 matrices sont identiques à epsilon près (vérifie pour chaque composante).
bool Mat_Equal(Mat* m1, Mat* m2, data epsilon);
