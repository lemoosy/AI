#pragma once

#include "Batch.h"
#include "Utils/Data.h"
#include "Layer.h"
#include "Utils/Mat.h"
#include "Utils/DList.h"
#include "Utils/Utils.h"
#include "Settings.h"

// Structure repr�sentant un r�seau de neurones.
typedef struct sNetwork
{
	// Liste doublement cha�n�e repr�sentant les couches du r�seau.
	DList* layers;
	
	// Pas d'apprentissage.
	float learningStep;
}Network;

// Cr�e un r�seau de neurones vide.
Network* Network_New(float learningStep);

// Copie un r�seau de neurones.
Network* Network_Copy(Network* net);

// D�truit un r�seau de neurones.
void Network_Destroy(Network* net);

// Ajoute une couche dans un r�seau de neurones.
void Network_AddLayer(Network* net, int size, FunctionID functionID);

// Affiche une matrice dans une couche dans un r�seau de neurones.
void Network_PrintLayer(Network* net, int index, char var);

// R�alise la propagation vers l'avant.
void Network_Forward(Network* net, Mat* inputs);

// R�alise la propagation vers l'arri�re (m�thode du gradient).
void Network_Backward(Network* net, Mat* outputs);

// Apprends � un r�seau de neurones un dataset.
void Network_Learning(Network* net, Batch* data);

//
int Network_CountError(Network* net, Batch* batch, data epsilon);
