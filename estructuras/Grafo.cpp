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
    NodoVertice* origenVertice = buscarVertice(origen);
    NodoVertice* destinoVertice = buscarVertice(destino);
    if (!origenVertice || !destinoVertice) {
        std::cerr << "La ciudad de origen o destino no existe en el grafo.\n";
        return;
    }
    NodoVertice* actual = vertices;
    while (actual != nullptr) {
        actual->distancia = INT_MAX;
        actual->padre = nullptr;
        actual = actual->siguiente;
    }
    origenVertice->distancia = 0;
    bool todoVisitado = false;
    while (!todoVisitado) {
        NodoVertice* u = nullptr;
        int minDistancia = INT_MAX;
        actual = vertices;
        todoVisitado = true;
        while (actual != nullptr) {
            if (actual->distancia < minDistancia && actual->padre != actual) {
                u = actual;
                minDistancia = actual->distancia;
                todoVisitado = false;
            }
            actual = actual->siguiente;
        }
        if (u == nullptr) break;
        u->padre = u;
        NodoAdyacencia* adyacente = u->listaAdyacencia;
        while (adyacente != nullptr) {
            NodoVertice* v = buscarVertice(adyacente->ruta.getDestino());
            int alt = u->distancia + adyacente->ruta.getDistanciaDeRuta();
            if (alt < v->distancia) {
                v->distancia = alt;
                v->padre = u;
            }
            adyacente = adyacente->siguiente;
        }
    }
    if (destinoVertice->distancia == INT_MAX) {
        std::cout << "No se encontró un camino desde " << origen << " hasta " << destino << ".\n";
    } else {
        std::cout << "Ruta mas corta desde " << origen << " a " << destino
                  << " con distancia " << destinoVertice->distancia << " km:\n";
        NodoVertice* v = destinoVertice;
        NodoCamino* camino = nullptr;
        while (v != nullptr && v != v->padre) {
            NodoCamino* nuevoCamino = new NodoCamino(v->ciudad);
            nuevoCamino->siguiente = camino;
            camino = nuevoCamino;
            v = v->padre;
        }
        while (camino != nullptr) {
            std::cout << camino->ciudad;
            camino = camino->siguiente;
            if (camino != nullptr) std::cout << " -> ";
        }
        std::cout << std::endl;
NodoCamino* temp = camino;
        while (camino != nullptr) {
            NodoCamino* temp = camino;
            camino = camino->siguiente;
            delete temp;
        }
        camino= nullptr;
    }
}
