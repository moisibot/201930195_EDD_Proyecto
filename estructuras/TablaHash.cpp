#include "TablaHash.h"
#include <iostream>
#include <fstream>
NodoHash::NodoHash(const Piloto& piloto) : dato(piloto), siguiente(nullptr) {}
TablaHash::TablaHash(int tamanioInicial) : tamanio(tamanioInicial), elementos(0) {
    tabla = new NodoHash*[tamanio];
    for (int i = 0; i < tamanio; i++) {
        tabla[i] = nullptr;
    }
}
TablaHash::~TablaHash() {
    for (int i = 0; i < tamanio; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            NodoHash* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
    delete[] tabla;
}

int TablaHash::funcionHash(const std::string& id) {
    int suma = 0;
    for (char c : id) {
        suma += c;
    }
    return suma % tamanio;
}
void TablaHash::insertar(const Piloto& piloto) {
    if (static_cast<double>(elementos) / tamanio > 0.75) {
        redimensionar();
    }
    int indice = funcionHash(piloto.getNumeroDeId());
    NodoHash* nuevoNodo = new NodoHash(piloto);
    nuevoNodo->siguiente = tabla[indice];
    tabla[indice] = nuevoNodo;
    elementos++;
}
bool TablaHash::eliminar(const std::string& id) {
    int indice = funcionHash(id);
    NodoHash* actual = tabla[indice];
    NodoHash* anterior = nullptr;
    while (actual != nullptr && actual->dato.getNumeroDeId() != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        return false;
    }
    if (anterior == nullptr) {
        tabla[indice] = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    delete actual;
    elementos--;
    return true;
}

Piloto* TablaHash::buscar(const std::string& id) {
    int indice = funcionHash(id);
    NodoHash* actual = tabla[indice];
    while (actual != nullptr) {
        if (actual->dato.getNumeroDeId() == id) {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void TablaHash::redimensionar() {
    int nuevoTamanio = tamanio * 2;
    NodoHash** nuevaTabla = new NodoHash*[nuevoTamanio];
    for (int i = 0; i < nuevoTamanio; i++) {
        nuevaTabla[i] = nullptr;
    }
    for (int i = 0; i < tamanio; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            NodoHash* siguiente = actual->siguiente;
            int nuevoIndice = funcionHash(actual->dato.getNumeroDeId()) % nuevoTamanio;
            actual->siguiente = nuevaTabla[nuevoIndice];
            nuevaTabla[nuevoIndice] = actual;
            actual = siguiente;
        }
    }
    delete[] tabla;
    tabla = nuevaTabla;
    tamanio = nuevoTamanio;
}

void TablaHash::imprimir() {
    for (int i = 0; i < tamanio; i++) {
        std::cout << "Índice " << i << ": ";
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            std::cout << actual->dato.getNombre() << " (" << actual->dato.getNumeroDeId() << ") -> ";
            actual = actual->siguiente;
        }
        std::cout << "nullptr" << std::endl;
    }
}
void TablaHash::generarReporte(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph TablaHash {\n";
    archivo << "node [shape=record];\n";
    for (int i = 0; i < tamanio; i++) {
        archivo << "bucket" << i << " [label=\"" << i << "\"];\n";
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            archivo << "nodo" << actual << " [label=\"" << actual->dato.getNombre()
                    << "\\n" << actual->dato.getNumeroDeId() << "\"];\n";
            archivo << "bucket" << i << " -> nodo" << actual << ";\n";
            if (actual->siguiente != nullptr) {
                archivo << "nodo" << actual << " -> nodo" << actual->siguiente << ";\n";
            }
            actual = actual->siguiente;
        }
    }
    archivo << "}\n";
    archivo.close();
    std::string comando = "dot -Tpng " + nombreArchivo + " -o tabla_hash.png";
    system(comando.c_str());
}