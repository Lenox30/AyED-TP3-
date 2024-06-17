#ifndef HAMILTON_H
#define HAMILTON_H

#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "Grafo.h"

class Hamilton {
public:
    // Encuentra el Árbol de Expansión Mínima usando el algoritmo de Prim
    std::vector<std::pair<int, int>> prim(const Grafo& grafo);

    // Encuentra el ciclo Hamiltoniano de costo mínimo usando BFS
    double busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino);
};

#endif // HAMILTON_H
