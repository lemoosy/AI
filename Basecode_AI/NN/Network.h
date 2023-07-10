#pragma once

#include "../Settings.h"
#include "../Utils/DList.h"
#include "../Utils/FunctionID.h"
#include "../Utils/Mat.h"
#include "../Utils/Type/Int.h"
#include "Batch.h"
#include "Layer.h"

/// @brief Structure représentant un réseau de neurones.
typedef struct sNetwork
{
	/// @brief Liste doublement chaînée représentant les couches du réseau.
	DList* layers;
	
	/// @brief Pas d'apprentissage.
	float learningStep;
}Network;

/// @brief Crée un réseau de neurones vide.
Network* Network_Create(float learningStep);

/// @brief Copie un réseau de neurones.
Network* Network_Copy(Network* net);

/// @brief Détruit un réseau de neurones.
void Network_Destroy(Network* net);

/// @brief Ajoute une couche dans un réseau de neurones.
void Network_AddLayer(Network* net, int size, FunctionID functionID);

/// @brief Affiche une matrice dans une couche dans un réseau de neurones.
void Network_PrintLayer(Network* net, int index, char var);

/// @brief Réalise la propagation vers l'avant.
void Network_Forward(Network* net, Mat* inputs);

/// @brief Réalise la propagation vers l'arrière (méthode du gradient).
void Network_Backward(Network* net, Mat* outputs);

/// @brief Apprends à un réseau de neurones un jeu de données.
void Network_Learning(Network* net, Batch* batch);

/// @brief Compte le nombre d'erreurs que fait un réseau de neurones sur un jeu de données (à epsilon près).
int Network_CountError(Network* net, Batch* batch, data epsilon);
