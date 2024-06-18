// Métodos de Lista
template <class T>
void Lista<T>::add(T d) {
    Nodo<T>* nuevo = new Nodo<T>(d);
    if (esvacia()) {
        czo = nuevo;
        fin = nuevo;
    } else {
        fin->set_next(nuevo);
        fin = nuevo;
    }
}

template <class T>
T Lista<T>::cabeza() {
    if (esvacia()) {
        std::cerr << "Error, Cabeza de lista vacia" << std::endl;
        return T();
    }
    return czo->get_dato();
}

template <class T>
void Lista<T>::borrar() {
    if (!esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
        if (czo == nullptr) {
            fin = nullptr; // Actualizar fin si la lista está vacía
        }
    }
}

// Método tope de Cola
template <class T>
T Cola<T>::tope() {
    return lista.cabeza();
}
