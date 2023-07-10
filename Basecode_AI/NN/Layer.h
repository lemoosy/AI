#pragma once

#include "../Settings.h"
#include "../Utils/FunctionID.h"
#include "../Utils/Mat.h"
#include "../Utils/Type/Float.h"

/// @brief Structure représentant une couche dans un réseau de neurones.
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

	/// @brief Valeurs intermédiaires pour la backpropagation (dE/dz).
	Mat* S;

	/// @brief ID de la fonction d'activation.
	FunctionID funcActivationID;

	/// @brief Fonction d'activation.
	data (*funcActivation)(data);

	/// @brief Dérivée de la fonction d'activation.
	data (*funcActivationDer)(data);
}Layer;

/// @brief Crée une couche (les poids et les biais sont inialisées aléatoirement entre -1 et +1).
Layer* Layer_Create(Layer* layerPrev, int size, FunctionID funcActivationID);

/// @brief Copie une couche.
Layer* Layer_Copy(Layer* layer);

/// @brief Détruit une couche.
void Layer_Destroy(Layer* layer);
