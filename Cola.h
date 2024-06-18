#ifndef COLA_H
#define COLA_H

#include <iostream>

// Clase Nodo como template
template <class T>
class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() : next(nullptr) {}
    Nodo(T a) : dato(a), next(nullptr) {}
    void set_dato(T a) { dato = a; }
    void set_next(Nodo* n) { next = n; }
    T get_dato() { return dato; }
    Nodo* get_next() { return next; }
};

// Clase Lista como template
template <class T>
class Lista {
private:
    Nodo<T>* czo;
    Nodo<T>* fin; // Nodo al final de la lista
public:
    Lista() : czo(nullptr), fin(nullptr) {}
    bool esvacia() { return czo == nullptr; }
    void add(T d); // Suma nodos a la lista
    T cabeza(); // Retorna el dato del primer nodo
    void borrar();
};

// Clase Cola como template
template <class T>
class Cola {
private:
    Lista<T> lista;
public:
    Cola() : lista() {}
    T tope();
    bool colavacia() { return lista.esvacia(); }
    void encolar(T a) { lista.add(a); }
    void desencolar() { lista.borrar(); }
};

#include "Cola.tpp"  // Incluir la implementación

#endif // COLA_H
