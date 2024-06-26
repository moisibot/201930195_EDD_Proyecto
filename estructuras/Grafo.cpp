#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <algorithm>

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
std::vector<std::string> Grafo::encontrarRutaMasCorta(const std::string& origen, const std::string& destino) {
    std::unordered_map<std::string, int> distancias;
    std::unordered_map<std::string, std::string> previos;
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;
    NodoVertice* actual = vertices;
    while (actual != nullptr) {
        distancias[actual->ciudad] = std::numeric_limits<int>::max();
        actual = actual->siguiente;
    }
    distancias[origen] = 0;
    pq.push({0, origen});
    while (!pq.empty()) {
        std::string ciudadActual = pq.top().second;
        int distanciaActual = pq.top().first;
        pq.pop();
        if (ciudadActual == destino) break;
        NodoVertice* verticeActual = buscarVertice(ciudadActual);
        NodoAdyacencia* adyacente = verticeActual->listaAdyacencia;
        while (adyacente != nullptr) {
            int nuevaDistancia = distanciaActual + adyacente->ruta.getDistanciaDeRuta();
            if (nuevaDistancia < distancias[adyacente->ruta.getDestino()]) {
                distancias[adyacente->ruta.getDestino()] = nuevaDistancia;
                previos[adyacente->ruta.getDestino()] = ciudadActual;
                pq.push({nuevaDistancia, adyacente->ruta.getDestino()});
            }
            adyacente = adyacente->siguiente;
        }
    }
    std::vector<std::string> ruta;
    std::string ciudadActual = destino;
    while (ciudadActual != origen) {
        ruta.push_back(ciudadActual);
        ciudadActual = previos[ciudadActual];
    }
    ruta.push_back(origen);
    std::reverse(ruta.begin(), ruta.end());
    return ruta;
}
