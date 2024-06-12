#include "Filtro.h"
#include <iostream>

Filtro::Filtro(const Imagen& img) : imagen(img) {}

void Filtro::encontrarManchas() {
    for (int i = 0; i <= TAMANO - 3; ++i) {
        for (int j = 0; j <= TAMANO - 3; ++j) {
            if (imagen.esMancha(i, j)) {
                manchas.push_back({i + 1, j + 1});
                std::cout << "Mancha encontrada en: (" << i + 1 << ", " << j + 1 << ")\n";
            }
        }
    }
}

const std::vector<std::pair<int, int>>& Filtro::getManchas() const {
    return manchas;
}
