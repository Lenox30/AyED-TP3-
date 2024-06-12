#include "Grafo.h"
#include <iostream>
#include <cmath>

Grafo::Grafo(const std::vector<std::pair<int, int>>& manchas, const std::set<std::pair<int, int>>& barreras)
        : manchas(manchas), barreras(barreras) {
    crearGrafo();
}

double Grafo::calcularDistancia(std::pair<int, int> a, std::pair<int, int> b) const {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

bool Grafo::hayBarrera(std::pair<int, int> a, std::pair<int, int> b) const {
    // Implementar lógica para verificar si hay una barrera entre a y b
    // Por simplicidad, vamos a asumir que las barreras son líneas rectas
    // y que cualquier cruce entre los puntos a y b debe ser evitado.
    // Esta implementación es un simplificación y puede ser mejorada según el caso de uso.
    int minX = std::min(a.first, b.first);
    int maxX = std::max(a.first, b.first);
    int minY = std::min(a.second, b.second);
    int maxY = std::max(a.second, b.second);

    for (const auto& barrera : barreras) {
        if ((barrera.first >= minX && barrera.first <= maxX) &&
            (barrera.second >= minY && barrera.second <= maxY)) {
            return true;
        }
    }
    return false;
}

void Grafo::crearGrafo() {
    int n = manchas.size();
    matriz.resize(n, std::vector<double>(n, INFINITY));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && !hayBarrera(manchas[i], manchas[j])) {
                matriz[i][j] = calcularDistancia(manchas[i], manchas[j]);
            }
        }
    }
}

void Grafo::imprimir() const {
    int n = manchas.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] == INFINITY) {
                std::cout << "INF ";
            } else {
                std::cout << matriz[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

const std::vector<std::vector<double>>& Grafo::getMatriz() const {
    return matriz;
}
