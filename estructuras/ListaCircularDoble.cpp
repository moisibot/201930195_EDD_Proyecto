#include "ListaCircularDoble.h"
#include <iostream>
#include <fstream>

NodoLCD::NodoLCD(const Avion& avion) : dato(avion), siguiente(nullptr), anterior(nullptr) {}

ListaCircularDoble::ListaCircularDoble() : cabeza(nullptr) {}

ListaCircularDoble::~ListaCircularDoble() {
    if (cabeza == nullptr) return;

    NodoLCD* actual = cabeza;
    do {
        NodoLCD* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);
}

void ListaCircularDoble::insertar(const Avion& avion) {
    NodoLCD* nuevoNodo = new NodoLCD(avion);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cabeza->anterior;
        cabeza->anterior->siguiente = nuevoNodo;
        cabeza->anterior = nuevoNodo;
    }
}

bool ListaCircularDoble::eliminar(const std::string& numeroRegistro) {
    if (cabeza == nullptr) return false;

    NodoLCD* actual = cabeza;
    do {
        if (actual->dato.getNumeroDeRegistro() == numeroRegistro) {
            if (actual == cabeza && actual->siguiente == cabeza) {
                delete cabeza;
                cabeza = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == cabeza) cabeza = actual->siguiente;
                delete actual;
            }
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

void ListaCircularDoble::imprimir() {
    if (cabeza == nullptr) {
        std::cout << "Lista vacía" << std::endl;
        return;
    }

    NodoLCD* actual = cabeza;
    do {
        std::cout << actual->dato.getNumeroDeRegistro() << " ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << std::endl;
}
void ListaCircularDoble::generarReporte(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph ListaCircularDoble {\n";
    archivo << "node [shape=record];\n";

    if (cabeza != nullptr) {
        NodoLCD* actual = cabeza;
        do {
            archivo << "nodo" << actual << " [label=\"" << actual->dato.getNumeroDeRegistro() << "\"];\n";
            archivo << "nodo" << actual << " -> nodo" << actual->siguiente << ";\n";
            archivo << "nodo" << actual << " -> nodo" << actual->anterior << " [dir=back];\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    archivo << "}\n";
    archivo.close();

    std::string comando = "dot -Tpng " + nombreArchivo + " -o lista_circular_doble.png";
    system(comando.c_str());
}
Avion* ListaCircularDoble::buscarYEliminar(const std::string& numeroRegistro) {
    if (cabeza == nullptr) return nullptr;

    NodoLCD* actual = cabeza;
    do {
        if (actual->dato.getNumeroDeRegistro() == numeroRegistro) {
            if (actual == cabeza && actual->siguiente == cabeza) {
                cabeza = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == cabeza) cabeza = actual->siguiente;
            }
            Avion* avionEncontrado = new Avion(actual->dato);
            delete actual;
            return avionEncontrado;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}