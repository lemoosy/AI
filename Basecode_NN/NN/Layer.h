#pragma once

#include "../Settings.h"
#include "../Utils/FunctionID.h"
#include "../Utils/Mat.h"
#include "../Utils/Type/Float.h"

/// @brief Structure repr�sentant une couche dans un r�seau de neurones.
typedef struct sLayer
{
	/// @brief Nombre de neurones.
	int size;

	/// @brief Poids.
	Mat* W;

	/// @brief Biais.
	Mat* B;

	/// @brief Sorties de la fonction somme.
	Mat* Z;

	/// @brief Sorties de la fonction d'activation.
	Mat* A;

	/// @brief Valeurs interm�diaires pour la backpropagation (dE/dz).
	Mat* S;

	/// @brief ID de la fonction d'activation.
	FunctionID funcActivationID;

	/// @brief Fonction d'activation.
	data (*funcActivation)(data);

	/// @brief D�riv�e de la fonction d'activation.
	data (*funcActivationDer)(data);
}Layer;

/// @brief Cr�e une couche (les poids et les biais sont inialis�es al�atoirement entre -1 et +1).
Layer* Layer_Create(Layer* layerPrev, int size, FunctionID funcActivationID);

/// @brief Copie une couche.
Layer* Layer_Copy(Layer* layer);

/// @brief D�truit une couche.
void Layer_Destroy(Layer* layer);
