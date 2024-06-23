#include "ArbolB.h"
#include <iostream>
#include <fstream>
#include "sstream"

NodoB::NodoB(int t) {
    claves = new Avion[2*t - 1];
    hijos = new NodoB*[2*t];
    numClaves = 0;
    esHoja = true;
}

NodoB::~NodoB() {
    delete[] claves;
    delete[] hijos;
}

ArbolB::ArbolB(int grado) : raiz(nullptr), t(grado) {}

ArbolB::~ArbolB() {
    liberarMemoriaRecursiva(raiz);
}

void ArbolB::liberarMemoriaRecursiva(NodoB* nodo) {
    if (nodo != nullptr) {
        if (!nodo->esHoja) {
            for (int i = 0; i <= nodo->numClaves; i++) {
                liberarMemoriaRecursiva(nodo->hijos[i]);
            }
        }
        delete nodo;
    }
}

void ArbolB::insertar(const Avion& avion) {
    if (raiz == nullptr) {
        raiz = new NodoB(t);
        raiz->claves[0] = avion;
        raiz->numClaves = 1;
    } else {
        if (raiz->numClaves == 2*t - 1) {
            NodoB* nuevoNodo = new NodoB(t);
            nuevoNodo->hijos[0] = raiz;
            nuevoNodo->esHoja = false;
            dividirHijo(nuevoNodo, 0, raiz);
            raiz = nuevoNodo;
        }
        insertarNoLleno(raiz, avion);
    }
}

void ArbolB::dividirHijo(NodoB* padre, int indice, NodoB* hijo) {
    NodoB* nuevoNodo = new NodoB(t);
    nuevoNodo->esHoja = hijo->esHoja;
    nuevoNodo->numClaves = t - 1;

    for (int j = 0; j < t-1; j++) {
        nuevoNodo->claves[j] = hijo->claves[j+t];
    }

    if (!hijo->esHoja) {
        for (int j = 0; j < t; j++) {
            nuevoNodo->hijos[j] = hijo->hijos[j+t];
        }
    }

    hijo->numClaves = t - 1;

    for (int j = padre->numClaves; j >= indice+1; j--) {
        padre->hijos[j+1] = padre->hijos[j];
    }

    padre->hijos[indice+1] = nuevoNodo;

    for (int j = padre->numClaves-1; j >= indice; j--) {
        padre->claves[j+1] = padre->claves[j];
    }

    padre->claves[indice] = hijo->claves[t-1];
    padre->numClaves++;
}

void ArbolB::insertarNoLleno(NodoB* nodo, const Avion& avion) {
    int i = nodo->numClaves - 1;

    if (nodo->esHoja) {
        while (i >= 0 && avion.getNumeroDeRegistro() < nodo->claves[i].getNumeroDeRegistro()) {
            nodo->claves[i+1] = nodo->claves[i];
            i--;
        }

        nodo->claves[i+1] = avion;
        nodo->numClaves++;
    } else {
        while (i >= 0 && avion.getNumeroDeRegistro() < nodo->claves[i].getNumeroDeRegistro()) {
            i--;
        }

        i++;

        if (nodo->hijos[i]->numClaves == 2*t - 1) {
            dividirHijo(nodo, i, nodo->hijos[i]);

            if (avion.getNumeroDeRegistro() > nodo->claves[i].getNumeroDeRegistro()) {
                i++;
            }
        }
        insertarNoLleno(nodo->hijos[i], avion);
    }
}

void ArbolB::imprimirArbol() {
    if (raiz != nullptr) {
        imprimirNodo(raiz, 0);
    }
}

void ArbolB::imprimirNodo(NodoB* nodo, int nivel) {
    std::cout << "Nivel " << nivel << ": ";
    for (int i = 0; i < nodo->numClaves; i++) {
        std::cout << nodo->claves[i].getNumeroDeRegistro() << " ";
    }
    std::cout << std::endl;

    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->numClaves; i++) {
            imprimirNodo(nodo->hijos[i], nivel + 1);
        }
    }
}
void ArbolB::generarReporte(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph ArbolB {\n";
    archivo << "node [shape=record];\n";

    if (raiz != nullptr) {
        generarReporteRecursivo(raiz, archivo);
    }

    archivo << "}\n";
    archivo.close();

    std::string comando = "dot -Tpng " + nombreArchivo + " -o arbol_b.png";
    system(comando.c_str());
}

void ArbolB::generarReporteRecursivo(NodoB* nodo, std::ofstream& archivo) {
    if (nodo == nullptr) return;

    archivo << "nodo" << nodo << " [label=\"";
    for (int i = 0; i < nodo->numClaves; i++) {
        archivo << nodo->claves[i].getNumeroDeRegistro();
        if (i < nodo->numClaves - 1) archivo << "|";
    }
    archivo << "\"];\n";

    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->numClaves; i++) {
            archivo << "nodo" << nodo << " -> nodo" << nodo->hijos[i] << ";\n";
            generarReporteRecursivo(nodo->hijos[i], archivo);
        }
    }
}