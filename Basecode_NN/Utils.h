#pragma once

#include "Settings.h"

// Renvoie un nombre dans [a, b].
float float_random(float a, float b);

// Renvoie un nombre dans [a, b].
int int_random(int a, int b);

// �change deux valeurs : a <- b et b <- a.
void int_swap(int* a, int* b);

// Cr�e un tableau de taille size : { 0, 1, 2, ..., size - 1 }
int* int_tab(int size);

// Cr�e un tableau de taille size : { 3, 1, 3, 2, ... }
int* int_tab_random(int size);

// Cr�e un tableau de taille size : { 3, 1, 2, 4, ... }
int* int_tab_random_norep(int size);

float linear(float x);
float linearDer(float x);

float sigmoid(float x);
float sigmoidDer(float x);
