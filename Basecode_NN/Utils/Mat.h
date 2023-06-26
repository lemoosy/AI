#pragma once

#include "../Settings.h"

// Structure repr�sentant une matrice.
typedef struct sMat
{
	// Largeur.
	int w;

	// Hauteur.
	int h;

	// Valeurs.
	data* values;
}Mat;

// Cr�e une matrice (toutes les valeurs sont initialis�es � 0).
Mat* Mat_New(int w, int h);

// Copie une matrice.
Mat* Mat_Copy(Mat* m);

// Copie une matrice, initialise le r�sultat dans res.
void Mat_Copy2(Mat* m, Mat* res);

// D�truit une matrice.
void Mat_Destroy(Mat* m);

// Renvoie la valeur d'une matrice � la position (i, j).
data Mat_Get(Mat* m, int i, int j);

// Modifie la valeur d'une matrice � la position (i, j).
void Mat_Set(Mat* m, int i, int j, data value);

// Affiche une matrice.
void Mat_Print(Mat* m);

// Additionne 2 matrices.
void Mat_Add(Mat* m1, Mat* m2);

// Soustrait 2 matrices.
void Mat_Sub(Mat* m1, Mat* m2);

// Multiplie 2 matrices (Hadamard).
void Mat_Product(Mat* m1, Mat* m2);

// Multiplie toutes les composantes d'une matrice par un scalaire.
void Mat_Scale(Mat* m, data s);

// Multiplie toutes les composantes d'une matrice par un scalaire, initialise le r�sultat dans res.
void Mat_Scale2(Mat* m, data s, Mat* res);

// Additionne toutes les composantes d'une matrice.
data Mat_Sum(Mat* m);

// Renvoie le produit matriciel de 2 matrices.
Mat* Mat_Multiply(Mat* m1, Mat* m2);

// R�alise le produit matriciel de 2 matrices, initialise le r�sultat dans res.
void Mat_Multiply2(Mat* m1, Mat* m2, Mat* res);

// Compose une matrice.
void Mat_Compose(Mat* m, data (*funcCompose)(data));

// Compose une matrice, initialise le r�sultat dans res.
void Mat_Compose2(Mat* m, data (*funcCompose)(data), Mat* res);

// Renvoie la transpos�e d'une matrice.
Mat* Mat_Transpose(Mat* m);

// Initialise chaque composante d'une matrice al�atoirement entre a et b.
void Mat_Randomize(Mat* m, data a, data b, data (*funcRandom)(data, data));

// V�rifie si 2 matrices sont identiques � epsilon pr�s (v�rifie pour chaque composante).
bool Mat_Equal(Mat* m1, Mat* m2, data epsilon);
