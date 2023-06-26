#pragma once

#include "../Settings.h"

// Renvoie un nombre dans l'intervalle [a, b].
float float_random(float a, float b);

// Renvoie un nombre dans l'intervalle [a, b].
int int_random(int a, int b);

// �change 2 entiers.
void int_swap(int* a, int* b);

// Cr�e un tableau de taille 'size', renvoie { 0, 1, 2, 3, ..., size - 1 }
int* int_tab(int size);

// Cr�e un tableau de taille 'size',
// chaque �l�ment est initialis� al�atoirement entre 0 et size-1,
// chaque �l�ment est unique.
int* int_tab_random_norep(int size);
