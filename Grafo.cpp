#include "Grafo.h"
#include <iostream>
#include <cmath>
#include <iomanip>

Grafo::Grafo(const std::vector<std::pair<int, int>>& manchas, const std::set<std::pair<int, int>>& barreras)
        : manchas(manchas), barreras(barreras) {
    crearGrafo();
}

double Grafo::calcularDistancia(std::pair<int, int> a, std::pair<int, int> b) const {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

bool Grafo::hayBarrera(std::pair<int, int> a, std::pair<int, int> b) const {
    for (const auto& barrera : barreras) {
        std::pair<int, int> c = barrera;
        std::pair<int, int> d = {barrera.first + 1, barrera.second};  // Asumiendo que las barreras son segmentos horizontales

        // Vector del segmento (a, b)
        int dx1 = b.first - a.first;
        int dy1 = b.second - a.second;

        // Vector del segmento (c, d)
        int dx2 = d.first - c.first;
        int dy2 = d.second - c.second;

        // Vector entre (a, c)
        int vx = c.first - a.first;
        int vy = c.second - a.second;

        double vp = dx1 * dy2 - dx2 * dy1;
        if (vp == 0) {
            continue;  // Segmentos paralelos
        }

        double k1 = (vx * dy2 - vy * dx2) / vp;
        double k2 = (vx * dy1 - vy * dx1) / vp;

        if (k1 >= 0 && k1 <= 1 && k2 >= 0 && k2 <= 1) {
            return true;  // Los segmentos se intersectan
        }
    }
    return false;
}


void Grafo::crearGrafo() {
    int n = manchas.size();
    matriz.resize(n, std::vector<double>(n, INFINITY));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && !hayBarrera(manchas[i], manchas[j])) {
                matriz[i][j] = calcularDistancia(manchas[i], manchas[j]);
            }
        }
    }
}

void Grafo::imprimir() const {
    int n = manchas.size();
    for (int i = 0; i < n; ++i) {
        std::cout<<"\tM"<<i;
    }
            std::cout<<"\n";
    for (int i = 0; i < n; ++i) {
        std::cout<<"M"<<i<<":\t";
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] == INFINITY) {
                std::cout << "INF\t";
            } else {
                std::cout <<std::fixed << std::setprecision(2)<<matriz[i][j] << "\t";
            }
        }
        std::cout << std::endl;
    }
}

const std::vector<std::vector<double>>& Grafo::getMatriz() const {
    return matriz;
}
