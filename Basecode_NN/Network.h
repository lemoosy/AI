#pragma once

#include "Batch.h"
#include "Layer.h"
#include "Utils/Mat.h"
#include "Utils/DList.h"
#include "Utils/Utils.h"
#include "Settings.h"

// Structure représentant un réseau de neurones.
typedef struct sNetwork
{
	// Liste doublement chaînée représentant les couches du réseau.
	DList* layers;
	
	// Pas d'apprentissage.
	float learningStep;
}Network;

// Crée un réseau de neurones vide.
Network* Network_New(float learningStep);

// Copie un réseau de neurones.
Network* Network_Copy(Network* net);

// Détruit un réseau de neurones.
void Network_Destroy(Network* net);

// Ajoute une couche dans un réseau de neurones.
void Network_AddLayer(Network* net, int size, FunctionID functionID);

// Affiche une matrice dans une couche dans un réseau de neurones.
void Network_PrintLayer(Network* net, int index, char var);

// Réalise la propagation vers l'avant.
void Network_Forward(Network* net, Mat* inputs);

// Réalise la propagation vers l'arrière (méthode du gradient).
void Network_Backward(Network* net, Mat* outputs);

// Apprends à un réseau de neurones un je ude données.
void Network_Learning(Network* net, Batch* batch);

// 
int Network_CountError(Network* net, Batch* batch, data epsilon);
