#include "Grafo.h"
#include <iostream>
#include <fstream>

NodoAdyacencia::NodoAdyacencia(const Ruta& r) : ruta(r), siguiente(nullptr) {}
NodoVertice::NodoVertice(const std::string& c) : ciudad(c), listaAdyacencia(nullptr), siguiente(nullptr) {}
Grafo::Grafo() : vertices(nullptr) {}
Grafo::~Grafo() {
    while (vertices != nullptr) {
        NodoVertice* tempV = vertices;
        vertices = vertices->siguiente;

        while (tempV->listaAdyacencia != nullptr) {
            NodoAdyacencia* tempA = tempV->listaAdyacencia;
            tempV->listaAdyacencia = tempV->listaAdyacencia->siguiente;
            delete tempA;
        }

        delete tempV;
    }
}

NodoVertice* Grafo::buscarVertice(const std::string& ciudad) {
    NodoVertice* actual = vertices;
    while (actual != nullptr) {
        if (actual->ciudad == ciudad) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

NodoVertice* Grafo::agregarVertice(const std::string& ciudad) {
    NodoVertice* nuevoVertice = new NodoVertice(ciudad);
    nuevoVertice->siguiente = vertices;
    vertices = nuevoVertice;
    return nuevoVertice;
}

void Grafo::agregarRuta(const Ruta& ruta) {
    NodoVertice* origen = buscarVertice(ruta.getOrigen());
    if (origen == nullptr) {
        origen = agregarVertice(ruta.getOrigen());
    }

    NodoAdyacencia* nuevaAdyacencia = new NodoAdyacencia(ruta);
    nuevaAdyacencia->siguiente = origen->listaAdyacencia;
    origen->listaAdyacencia = nuevaAdyacencia;

    // Asegúrate de que el destino también exista como vértice
    if (buscarVertice(ruta.getDestino()) == nullptr) {
        agregarVertice(ruta.getDestino());
    }
}

void Grafo::imprimirGrafo() {
    NodoVertice* actualVertice = vertices;
    while (actualVertice != nullptr) {
        std::cout << actualVertice->ciudad << " -> ";
        NodoAdyacencia* actualAdyacencia = actualVertice->listaAdyacencia;
        while (actualAdyacencia != nullptr) {
            std::cout << actualAdyacencia->ruta.getDestino() << "(" << actualAdyacencia->ruta.getDistanciaDeRuta() << "km) ";
            actualAdyacencia = actualAdyacencia->siguiente;
        }
        std::cout << std::endl;
        actualVertice = actualVertice->siguiente;
    }
}
void Grafo::generarReporte(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph Grafo {\n";

    NodoVertice* actualVertice = vertices;
    while (actualVertice != nullptr) {
        archivo << "\"" << actualVertice->ciudad << "\";\n";
        NodoAdyacencia* actualAdyacencia = actualVertice->listaAdyacencia;
        while (actualAdyacencia != nullptr) {
            archivo << "\"" << actualVertice->ciudad << "\" -> \""
                    << actualAdyacencia->ruta.getDestino() << "\" [label=\""
                    << actualAdyacencia->ruta.getDistanciaDeRuta() << "km\"];\n";
            actualAdyacencia = actualAdyacencia->siguiente;
        }
        actualVertice = actualVertice->siguiente;
    }

    archivo << "}\n";
    archivo.close();

    std::string comando = "dot -Tpng " + nombreArchivo + " -o grafo_rutas.png";
    system(comando.c_str());
}