#pragma once

#include "../Settings.h"

/// @brief Structure repr�sentant une matrice.
typedef struct sMat
{
	/// @brief Largeur.
	int w;

	/// @brief Hauteur.
	int h;

	/// @brief Valeurs.
	data* values;
}Mat;

/// @brief Cr�e une matrice (toutes les valeurs sont initialis�es � 0).
Mat* Mat_Create(int w, int h);

/// @brief Copie une matrice.
Mat* Mat_Copy(Mat* m);

/// @brief Copie une matrice, initialise le r�sultat dans res.
void Mat_Copy2(Mat* m, Mat* res);

/// @brief D�truit une matrice.
void Mat_Destroy(Mat* m);

/// @brief Renvoie la valeur d'une matrice � la position (i, j).
data Mat_Get(Mat* m, int i, int j);

/// @brief Modifie la valeur d'une matrice � la position (i, j).
void Mat_Set(Mat* m, int i, int j, data value);

/// @brief Affiche une matrice.
void Mat_Print(Mat* m);

/// @brief Additionne 2 matrices.
void Mat_Add(Mat* m1, Mat* m2);

/// @brief Soustrait 2 matrices.
void Mat_Sub(Mat* m1, Mat* m2);

/// @brief Multiplie 2 matrices (Hadamard).
void Mat_Product(Mat* m1, Mat* m2);

/// @brief Multiplie toutes les composantes d'une matrice par un scalaire.
void Mat_Scale(Mat* m, data s);

/// @brief Multiplie toutes les composantes d'une matrice par un scalaire, initialise le r�sultat dans res.
void Mat_Scale2(Mat* m, data s, Mat* res);

/// @brief Additionne toutes les composantes d'une matrice.
data Mat_Sum(Mat* m);

/// @brief Renvoie le produit matriciel de 2 matrices.
Mat* Mat_Multiply(Mat* m1, Mat* m2);

/// @brief R�alise le produit matriciel de 2 matrices, initialise le r�sultat dans res.
void Mat_Multiply2(Mat* m1, Mat* m2, Mat* res);

/// @brief Compose une matrice.
void Mat_Compose(Mat* m, data (*funcCompose)(data));

/// @brief Compose une matrice, initialise le r�sultat dans res.
void Mat_Compose2(Mat* m, data (*funcCompose)(data), Mat* res);

/// @brief Renvoie la transpos�e d'une matrice.
Mat* Mat_Transpose(Mat* m);

/// @brief Initialise chaque composante d'une matrice al�atoirement entre a et b.
void Mat_Randomize(Mat* m, data a, data b, data (*funcRandom)(data, data));

/// @brief V�rifie si 2 matrices sont identiques � epsilon pr�s (v�rifie pour chaque composante).
bool Mat_Equal(Mat* m1, Mat* m2, data epsilon);
