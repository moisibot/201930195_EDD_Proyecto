#include "ArbolB.h"
#include <iostream>
#include <fstream>
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
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    archivo << "digraph ArbolB {\n";
    archivo << "node [shape=record, height=.1];\n";
    archivo << "rankdir=TB;\n";
    if (raiz != nullptr) {
        generarReporteRecursivo(raiz, archivo);
    }
    archivo << "}\n";
    archivo.close();
    std::string comando = "dot -Tpng " + nombreArchivo + " -o arbol_b_disponibles.png";
    system(comando.c_str());
}
void ArbolB::generarReporteRecursivo(NodoB* nodo, std::ofstream& archivo) {
    if (nodo == nullptr) return;
    archivo << "nodo" << nodo << " [label=\"";
    for (int i = 0; i < nodo->numClaves; i++) {
        archivo << nodo->claves[i].getNumeroDeRegistro();
        if (i < nodo->numClaves - 1) archivo << " | ";
    }
    archivo << "\"];\n";
    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->numClaves; i++) {
            if (nodo->hijos[i] != nullptr) {
                archivo << "nodo" << nodo << " -> nodo" << nodo->hijos[i] << ";\n";
                generarReporteRecursivo(nodo->hijos[i], archivo);
            }
        }
    }
}

Avion* ArbolB::buscarYEliminar(const std::string& numeroRegistro) {
    return buscarYEliminarRecursivo(raiz, numeroRegistro);
}
Avion* ArbolB::buscarYEliminarRecursivo(NodoB*& nodo, const std::string& numeroRegistro) {
    if (nodo == nullptr) return nullptr;
    int i = 0;
    while (i < nodo->numClaves && numeroRegistro > nodo->claves[i].getNumeroDeRegistro()) {
        i++;
    }
    if (i < nodo->numClaves && numeroRegistro == nodo->claves[i].getNumeroDeRegistro()) {
        Avion* avionEncontrado = new Avion(nodo->claves[i]);
        if (nodo->esHoja) {
            for (int j = i; j < nodo->numClaves - 1; j++) {
                nodo->claves[j] = nodo->claves[j + 1];
            }
            nodo->numClaves--;
            if (nodo->numClaves == 0 && nodo == raiz) {
                delete nodo;
                raiz = nullptr;
            }
        } else {
            Avion sucesor = nodo->hijos[i + 1]->claves[0];
            nodo->claves[i] = sucesor;
            return buscarYEliminarRecursivo(nodo->hijos[i + 1], sucesor.getNumeroDeRegistro());
        }
        return avionEncontrado;
    }
    if (nodo->esHoja) return nullptr;
    bool ultimoHijo = (i == nodo->numClaves);
    if (nodo->hijos[i]->numClaves < t) {
        redistribuirNodos(nodo, i, !ultimoHijo);
    }
    if (ultimoHijo && i > nodo->numClaves) {
        return buscarYEliminarRecursivo(nodo->hijos[i - 1], numeroRegistro);
    } else {
        return buscarYEliminarRecursivo(nodo->hijos[i], numeroRegistro);
    }
}

void ArbolB::redistribuirNodos(NodoB* padre, int indice, bool izquierda) {
    NodoB* hijo = padre->hijos[indice];
    if (izquierda && indice > 0 && padre->hijos[indice - 1]->numClaves >= t) {
        NodoB* izq = padre->hijos[indice - 1];
        for (int i = hijo->numClaves; i > 0; i--) {
            hijo->claves[i] = hijo->claves[i - 1];
        }
        hijo->claves[0] = padre->claves[indice - 1];
        padre->claves[indice - 1] = izq->claves[izq->numClaves - 1];
        if (!hijo->esHoja) {
            for (int i = hijo->numClaves + 1; i > 0; i--) {
                hijo->hijos[i] = hijo->hijos[i - 1];
            }
            hijo->hijos[0] = izq->hijos[izq->numClaves];
        }
        hijo->numClaves++;
        izq->numClaves--;
    } else if (!izquierda && indice < padre->numClaves && padre->hijos[indice + 1]->numClaves >= t) {
        NodoB* der = padre->hijos[indice + 1];
        hijo->claves[hijo->numClaves] = padre->claves[indice];
        padre->claves[indice] = der->claves[0];
        for (int i = 0; i < der->numClaves - 1; i++) {
            der->claves[i] = der->claves[i + 1];
        }
        if (!hijo->esHoja) {
            hijo->hijos[hijo->numClaves + 1] = der->hijos[0];
            for (int i = 0; i < der->numClaves; i++) {
                der->hijos[i] = der->hijos[i + 1];
            }
        }
        hijo->numClaves++;
        der->numClaves--;
    } else {
        if (izquierda && indice > 0) {
            fusionarNodos(padre, indice - 1);
        } else {
            fusionarNodos(padre, indice);
        }
    }
}

void ArbolB::fusionarNodos(NodoB*& padre, int indice) {
    NodoB* hijo1 = padre->hijos[indice];
    NodoB* hijo2 = padre->hijos[indice + 1];
    hijo1->claves[t - 1] = padre->claves[indice];
    for (int i = 0; i < hijo2->numClaves; i++) {
        hijo1->claves[i + t] = hijo2->claves[i];
    }
    if (!hijo1->esHoja) {
        for (int i = 0; i <= hijo2->numClaves; i++) {
            hijo1->hijos[i + t] = hijo2->hijos[i];
        }
    }
    hijo1->numClaves = 2 * t - 1;
    for (int i = indice; i < padre->numClaves - 1; i++) {
        padre->claves[i] = padre->claves[i + 1];
        padre->hijos[i + 1] = padre->hijos[i + 2];
    }
    padre->numClaves--;
    delete hijo2;
    if (padre->numClaves == 0 && padre == raiz) {
        delete padre;
        raiz = hijo1;
    }
}