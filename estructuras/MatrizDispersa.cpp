#include "MatrizDispersa.h"
#include <iostream>
#include <fstream>
NodoMatriz::NodoMatriz(const std::string& vuelo, const std::string& ciudadDestino, Piloto* piloto, int distancia)
        : vuelo(vuelo), ciudadDestino(ciudadDestino), piloto(piloto), distancia(distancia), derecha(nullptr), abajo(nullptr) {}

MatrizDispersa::MatrizDispersa() : filas(nullptr), columnas(nullptr) {}
MatrizDispersa::~MatrizDispersa() {
    // Implementar la liberación de memoria
}

NodoMatriz* MatrizDispersa::buscarOCrearFila(const std::string& vuelo) {
    if (filas == nullptr || vuelo < filas->vuelo) {
        NodoMatriz* nuevaFila = new NodoMatriz(vuelo, "", nullptr, 0);  // Añadimos 0 como distancia por defecto
        nuevaFila->abajo = filas;
        filas = nuevaFila;
        return nuevaFila;
    }
    NodoMatriz* actual = filas;
    while (actual->abajo != nullptr && actual->abajo->vuelo <= vuelo) {
        if (actual->vuelo == vuelo) {
            return actual;
        }
        actual = actual->abajo;
    }
    if (actual->vuelo == vuelo) {
        return actual;
    }
    NodoMatriz* nuevaFila = new NodoMatriz(vuelo, "", nullptr, 0);  // Añadimos 0 como distancia por defecto
    nuevaFila->abajo = actual->abajo;
    actual->abajo = nuevaFila;
    return nuevaFila;
}

NodoMatriz* MatrizDispersa::buscarOCrearColumna(const std::string& ciudadDestino) {
    if (columnas == nullptr || ciudadDestino < columnas->ciudadDestino) {
        NodoMatriz* nuevaColumna = new NodoMatriz("", ciudadDestino, nullptr, 0);  // Añadimos 0 como distancia por defecto
        nuevaColumna->derecha = columnas;
        columnas = nuevaColumna;
        return nuevaColumna;
    }
    NodoMatriz* actual = columnas;
    while (actual->derecha != nullptr && actual->derecha->ciudadDestino <= ciudadDestino) {
        if (actual->ciudadDestino == ciudadDestino) {
            return actual;
        }
        actual = actual->derecha;
    }
    if (actual->ciudadDestino == ciudadDestino) {
        return actual;
    }
    NodoMatriz* nuevaColumna = new NodoMatriz("", ciudadDestino, nullptr, 0);  // Añadimos 0 como distancia por defecto
    nuevaColumna->derecha = actual->derecha;
    actual->derecha = nuevaColumna;
    return nuevaColumna;
}

void MatrizDispersa::insertar(const std::string& vuelo, const std::string& ciudadDestino, Piloto* piloto, int distancia) {
    NodoMatriz* fila = buscarOCrearFila(vuelo);
    NodoMatriz* columna = buscarOCrearColumna(ciudadDestino);
    NodoMatriz* nuevo = new NodoMatriz(vuelo, ciudadDestino, piloto, distancia);

    // Insertar en la fila
    if (fila->derecha == nullptr || fila->derecha->ciudadDestino > ciudadDestino) {
        nuevo->derecha = fila->derecha;
        fila->derecha = nuevo;
    } else {
        NodoMatriz* actual = fila->derecha;
        while (actual->derecha != nullptr && actual->derecha->ciudadDestino < ciudadDestino) {
            actual = actual->derecha;
        }
        nuevo->derecha = actual->derecha;
        actual->derecha = nuevo;
    }

    // Insertar en la columna
    if (columna->abajo == nullptr || columna->abajo->vuelo > vuelo) {
        nuevo->abajo = columna->abajo;
        columna->abajo = nuevo;
    } else {
        NodoMatriz* actual = columna->abajo;
        while (actual->abajo != nullptr && actual->abajo->vuelo < vuelo) {
            actual = actual->abajo;
        }
        nuevo->abajo = actual->abajo;
        actual->abajo = nuevo;
    }
}
void MatrizDispersa::eliminar(const std::string& vuelo, const std::string& ciudadDestino) {
    NodoMatriz* fila = filas;
    NodoMatriz* prevFila = nullptr;
    while (fila != nullptr && fila->vuelo != vuelo) {
        prevFila = fila;
        fila = fila->abajo;
    }
    if (fila == nullptr) return;
    NodoMatriz* actual = fila;
    NodoMatriz* prevActual = nullptr;
    while (actual != nullptr && actual->ciudadDestino != ciudadDestino) {
        prevActual = actual;
        actual = actual->derecha;
    }
    if (actual == nullptr) return;
    if (prevActual == nullptr) {
        fila->derecha = actual->derecha;
    } else {
        prevActual->derecha = actual->derecha;
    }
    NodoMatriz* columna = columnas;
    NodoMatriz* prevColumna = nullptr;
    while (columna != nullptr && columna->ciudadDestino != ciudadDestino) {
        prevColumna = columna;
        columna = columna->derecha;
    }
    if (columna != nullptr) {
        NodoMatriz* actualCol = columna;
        NodoMatriz* prevActualCol = nullptr;
        while (actualCol != nullptr && actualCol->vuelo != vuelo) {
            prevActualCol = actualCol;
            actualCol = actualCol->abajo;
        }
        if (actualCol != nullptr) {
            if (prevActualCol == nullptr) {
                columna->abajo = actualCol->abajo;
            } else {
                prevActualCol->abajo = actualCol->abajo;
            }
        }
    }
    delete actual;
    if (fila->derecha == nullptr) {
        if (prevFila == nullptr) {
            filas = fila->abajo;
        } else {
            prevFila->abajo = fila->abajo;
        }
        delete fila;
    }
    if (columna != nullptr && columna->abajo == nullptr) {
        if (prevColumna == nullptr) {
            columnas = columna->derecha;
        } else {
            prevColumna->derecha = columna->derecha;
        }
        delete columna;
    }
}

