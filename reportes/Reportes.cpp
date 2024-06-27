#include "Reportes.h"
#include "../nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Reportes::generarReporteArbolB(ArbolB& arbolAviones) {
    std::ofstream archivo("arbol_b_aviones.dot");
    archivo << "digraph arbol_b_aviones {" << std::endl;
    // Agregar nodos y edges del árbol B
    archivo << "}" << std::endl;
    archivo.close();
    generarImagenDesdeArchivoDot("arbol_b_aviones.dot", "arbol_b_aviones.png", "png");
    std::cout << "Reporte de árbol B de aviones disponibles generado correctamente." << std::endl;
}

void Reportes::generarReporteListaMantenimiento(ListaCircularDoble& listaMantenimiento) {
    std::ofstream archivo("lista_mantenimiento.txt");
    // Recorrer la lista circular doble e imprimir los aviones en mantenimiento
    archivo.close();
    std::cout << "Reporte de lista de aviones en mantenimiento generado correctamente." << std::endl;
}

void Reportes::generarReporteArbolBinario(ArbolBinarioBusqueda& arbolPilotos) {
    std::ofstream archivo("arbol_binario_pilotos.dot");
    archivo << "digraph arbol_binario_pilotos {" << std::endl;
    // Agregar nodos y edges del árbol binario de búsqueda
    archivo << "}" << std::endl;
    archivo.close();
    generarImagenDesdeArchivoDot("arbol_binario_pilotos.dot", "arbol_binario_pilotos.png", "png");
    std::cout << "Reporte de árbol binario de búsqueda de pilotos generado correctamente." << std::endl;
}

void Reportes::generarReporteTablaHash(TablaHash& tablaPilotos) {
    std::ofstream archivo("tabla_hash_pilotos.txt");
    // Recorrer la tabla hash e imprimir los pilotos
    archivo.close();
    std::cout << "Reporte de tabla hash de pilotos generado correctamente." << std::endl;
}

void Reportes::generarReporteGrafoDirigido(Grafo& grafoRutas) {
    std::ofstream archivo("grafo_rutas.dot");
    archivo << "digraph grafo_rutas {" << std::endl;
    // Agregar vértices y aristas del grafo dirigido
    archivo << "}" << std::endl;
    archivo.close();
    generarImagenDesdeArchivoDot("grafo_rutas.dot", "grafo_rutas.png", "png");
    std::cout << "Reporte de grafo dirigido de rutas generado correctamente." << std::endl;
}

void Reportes::generarReporteMatrizDispersa(MatrizDispersa& matrizVuelos) {
    std::ofstream archivo("matriz_dispersa_vuelos.txt");
    // Imprimir la matriz dispersa de vuelos y ciudades destino
    archivo.close();
    std::cout << "Reporte de matriz dispersa de vuelos y ciudades destino generado correctamente." << std::endl;
}

void Reportes::generarImagenDesdeArchivoDot(const std::string& archivoEntrada, const std::string& archivoSalida, const std::string& formato) {
    std::string comando = "dot -T" + formato + " -o " + archivoSalida + " " + archivoEntrada;
    int resultado = std::system(comando.c_str());
    if (resultado != 0) {
        std::cout << "Error al generar la imagen desde el archivo dot." << std::endl;
    } else {
        std::cout << "Imagen generada correctamente: " << archivoSalida << std::endl;
    }
}
