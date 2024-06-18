#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <tuple>

// Node class template
template <class T>
class Nodo {
public:
    T dato;
    Nodo* next;

    Nodo(T a) : dato(a), next(nullptr) {}
};

// List class template
template <class T>
class Lista {
private:
    Nodo<T>* czo;
    Nodo<T>* fin;
public:
    Lista() : czo(nullptr), fin(nullptr) {}
    bool esvacia() { return czo == nullptr; }
    void add(T d);
    T cabeza();
    void borrar();

    void addOrdenado(T d);
};

// Cola class template
template <class T>
class Cola {
private:
    Lista<T> lista;
public:
    Cola() : lista() {}
    T tope() { return lista.cabeza(); }
    bool colavacia() { return lista.esvacia(); }
    void encolar(T a) { lista.add(a); }
    void desencolar() { lista.borrar(); }
};

// Métodos de Lista
template <class T>
void Lista<T>::add(T d) {
    Nodo<T>* nuevo = new Nodo<T>(d);
    if (esvacia()) {
        czo = nuevo;
        fin = nuevo;
    } else {
        fin->next = nuevo;
        fin = nuevo;
    }
}

template <class T>
T Lista<T>::cabeza() {
    if (esvacia()) {
        std::cerr << "Error, Cabeza de lista vacia" << std::endl;
        return T();
    }
    return czo->dato;
}

template <class T>
void Lista<T>::borrar() {
    if (!esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->next;
        delete tmp;
        if (czo == nullptr) {
            fin = nullptr; // Actualizar fin si la lista está vacía
        }
    }
}
template <class T>
void Lista<T>::addOrdenado(T d) {
    Nodo<T>* nuevo = new Nodo<T>(d);
    if (this->esvacia() || d.first < czo->get_dato().first) {
        nuevo->set_next(czo);
        czo = nuevo;
    } else {
        Nodo<T>* aux = czo;
        while (aux->get_next() != nullptr && aux->get_next()->get_dato().first <= d.first) {
            aux = aux->get_next();
        }
        nuevo->set_next(aux->get_next());
        aux->set_next(nuevo);
    }
}

#endif // COLA_H