NodoMatriz* MatrizDispersa::obtener(const std::string& vuelo, const std::string& ciudadDestino) {
    NodoMatriz* fila = filas;
    while (fila != nullptr) {
        if (fila->vuelo == vuelo || fila->ciudadDestino == ciudadDestino) {
            NodoMatriz* actual = fila->derecha;
            while (actual != nullptr) {
                if (actual->vuelo == vuelo && actual->ciudadDestino == ciudadDestino) {
                    return actual;
                }
                actual = actual->derecha;
            }
        }
        fila = fila->abajo;
    }
    return nullptr;
}

void MatrizDispersa::imprimir() {
    NodoMatriz* fila = filas;
    while (fila != nullptr) {
        NodoMatriz* actual = fila->derecha;
        while (actual != nullptr) {
            std::cout << "Vuelo: " << actual->vuelo << ", Destino: " << actual->ciudadDestino;
            if (actual->piloto != nullptr) {
                std::cout << ", Piloto: " << actual->piloto->getNombre();
            }
            std::cout << ", Distancia: " << actual->distancia;
            std::cout << std::endl;
            actual = actual->derecha;
        }
        fila = fila->abajo;
    }
}

void MatrizDispersa::generarReporte(const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    archivo << "digraph MatrizDispersa {\n";
    archivo << "node [shape=record];\n";
    archivo << "raiz [label=\"Raíz\"];\n";

    // Generar nodos de columnas
    NodoMatriz* columnaActual = columnas;
    while (columnaActual != nullptr) {
        archivo << "col_" << columnaActual->ciudadDestino << " [label=\"" << columnaActual->ciudadDestino << "\"];\n";
        archivo << "raiz -> col_" << columnaActual->ciudadDestino << ";\n";
        if (columnaActual->derecha != nullptr) {
            archivo << "col_" << columnaActual->ciudadDestino << " -> col_" << columnaActual->derecha->ciudadDestino << ";\n";
        }
        columnaActual = columnaActual->derecha;
    }

    // Generar nodos de filas y elementos
    NodoMatriz* filaActual = filas;
    while (filaActual != nullptr) {
        archivo << "fila_" << filaActual->vuelo << " [label=\"" << filaActual->vuelo << "\"];\n";
        archivo << "raiz -> fila_" << filaActual->vuelo << ";\n";
        NodoMatriz* elementoActual = filaActual->derecha;
        while (elementoActual != nullptr) {
            std::string pilotoNombre = (elementoActual->piloto != nullptr) ? elementoActual->piloto->getNombre() : "N/A";
            archivo << "nodo_" << elementoActual->vuelo << "_" << elementoActual->ciudadDestino
                    << " [label=\"{Piloto: " << pilotoNombre << "|Distancia: " << elementoActual->distancia << "}\"];\n";
            archivo << "fila_" << elementoActual->vuelo << " -> nodo_" << elementoActual->vuelo
                    << "_" << elementoActual->ciudadDestino << ";\n";
            archivo << "col_" << elementoActual->ciudadDestino << " -> nodo_" << elementoActual->vuelo
                    << "_" << elementoActual->ciudadDestino << ";\n";
            elementoActual = elementoActual->derecha;
        }
        if (filaActual->abajo != nullptr) {
            archivo << "fila_" << filaActual->vuelo << " -> fila_" << filaActual->abajo->vuelo << ";\n";
        }
        filaActual = filaActual->abajo;
    }

    archivo << "}\n";
    archivo.close();
    std::string comando = "dot -Tpng " + nombreArchivo + " -o matrizVuelos.png";
    system(comando.c_str());
}

void MatrizDispersa::eliminarPiloto(const std::string& pilotoId) {
    NodoMatriz* fila = filas;
    while (fila != nullptr) {
        NodoMatriz* actual = fila->derecha;
        while (actual != nullptr) {
            if (actual->piloto != nullptr && actual->piloto->getNumeroDeId() == pilotoId) {
                actual->piloto = nullptr;  // Solo eliminamos la referencia al piloto, no el nodo completo
            }
            actual = actual->derecha;
        }
        fila = fila->abajo;
    }
}
