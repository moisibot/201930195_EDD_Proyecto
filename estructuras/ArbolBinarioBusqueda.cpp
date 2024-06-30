#include "ArbolBinarioBusqueda.h"
#include <iostream>
#include <fstream>

NodoABB::NodoABB(const Piloto& piloto) : dato(piloto), izquierdo(nullptr), derecho(nullptr) {}

ArbolBinarioBusqueda::ArbolBinarioBusqueda() : raiz(nullptr) {}

ArbolBinarioBusqueda::~ArbolBinarioBusqueda() {
    destruirRecursivo(raiz);
}
void ArbolBinarioBusqueda::destruirRecursivo(NodoABB* nodo) {
    if (nodo != nullptr) {
        destruirRecursivo(nodo->izquierdo);
        destruirRecursivo(nodo->derecho);
        delete nodo;
    }
}

void ArbolBinarioBusqueda::insertar(const Piloto& piloto) {
    insertarRecursivo(raiz, piloto);
}
void ArbolBinarioBusqueda::insertarRecursivo(NodoABB*& nodo, const Piloto& piloto) {
    if (nodo == nullptr) {
        nodo = new NodoABB(piloto);
    } else if (piloto.getHorasDeVuelo() < nodo->dato.getHorasDeVuelo()) {
        insertarRecursivo(nodo->izquierdo, piloto);
    } else {
        insertarRecursivo(nodo->derecho, piloto);
    }
}

void ArbolBinarioBusqueda::inorden() const {
    inordenRecursivo(raiz);
    std::cout << std::endl;
}
void ArbolBinarioBusqueda::inordenRecursivo(NodoABB* nodo) const {
    if (nodo != nullptr) {
        inordenRecursivo(nodo->izquierdo);
        std::cout << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas) ";
        inordenRecursivo(nodo->derecho);
    }
}

void ArbolBinarioBusqueda::preorden() const {
    preordenRecursivo(raiz);
    std::cout << std::endl;
}
void ArbolBinarioBusqueda::preordenRecursivo(NodoABB* nodo) const {
    if (nodo != nullptr) {
        std::cout << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas) ";
        preordenRecursivo(nodo->izquierdo);
        preordenRecursivo(nodo->derecho);
    }
}

void ArbolBinarioBusqueda::postorden() const {
    postordenRecursivo(raiz);
    std::cout << std::endl;
}
void ArbolBinarioBusqueda::postordenRecursivo(NodoABB* nodo) const {
    if (nodo != nullptr) {
        postordenRecursivo(nodo->izquierdo);
        postordenRecursivo(nodo->derecho);
        std::cout << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas) ";
    }
}

void ArbolBinarioBusqueda::generarReporte(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph ArbolBinario {\n";
    generarDotRecursivo(raiz, archivo);
    archivo << "}\n";
    archivo.close();
    std::string comando = "dot -Tpng " + nombreArchivo + " -o arbol_binario_pilotos.png";
    system(comando.c_str());
}
void ArbolBinarioBusqueda::generarDotRecursivo(NodoABB* nodo, std::ofstream& archivo) const {
    if (nodo != nullptr) {
        archivo << "\"" << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas)\" [label=\""
                << nodo->dato.getNombre() << "\\n" << nodo->dato.getHorasDeVuelo() << " horas\"];\n";

        if (nodo->izquierdo != nullptr) {
            archivo << "\"" << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas)\" -> \""
                    << nodo->izquierdo->dato.getNombre() << " (" << nodo->izquierdo->dato.getHorasDeVuelo() << " horas)\";\n";
            generarDotRecursivo(nodo->izquierdo, archivo);
        }

        if (nodo->derecho != nullptr) {
            archivo << "\"" << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas)\" -> \""
                    << nodo->derecho->dato.getNombre() << " (" << nodo->derecho->dato.getHorasDeVuelo() << " horas)\";\n";
            generarDotRecursivo(nodo->derecho, archivo);
        }
    }
}

void ArbolBinarioBusqueda::eliminar(const std::string& id) {
    raiz = eliminarRecursivo(raiz, id);
}
NodoABB* ArbolBinarioBusqueda::eliminarRecursivo(NodoABB* nodo, const std::string& id) {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (id < nodo->dato.getNumeroDeId()) {
        nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, id);
    } else if (id > nodo->dato.getNumeroDeId()) {
        nodo->derecho = eliminarRecursivo(nodo->derecho, id);
    } else {
        if (nodo->izquierdo == nullptr) {
            NodoABB* temp = nodo->derecho;
            delete nodo;
            return temp;
        } else if (nodo->derecho == nullptr) {
            NodoABB* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }
        NodoABB* temp = encontrarMinimo(nodo->derecho);
        nodo->dato = temp->dato;
        nodo->derecho = eliminarRecursivo(nodo->derecho, temp->dato.getNumeroDeId());
    }

    return nodo;
}

NodoABB* ArbolBinarioBusqueda::encontrarMinimo(NodoABB* nodo) {
    NodoABB* actual = nodo;
    while (actual && actual->izquierdo != nullptr) {
        actual = actual->izquierdo;
    }
    return actual;
}



