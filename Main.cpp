#include <iostream>
#include "Imagen.h"
#include "Filtro.h"
#include "Grafo.h"
#include "Hamilton.h" // Cambiado de DijkstraPrim.h a Hamilton.h

using namespace std;

int main() {
    Imagen imagen("imagen.txt");
    imagen.imprimir();

    Filtro filtro(imagen);
    filtro.encontrarManchas();

    Grafo grafo(filtro.getManchas(), imagen.getBarreras());
    grafo.imprimir();

    Hamilton hamilton;

    // Usar el metodo prim de la clase Hamilton
    std::vector<std::pair<int, int>> aristas = Prim(grafo);

    cout << "----------------------------------------------\n";
    for (const auto& arista : aristas) {
        cout << "Arista: " << arista.first << " al: " << arista.second << endl;
    }

    // Imprimir el resultado de Prim
    std::cout << "Arbol de expansion minima (Prim): ";
    for (const auto& arista : aristas) {
        std::cout << "(" << arista.first << ", " << arista.second << ") ";
    }
    std::cout << std::endl;

    std::vector<int> caminoHamiltoniano;
    double costo = hamilton.busquedaAmplitud(grafo, caminoHamiltoniano);

    /*
    if (costo != std::numeric_limits<double>::infinity()) {
        std::cout << "Costo minimo del ciclo Hamiltoniano: " << costo << std::endl;
        std::cout << "Camino: ";
        for (int nodo : caminoHamiltoniano) {
            std::cout << nodo << " ";
        }
        std::cout << std::endl;
    }
    */

    return 0;
}
