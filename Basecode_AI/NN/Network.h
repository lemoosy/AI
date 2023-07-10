#pragma once

#include "../Settings.h"
#include "../Utils/DList.h"
#include "../Utils/FunctionID.h"
#include "../Utils/Mat.h"
#include "../Utils/Type/Int.h"
#include "Batch.h"
#include "Layer.h"

/// @brief Structure repr�sentant un r�seau de neurones.
typedef struct sNetwork
{
	/// @brief Liste doublement cha�n�e repr�sentant les couches du r�seau.
	DList* layers;
	
	/// @brief Pas d'apprentissage.
	float learningStep;
}Network;

/// @brief Cr�e un r�seau de neurones vide.
Network* Network_Create(float learningStep);

/// @brief Copie un r�seau de neurones.
Network* Network_Copy(Network* net);

/// @brief D�truit un r�seau de neurones.
void Network_Destroy(Network* net);

/// @brief Ajoute une couche dans un r�seau de neurones.
void Network_AddLayer(Network* net, int size, FunctionID functionID);

/// @brief Affiche une matrice dans une couche dans un r�seau de neurones.
void Network_PrintLayer(Network* net, int index, char var);

/// @brief R�alise la propagation vers l'avant.
void Network_Forward(Network* net, Mat* inputs);

/// @brief R�alise la propagation vers l'arri�re (m�thode du gradient).
void Network_Backward(Network* net, Mat* outputs);

/// @brief Apprends � un r�seau de neurones un jeu de donn�es.
void Network_Learning(Network* net, Batch* batch);

/// @brief Compte le nombre d'erreurs que fait un r�seau de neurones sur un jeu de donn�es (� epsilon pr�s).
int Network_CountError(Network* net, Batch* batch, data epsilon);
