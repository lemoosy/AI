#pragma once

#include "Function.h"
#include "Settings.h"
#include "Utils/Mat.h"
#include "Utils/Utils.h"

// Structure repr�sentant une couche dans un r�seau de neurones.
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

	// Valeurs interm�diaires pour la backpropagation (dE/dz).
	Mat* S;

	// ID de la fonction d'activation.
	FunctionID funcActivationID;

	// Fonction d'activation.
	data (*funcActivation)(data);

	// D�riv�e de la fonction d'activation.
	data (*funcActivationDer)(data);
}Layer;

// Cr�e une couche.
Layer* Layer_New(Layer* layerPrev, int size, FunctionID funcActivationID);

// Copie une couche.
Layer* Layer_Copy(Layer* layer);

// D�truit une couche.
void Layer_Destroy(Layer* layer);
