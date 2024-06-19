#include "Hamilton.h"
#include <fstream> // Incluir la biblioteca para manejo de archivos

double Hamilton::busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    double min_cost = std::numeric_limits<double>::infinity();
    std::vector<int> best_path;
    Cola<std::tuple<int, std::vector<bool>, double, std::vector<int>>> q;
    std::vector<bool> visitados(n, false);
    visitados[0] = true;
    q.encolar(std::make_tuple(0, visitados, 0.0, std::vector<int>{0}));

    std::ofstream outfile("ciclos_hamiltonianos.txt");  // Abrir archivo de texto para escritura

    while (!q.colavacia()) {
        auto [u, visitados, cost, path] = q.tope();
        q.desencolar();

        if (std::all_of(visitados.begin(), visitados.end(), [](bool v) { return v; })) {
            if (matriz[u][0] != std::numeric_limits<double>::infinity()) {
                double total_cost = cost + matriz[u][0];
                outfile << "Ciclo Hamiltoniano encontrado: ";
                for (int i = 0; i < path.size(); ++i) {
                    outfile << path[i] << "->";
                }
                outfile << "0 con costo " << total_cost << std::endl;

                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_path = path;
                    best_path.push_back(0);
                }
            }
        }

        for (int v = 0; v < n; ++v) {
            if (!visitados[v] && matriz[u][v] != std::numeric_limits<double>::infinity()) {
                auto new_path = path;
                new_path.push_back(v);
                auto new_visitados = visitados;
                new_visitados[v] = true;
                q.encolar(std::make_tuple(v, new_visitados, cost + matriz[u][v], new_path));
            }
        }
    }

    outfile << "Costo minimo del ciclo Hamiltoniano: " << min_cost << std::endl;
    outfile << "Camino: ";
    for (int i = 0; i < best_path.size(); ++i) {
        outfile << best_path[i] << (i == best_path.size() - 1 ? "" : "->");
    }
    outfile << std::endl;

    if (min_cost != std::numeric_limits<double>::infinity()) {
        camino = best_path;
    }

    outfile.close();  // Cerrar el archivo
    return min_cost;
}
