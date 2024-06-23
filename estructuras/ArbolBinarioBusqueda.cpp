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

void ArbolBinarioBusqueda::inorden() {
    inordenRecursivo(raiz);
    std::cout << std::endl;
}

void ArbolBinarioBusqueda::inordenRecursivo(NodoABB* nodo) {
    if (nodo != nullptr) {
        inordenRecursivo(nodo->izquierdo);
        std::cout << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas) ";
        inordenRecursivo(nodo->derecho);
    }
}

void ArbolBinarioBusqueda::preorden() {
    preordenRecursivo(raiz);
    std::cout << std::endl;
}

void ArbolBinarioBusqueda::preordenRecursivo(NodoABB* nodo) {
    if (nodo != nullptr) {
        std::cout << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas) ";
        preordenRecursivo(nodo->izquierdo);
        preordenRecursivo(nodo->derecho);
    }
}

void ArbolBinarioBusqueda::postorden() {
    postordenRecursivo(raiz);
    std::cout << std::endl;
}

void ArbolBinarioBusqueda::postordenRecursivo(NodoABB* nodo) {
    if (nodo != nullptr) {
        postordenRecursivo(nodo->izquierdo);
        postordenRecursivo(nodo->derecho);
        std::cout << nodo->dato.getNombre() << " (" << nodo->dato.getHorasDeVuelo() << " horas) ";
    }
}
void ArbolBinarioBusqueda::eliminarPiloto(int horasDeVuelo) {
    raiz = eliminarNodo(raiz, horasDeVuelo);
}

NodoABB* ArbolBinarioBusqueda::eliminarNodo(NodoABB* nodo, int horasDeVuelo) {
    if (nodo == nullptr) return nodo;
    if (horasDeVuelo < nodo->dato.getHorasDeVuelo()) {
        nodo->izquierdo = eliminarNodo(nodo->izquierdo, horasDeVuelo);
    } else if (horasDeVuelo > nodo->dato.getHorasDeVuelo()) {
        nodo->derecho = eliminarNodo(nodo->derecho, horasDeVuelo);
    } else {
        // Nodo con solo un hijo o sin hijos
        if (nodo->izquierdo == nullptr) {
            NodoABB* temp = nodo->derecho;
            delete nodo;
            return temp;
        } else if (nodo->derecho == nullptr) {
            NodoABB* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }
        // Nodo con dos hijos: obtener el sucesor inorden (mínimo en el subárbol derecho)
        NodoABB* temp = encontrarMinimo(nodo->derecho);
        // Copiar el contenido del sucesor inorden a este nodo
        nodo->dato = temp->dato;
        // Eliminar el sucesor inorden
        nodo->derecho = eliminarNodo(nodo->derecho, temp->dato.getHorasDeVuelo());
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
void ArbolBinarioBusqueda::generarReporte(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph ArbolBinario {\n";

    generarReporteRecursivo(raiz, archivo);

    archivo << "}\n";
    archivo.close();

    std::string comando = "dot -Tpng " + nombreArchivo + " -o arbol_binario.png";
    system(comando.c_str());
}

void ArbolBinarioBusqueda::generarReporteRecursivo(NodoABB* nodo, std::ofstream& archivo) {
    if (nodo == nullptr) return;

    archivo << "nodo" << nodo << " [label=\"" << nodo->dato.getNombre() << "\\n"
            << nodo->dato.getHorasDeVuelo() << " horas\"];\n";

    if (nodo->izquierdo != nullptr) {
        archivo << "nodo" << nodo << " -> nodo" << nodo->izquierdo << ";\n";
        generarReporteRecursivo(nodo->izquierdo, archivo);
    }

    if (nodo->derecho != nullptr) {
        archivo << "nodo" << nodo << " -> nodo" << nodo->derecho << ";\n";
        generarReporteRecursivo(nodo->derecho, archivo);
    }
}