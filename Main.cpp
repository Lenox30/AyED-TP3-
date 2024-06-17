#include <iostream>
#include "Imagen.h"
#include "Filtro.h"
#include "Grafo.h"
#include "Hamilton.h" // Cambiado de DijkstraPrim.h a Hamilton.h

using namespace std;

int main() {
    Imagen imagen("C:\\Users\\Ivan\\CLionProjects\\AyED-TP3\\imagen.txt");
    imagen.imprimir();

    Filtro filtro(imagen);
    filtro.encontrarManchas();

    Grafo grafo(filtro.getManchas(), imagen.getBarreras());
    grafo.imprimir();

    //int s = 0;  // primer nodo
    //int t = grafo.getMatriz().size() - 1;  // ultimo nodo

    Hamilton hamilton;  // Crear instancia de la clase Hamilton

    vector<double> dist;
    /**
    std::vector<int> predecesores = dijkstra(grafo, s, t, dist);

    if (dist[t] != INFINITY) {
        std::cout << "\n\nDistancia minima del nodo " << s << " al nodo " << t << " es " << dist[t];
        std::cout << "\n\nCAMINO: ";
        camino(predecesores, s, t);
        std::cout << std::endl << std::endl;
    } else {
        std::cout << "\nNO HAY CAMINO\n";
    }
    **/

    // Usar el método prim de la clase Hamilton
    std::vector<std::pair<int, int>> mst = hamilton.prim(grafo);

    // Imprimir el resultado de Prim
    std::cout << "Arbol de expansion minima (Prim): ";
    for (const auto& arista : mst) {
        std::cout << "(" << arista.first << ", " << arista.second << ") ";
    }
    std::cout << std::endl;

    std::vector<int> caminoHamiltoniano;
    double costo = hamilton.busquedaAmplitud(grafo, caminoHamiltoniano);
    /**
    if (costo != std::numeric_limits<double>::infinity()) {
        std::cout << "Costo minimo del ciclo Hamiltoniano: " << costo << std::endl;
        std::cout << "Camino: ";
        for (int nodo : caminoHamiltoniano) {
            std::cout << nodo << " ";
        }
        std::cout << std::endl;
    }

    return 0;
     **/
}
