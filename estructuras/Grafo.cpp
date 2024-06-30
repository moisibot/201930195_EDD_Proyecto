#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>

NodoAdyacencia::NodoAdyacencia(const Ruta& r) : ruta(r), siguiente(nullptr) {}
NodoVertice::NodoVertice(const std::string& c) : ciudad(c), listaAdyacencia(nullptr), siguiente(nullptr) {}
NodoCamino::NodoCamino(const std::string& c) : ciudad(c), siguiente(nullptr) {}

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
            std::cout << actualAdyacencia->ruta.getDestino() << "(" << actualAdyacencia->ruta.getDistanciaDeRuta() << ") ";
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
                    << actualAdyacencia->ruta.getDistanciaDeRuta() << "\"];\n";
            actualAdyacencia = actualAdyacencia->siguiente;
        }
        actualVertice = actualVertice->siguiente;
    }
    archivo << "}\n";
    archivo.close();
    std::string comando = "dot -Tpng " + nombreArchivo + " -o grafo_rutas.png";
    system(comando.c_str());
}

void Grafo::encontrarTodasLasRutasAux(NodoVertice* verticeActual, const std::string& destino, NodoCamino* camino, NodoCamino*& rutas) {
    if (!verticeActual || camino == nullptr) {
        return;
    }
    NodoCamino* nuevoCamino = new NodoCamino(verticeActual->ciudad);
    nuevoCamino->siguiente = camino;
    camino = nuevoCamino;
    if (verticeActual->ciudad == destino) {
        NodoCamino* ruta = nullptr;
        NodoCamino* temp = camino;
        while (temp != nullptr) {
            NodoCamino* nuevoNodo = new NodoCamino(temp->ciudad);
            nuevoNodo->siguiente = ruta;
            ruta = nuevoNodo;
            temp = temp->siguiente;
        }
        ruta->siguiente = rutas;
        rutas = ruta;
    } else {
        NodoAdyacencia* adyacente = verticeActual->listaAdyacencia;
        while (adyacente != nullptr) {
            NodoVertice* siguienteVertice = buscarVertice(adyacente->ruta.getDestino());
            encontrarTodasLasRutasAux(siguienteVertice, destino, camino, rutas);
            adyacente = adyacente->siguiente;
        }
    }
    while (camino != nullptr) {
        NodoCamino* temp = camino;
        camino = camino->siguiente;
        delete temp;
    }
}

NodoCamino* Grafo::encontrarTodasLasRutas(const std::string& origen, const std::string& destino) {
    NodoVertice* verticeOrigen = buscarVertice(origen);
    if (verticeOrigen == nullptr) {
        std::cerr << "La ciudad de origen '" << origen << "' no existe en el grafo.\n";
        return nullptr;
    }

    NodoCamino* rutas = nullptr;
    NodoCamino* camino = nullptr;
    encontrarTodasLasRutasAux(verticeOrigen, destino, camino, rutas);
    return rutas;
}

void Grafo::recomendarRutas(const std::string& origen, const std::string& destino) {
    NodoCamino* rutas = encontrarTodasLasRutas(origen, destino);
    if (rutas == nullptr) {
        std::cerr << "No se encontró una ruta válida desde '" << origen << "' hasta '" << destino << "'.\n";
        return;
    }

    NodoCamino* temp = rutas;
    while (temp != nullptr) {
        std::string ciudadActual = temp->ciudad;
        std::cout << ciudadActual << " -> ";
        NodoCamino* siguiente = temp->siguiente;
        if (siguiente != nullptr) {
            NodoVertice* verticeActual = buscarVertice(ciudadActual);
            NodoAdyacencia* adyacente = verticeActual->listaAdyacencia;
            while (adyacente != nullptr) {
                if (adyacente->ruta.getDestino() == siguiente->ciudad) {
                    std::cout << adyacente->ruta.getDestino() << "(" << adyacente->ruta.getDistanciaDeRuta() << ") ";
                    break;
                }
                adyacente = adyacente->siguiente;
            }
        }
        temp = temp->siguiente;
    }
    std::cout << std::endl;

    // Liberar memoria de la lista de rutas
    while (rutas != nullptr) {
        NodoCamino* temp = rutas;
        rutas = rutas->siguiente;
        delete temp;
    }
}

