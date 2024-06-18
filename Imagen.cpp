#include "Imagen.h"

Imagen::Imagen(const std::string& nombreArchivo) {
    leerDesdeArchivo(nombreArchivo);
}

void Imagen::leerDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    int fila = 0;
    while (std::getline(archivo, linea) && fila < TAMANO) {
        for (int columna = 0; columna < linea.size(); ++columna) {
            if (linea[columna] == '1') {
                imagenBits.set(fila * TAMANO + columna);
            } else if (linea[columna] == 'X') {
                barreras.insert({fila, columna});
                std::cout << "Barrera encontrada en: (" << fila +1<< ", " << columna +1<< ")\n";
            }
        }
        ++fila;
    }
    archivo.close();
}

void Imagen::imprimir() const {
    for (int i = 0; i < TAMANO; ++i) {
        for (int j = 0; j < TAMANO; ++j) {
            if (barreras.find({i, j}) != barreras.end()) {
                std::cout << 'X'<<" ";
            } else if (imagenBits[i * TAMANO + j]) {
                std::cout << '1'<<" ";
            } else {
                std::cout << '0'<<" ";
            }
        }
        std::cout << std::endl;
    }
}

bool Imagen::esMancha(int fila, int columna) const {
    for (int k = 0; k < 3; ++k) {
        for (int l = 0; l < 3; ++l) {
            if (barreras.find({fila + k, columna + l}) != barreras.end() || 
                !imagenBits[(fila + k) * TAMANO + (columna + l)]) {
                return false;
            }
        }
    }
    return true;
}

const std::set<std::pair<int, int>>& Imagen::getBarreras() const {
    return barreras;  // Agregado para obtener las barreras
}