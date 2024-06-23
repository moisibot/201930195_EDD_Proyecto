#include "Reportes.h"
#include <iostream>

void Reportes::generarReporteArbolB(const ArbolB* arbol) {
    std::ofstream dotFile("arbol_b.dot");
    dotFile << "digraph ArbolB {" << std::endl;
    dotFile << "  node [shape=record];" << std::endl;
    arbol->generarReporte(dotFile);
    dotFile << "}" << std::endl;
    dotFile.close();
    ejecutarGraphviz("arbol_b");
}

void Reportes::generarReporteListaCircularDoble(const ListaCircularDoble* lista) {
    std::ofstream dotFile("lista_circular_doble.dot");
    dotFile << "digraph ListaCircularDoble {" << std::endl;
    dotFile << "  node [shape=record];" << std::endl;
    dotFile << "  rankdir=LR;" << std::endl;
    lista->generarReporte(dotFile);
    dotFile << "}" << std::endl;
    dotFile.close();
    ejecutarGraphviz("lista_circular_doble");
}

void Reportes::generarReporteArbolBinario(const ArbolBinarioBusqueda* arbol) {
    std::ofstream dotFile("arbol_binario.dot");
    dotFile << "digraph ArbolBinario {" << std::endl;
    dotFile << "  node [shape=record];" << std::endl;
    arbol->generarReporte(dotFile);
    dotFile << "}" << std::endl;
    dotFile.close();
    ejecutarGraphviz("arbol_binario");
}

void Reportes::generarReporteTablaHash(const TablaHash* tabla) {
    std::ofstream dotFile("tabla_hash.dot");
    dotFile << "digraph TablaHash {" << std::endl;
    dotFile << "  node [shape=record];" << std::endl;
    dotFile << "  rankdir=LR;" << std::endl;
    tabla->generarReporte(dotFile);
    dotFile << "}" << std::endl;
    dotFile.close();
    ejecutarGraphviz("tabla_hash");
}

void Reportes::generarReporteGrafo(const Grafo* grafo) {
    std::ofstream dotFile("grafo_rutas.dot");
    dotFile << "digraph GrafoRutas {" << std::endl;
    grafo->generarReporte(dotFile);
    dotFile << "}" << std::endl;
    dotFile.close();
    ejecutarGraphviz("grafo_rutas");
}

void Reportes::generarReporteMatrizDispersa(const MatrizDispersa* matriz) {
    std::ofstream dotFile("matriz_dispersa.dot");
    dotFile << "digraph MatrizDispersa {" << std::endl;
    dotFile << "  node [shape=record];" << std::endl;
    dotFile << "  rankdir=LR;" << std::endl;
    matriz->generarReporte(dotFile);
    dotFile << "}" << std::endl;
    dotFile.close();
    ejecutarGraphviz("matriz_dispersa");
}

void Reportes::ejecutarGraphviz(const std::string& nombreArchivo) {
    std::string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
    system(comando.c_str());
}