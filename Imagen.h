#ifndef IMAGEN_H
#define IMAGEN_H

#include <bitset>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


const int TAMANO = 100;

class Imagen {
public:
    Imagen(const std::string& nombreArchivo);
    void imprimir() const;
    bool esMancha(int fila, int columna) const;
    const std::set<std::pair<int, int>>& getBarreras() const;  // Agregado para obtener las barreras

private:
    std::bitset<TAMANO * TAMANO> imagenBits;
    std::set<std::pair<int, int>> barreras;

    void leerDesdeArchivo(const std::string& nombreArchivo);
};

#endif // IMAGEN_H