void Grafo::imprimirRutasDesde(const std::string& ciudad) {
    NodoVertice* vertice = buscarVertice(ciudad);
    if (!vertice) {
        std::cout << "La ciudad " << ciudad << " no existe en el grafo." << std::endl;
        return;
    }

    NodoAdyacencia* adyacente = vertice->listaAdyacencia;
    while (adyacente) {
        std::cout << ciudad << " -> " << adyacente->ruta.getDestino()
                  << " (" << adyacente->ruta.getDistanciaDeRuta() << ")" << std::endl;
        adyacente = adyacente->siguiente;
    }
}

void Grafo::dijkstra(const std::string& origen, const std::string& destino) {
    const int MAX_CIUDADES = 100;
    int distancias[MAX_CIUDADES];
    bool visitados[MAX_CIUDADES] = { false };
    NodoVertice* previos[MAX_CIUDADES] = { nullptr };
    int numCiudades = 0;
    NodoVertice* actual = vertices;
    while (actual != nullptr) {
        distancias[numCiudades] = INT_MAX;
        actual = actual->siguiente;
        numCiudades++;
    }
    NodoVertice* origenVertice = buscarVertice(origen);
    NodoVertice* destinoVertice = buscarVertice(destino);
    if (!origenVertice || !destinoVertice) {
        std::cerr << "La ciudad de origen o destino no existe en el grafo.\n";
        return;
    }
    int indiceOrigen = 0;
    actual = vertices;
    while (actual != origenVertice) {
        indiceOrigen++;
        actual = actual->siguiente;
    }
    distancias[indiceOrigen] = 0;
    for (int i = 0; i < numCiudades; ++i) {
        int minDistancia = INT_MAX;
        int u = -1;
        actual = vertices;
        for (int j = 0; j < numCiudades; ++j) {
            if (!visitados[j] && distancias[j] < minDistancia) {
                minDistancia = distancias[j];
                u = j;
            }
            actual = actual->siguiente;
        }
        if (u == -1) break;
        visitados[u] = true;
        actual = vertices;
        for (int j = 0; j < u; ++j) actual = actual->siguiente;
        NodoAdyacencia* adyacente = actual->listaAdyacencia;
        while (adyacente != nullptr) {
            NodoVertice* v = buscarVertice(adyacente->ruta.getDestino());
            int indiceV = 0;
            NodoVertice* temp = vertices;
            while (temp != v) {
                indiceV++;
                temp = temp->siguiente;
            }
            if (!visitados[indiceV] && distancias[u] + adyacente->ruta.getDistanciaDeRuta() < distancias[indiceV]) {
                distancias[indiceV] = distancias[u] + adyacente->ruta.getDistanciaDeRuta();
                previos[indiceV] = actual;
            }
            adyacente = adyacente->siguiente;
        }
    }
    int indiceDestino = 0;
    actual = vertices;
    while (actual != destinoVertice) {
        indiceDestino++;
        actual = actual->siguiente;
    }
    if (distancias[indiceDestino] == INT_MAX) {
        std::cerr << "No hay ruta disponible entre " << origen << " y " << destino << "." << std::endl;
        return;
    }
    std::cout << "Ruta mas corta desde " << origen << " a " << destino
              << " con distancia " << distancias[indiceDestino] << " km:" << std::endl;
    NodoCamino* camino = nullptr;
    for (NodoVertice* v = destinoVertice; v != nullptr; v = previos[indiceDestino]) {
        NodoCamino* nuevoCamino = new NodoCamino(v->ciudad);
        nuevoCamino->siguiente = camino;
        camino = nuevoCamino;
        if (v == origenVertice) break;
        indiceDestino = 0;
        actual = vertices;
        while (actual != v) {
            indiceDestino++;
            actual = actual->siguiente;
        }
    }
    NodoCamino* nodoActual = camino;
    while (nodoActual != nullptr) {
        std::cout << nodoActual->ciudad;
        if (nodoActual->siguiente != nullptr) std::cout << " -> ";
        nodoActual = nodoActual->siguiente;
    }
    std::cout << std::endl;
    while (camino != nullptr) {
        NodoCamino* temp = camino;
        camino = camino->siguiente;
        delete temp;
    }
}
