#include "Filtro.h"


Filtro::Filtro(const Imagen& img) : imagen(img) {}

void Filtro::encontrarManchas() {
    int m=0;
    for (int i = 0; i <= TAMANO - 3; ++i) {
        for (int j = 0; j <= TAMANO - 3; ++j) {
            if (imagen.esMancha(i, j)) {
                manchas.push_back({i + 1, j + 1});
                std::cout << "Mancha "<<m<< " encontrada en: (" << i + 1 << ", " << j + 1 << ")\n";
                m++;
            }
        }
    }
}

const std::vector<std::pair<int, int>>& Filtro::getManchas() const {
    return manchas;
}
