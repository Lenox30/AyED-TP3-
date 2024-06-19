#include "Hamilton.h"


// Algoritmo BFS - O(n)
double Hamilton::busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    double min_cost = std::numeric_limits<double>::infinity();
    std::vector<int> mejor_camino;
    Cola<std::tuple<int, std::vector<bool>, double, std::vector<int>>> q;
    std::vector<bool> visitados(n, false);
    visitados[0] = true;
    // Inicializa la cola para la búsqueda en amplitud.
    // Utilizamos un tuple que almacena el nodo actual (int), los nodos visitados (std::vector<bool>), el costo acumulado (double), y un vector con el camino recorrido (std::vector<int>)
    q.encolar(std::make_tuple(0, visitados, 0.0, std::vector<int>{0}));

    std::ofstream outfile("C:\\Users\\Ivan\\CLionProjects\\AyED-TPFINAL\\ciclos_hamiltonianos.txt");  // Abrir archivo de texto para escritura

    // Si la cola está vacia, ya se recorrieron todos los ciclos posibles
    while (!q.colavacia()) {
        // Descompone la tupla en sus componentes y desencola el estado a procesar
        auto estado = q.tope();
        int u = std::get<0>(estado);
        std::vector<bool> visitados = std::get<1>(estado);
        double cost = std::get<2>(estado);
        std::vector<int> camino = std::get<3>(estado);
        q.desencolar();

        // Verifica si todos los nodos han sido visitados
        bool todosVisitados = true;
        for (bool v : visitados) {
            if (!v) {
                todosVisitados = false;
                break;
            }
        }

        // Si todos los nodos han sido visitados, verifica si es posible regresar al nodo inicial
        if (todosVisitados) {
            if (matriz[u][0] != std::numeric_limits<double>::infinity()) {
                double total_cost = cost + matriz[u][0];
                outfile << "Ciclo Hamiltoniano encontrado: ";
                for (int i = 0; i < camino.size(); ++i) {
                    outfile << camino[i] << "->";
                }
                outfile << "0 con costo " << total_cost << std::endl;
                // Actualiza el ciclo de menor costo
                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    mejor_camino = camino;
                    mejor_camino.push_back(0);
                }
            }
        }
        // Explora todos los nodos vecinos "v" del nodo actual "u"
        for (int v = 0; v < n; ++v) {
            // Si el nodo "v" no ha sido visitado y hay una arista del nodo "u" al nodo "v"
            if (!visitados[v] && matriz[u][v] != std::numeric_limits<double>::infinity()) {
                auto nuevo_camino = camino;
                nuevo_camino.push_back(v);
                auto nuevos_visitados = visitados;
                nuevos_visitados[v] = true;
                // Encola el nuevo estado: nodo "v", nodos visitados actualizados, nuevo costo y el nuevo camino
                q.encolar(std::make_tuple(v, nuevos_visitados, cost + matriz[u][v], nuevo_camino));
            }
        }
    }

    // Imprime el costo minimo y el mejor camino del ciclo Hamiltoniano encontrado
    if (min_cost != std::numeric_limits<double>::infinity()) {
        outfile << "Costo minimo del ciclo Hamiltoniano: " << min_cost << std::endl;
        outfile << "Camino: ";

        for (int i = 0; i < mejor_camino.size(); ++i) {
            outfile << mejor_camino[i] << (i == mejor_camino.size() - 1 ? "" : "->");
        }
        outfile << std::endl;
        camino = mejor_camino;
    }   else {
        outfile << "No se encontró un ciclo Hamiltoniano" << std::endl;
    }

    outfile.close();  // Cerrar el archivo
    return min_cost;
}
