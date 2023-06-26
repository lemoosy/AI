#pragma once

#include "Function.h"
#include "Settings.h"
#include "Utils/Mat.h"
#include "Utils/Utils.h"

// Structure représentant une couche dans un réseau de neurones.
typedef struct sLayer
{
	// Nombre de neurones.
	int size;

	// Poids.
	Mat* W;

	// Biais.
	Mat* B;

	// Sorties de la fonction somme.
	Mat* Z;

	// Sorties de la fonction d'activation.
	Mat* A;

	// Valeurs intermédiaires pour la backpropagation (dE/dz).
	Mat* S;

	// ID de la fonction d'activation.
	FunctionID funcActivationID;

	// Fonction d'activation.
	data (*funcActivation)(data);

	// Dérivée de la fonction d'activation.
	data (*funcActivationDer)(data);
}Layer;

// Crée une couche.
Layer* Layer_New(Layer* layerPrev, int size, FunctionID funcActivationID);

// Copie une couche.
Layer* Layer_Copy(Layer* layer);

// Détruit une couche.
void Layer_Destroy(Layer* layer);
