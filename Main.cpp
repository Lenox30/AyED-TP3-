#include <iostream>
#include "Imagen.h"
#include "Filtro.h"
#include "Grafo.h"
#include "DijkstraPrim.h"
#include "Filtro.cpp"
#include "Imagen.cpp"
#include "Grafo.cpp"
#include "DijkstraPrim.cpp"

using namespace std;

int main() {
    Imagen imagen("imagen.txt");
    imagen.imprimir();

    Filtro filtro(imagen);
    filtro.encontrarManchas();
    filtro.getManchas();
    imagen.getBarreras();

    Grafo grafo(filtro.getManchas(), imagen.getBarreras());
    grafo.imprimir();

    std::vector<int> predecesores = dijkstra(grafo, 0);
    std::vector<std::pair<int, int>> mst = prim(grafo);

    // Imprimir el resultado de Dijkstra
    std::cout << "Predecesores en Dijkstra: ";
    for (int p : predecesores) {
        std::cout << p << " ";
    }
    std::cout << std::endl;

    // Imprimir el resultado de Prim
    std::cout << "Arbol de expansion minima (Prim): ";
    for (const auto& arista : mst) {
        std::cout << "(" << arista.first << ", " << arista.second << ") ";
    }
    std::cout << std::endl;

    std::vector<int> camino;
    double costo = busquedaAmplitud(grafo, camino);

    if (costo != std::numeric_limits<double>::infinity()) {
        std::cout << "Costo minimo del ciclo Hamiltoniano: " << costo << std::endl;
        std::cout << "Camino: ";
        for (int nodo : camino) {
            std::cout << nodo << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

