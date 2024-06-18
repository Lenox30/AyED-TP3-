#include "Hamilton.h"
#include "Cola.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

#define INFI std::numeric_limits<double>::infinity()

using namespace std;

vector<pair<int, int>> Prim(const Grafo& grafo) {
    // Obtener la matriz de costos del grafo
    const auto& C = grafo.getMatriz();
    int n = C.size(); // Número de nodos en el grafo

    // Inicialización de estructuras auxiliares
    vector<double> mencosto(n, INFI);   // Distancia mínima a cada nodo
    vector<int> mascerca(n, -1);        // Nodo más cercano en el MST
    vector<bool> enMST(n, false);       // Indicador de si el nodo está en el MST
    Cola<pair<double, int>> pq;         // Cola de prioridad para nodos a procesar

    // Inicializar el nodo inicial (0)
    mencosto[0] = 0;    // La distancia al nodo inicial es 0
    pq.encolar({0, 0}); // Encolar el nodo inicial con costo 0

    vector<pair<int, int>> Aristas; // Para almacenar las aristas del MST

    // Bucle principal del algoritmo de Prim
    while (!pq.colavacia()) {
        // Obtener el nodo con el costo mínimo
        int u = pq.tope().second;
        pq.desencolar();

        // Si el nodo ya está en el MST, continuar con el siguiente
        if (enMST[u]) continue;
        enMST[u] = true;

        // Agregar la arista al MST (excepto para el nodo inicial)
        if (mascerca[u] != -1) {
            Aristas.push_back({mascerca[u], u});
        }

        // Imprimir información del nodo más cercano
        if (mascerca[u] != -1) {
            cout << "\nel nodo " << u << " es el mas cercano a " << mascerca[u] << "    distancia " << mencosto[u] << endl;
        }

        // Actualizar las distancias mínimas para los nodos adyacentes
        for (int v = 0; v < n; ++v) {
            if (C[u][v] != INFI && !enMST[v] && C[u][v] < mencosto[v]) {
                mencosto[v] = C[u][v];
                pq.encolar({mencosto[v], v}); // Encolar el nodo con su nueva distancia
                mascerca[v] = u; // Actualizar el nodo más cercano
            }
        }
    }

    return Aristas; // Devolver las aristas del MST
}

double Hamilton::busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    double min_cost = std::numeric_limits<double>::infinity();
    std::vector<int> best_path;

    Cola<std::tuple<int, int, double, std::vector<int>>> q;
    q.encolar(std::make_tuple(0, 1, 0.0, std::vector<int>{0}));

    while (!q.colavacia()) {
        auto [u, mask, cost, path] = q.tope();
        q.desencolar();

        // Si todos los nodos han sido visitados, verifica si es posible regresar al nodo inicial.
        if (mask == (1 << n) - 1) {
            if (matriz[u][0] != std::numeric_limits<double>::infinity()) {
                double total_cost = cost + matriz[u][0];
                // Imprime el ciclo hamiltoniano encontrado.
                std::cout << "Ciclo Hamiltoniano encontrado: ";
                for (int i = 0; i < path.size(); ++i) {
                    std::cout << path[i] << "->";
                }
                std::cout << "0 con costo " << total_cost << std::endl;

                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_path = path;
                    best_path.push_back(0);
                }
            }
            continue;
        }

        // Explorar todos los vecinos
        for (int v = 0; v < n; ++v) {
            if (!(mask & (1 << v)) && matriz[u][v] != std::numeric_limits<double>::infinity()) {
                auto new_path = path;
                new_path.push_back(v);
                q.encolar(std::make_tuple(v, mask | (1 << v), cost + matriz[u][v], new_path));
            }
        }
    }

    if (min_cost != std::numeric_limits<double>::infinity()) {
        std::cout << "Costo minimo del ciclo Hamiltoniano: " << min_cost << std::endl;
        std::cout << "Camino: ";
        for (int i = 0; i < best_path.size(); ++i) {
            std::cout << best_path[i] << (i == best_path.size() - 1 ? "" : "->");
        }
        std::cout << std::endl;
        camino = best_path;
    } else {
        std::cout << "No se pudo encontrar un ciclo Hamiltoniano valido debido a las barreras." << std::endl;
    }

    return min_cost;
}
