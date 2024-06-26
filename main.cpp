#include <iostream>
#include "estructuras/ArbolB.h"
#include "estructuras/ArbolBinarioBusqueda.h"
#include "estructuras/TablaHash.h"
#include "estructuras/Grafo.h"
#include "estructuras/ListaCircularDoble.h"
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
void cargarAviones(const std::string& nombreArchivo, ArbolB& arbolAviones, ListaCircularDoble& listaMantenimiento) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de aviones abierto correctamente." << std::endl;

    json jsonData;
    archivo >> jsonData;

    for (const auto& avionJson : jsonData) {
        Avion avion(
                avionJson["vuelo"],
                avionJson["numero_de_registro"],
                avionJson["modelo"],
                avionJson["capacidad"],
                avionJson["aerolinea"],
                avionJson["ciudad_destino"],
                avionJson["estado"]
        );

        if (avion.getEstado() == "Disponible") {
            arbolAviones.insertar(avion);
        } else if (avion.getEstado() == "Mantenimiento") {
            listaMantenimiento.insertar(avion);
        }
    }
}

void cargarPilotos(const std::string& nombreArchivo, ArbolBinarioBusqueda& arbolPilotos, TablaHash& tablaPilotos) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de pilotos abierto correctamente." << std::endl;

    json jsonData;
    archivo >> jsonData;

    for (const auto& pilotoJson : jsonData) {
        Piloto piloto(
                pilotoJson["nombre"],
                pilotoJson["nacionalidad"],
                pilotoJson["numero_de_id"],
                pilotoJson["vuelo"],
                pilotoJson["horas_de_vuelo"],
                pilotoJson["tipo_de_licencia"]
        );

        arbolPilotos.insertar(piloto);
        tablaPilotos.insertar(piloto);
    }
}

void cargarRutas(const std::string& nombreArchivo, Grafo& grafoRutas) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de rutas abierto correctamente." << std::endl;

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string origen, destino, distanciaStr;

        std::getline(iss, origen, '/');
        std::getline(iss, destino, '/');
        std::getline(iss, distanciaStr, ';');

        int distancia = std::stoi(distanciaStr);

        Ruta ruta(origen, destino, distancia);
        grafoRutas.agregarRuta(ruta);
    }
}

void procesarMovimientos(const std::string& nombreArchivo, ArbolB& arbolAviones, ListaCircularDoble& listaMantenimiento) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de movimientos abierto correctamente." << std::endl;
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string comando, numeroRegistro, estado;
        iss >> comando >> numeroRegistro >> estado;
        if (comando == "MantenimientoAviones") {
            if (estado == "Disponible") {
                Avion* avion = listaMantenimiento.buscarYEliminar(numeroRegistro);
                if (avion) {
                    avion->setEstado("Disponible");
                    arbolAviones.insertar(*avion);
                    delete avion;
                }
            } else if (estado == "Mantenimiento") {
                Avion* avion = arbolAviones.buscarYEliminar(numeroRegistro);
                if (avion) {
                    avion->setEstado("Mantenimiento");
                    listaMantenimiento.insertar(*avion);
                    delete avion;
                }
            }
        }
    }
}
void generarImagenDesdeArchivoDot(const std::string& archivoEntrada, const std::string& archivoSalida, const std::string& formato) {
    std::string comando = "dot -T" + formato + " -o " + archivoSalida + " " + archivoEntrada;
    int resultado = std::system(comando.c_str());
    if (resultado != 0) {
        std::cout << "Error al generar la imagen desde el archivo dot." << std::endl;
    } else {
        std::cout << "Imagen generada correctamente: " << archivoSalida << std::endl;
    }
}
void generarReporteArbolB() {
    // Generar archivo .dot para árbol B con aviones disponibles
    std::ofstream archivo("arbol_b_aviones.dot");
    archivo << "digraph arbol_b_aviones {" << std::endl;
    // Agregar nodos y edges del árbol B
    archivo << "}" << std::endl;
    archivo.close();

    // Convertir archivo .dot a imagen
    system("dot -Tpng arbol_b_aviones.dot -o arbol_b_aviones.png");
    std::cout << "Reporte generado con éxito. Ver archivo arbol_b_aviones.png" << std::endl;
}

void mostrarMenu() {
    std::cout << "=== Sistema de Gestión de Aeropuerto ===" << std::endl;
    std::cout << "1. Cargar aviones" << std::endl;
    std::cout << "2. cargar  pilotos" << std::endl;
    std::cout << "3. cargar  rutas" << std::endl;
    std::cout << "4. cargar  movimientos" << std::endl;
    std::cout << "5. consultar horas de vuelo"<<std::endl;
    std::cout << "6. Recomendar ruta más corta" << std::endl;
    std::cout << "7. Generar reportes" << std::endl;
    std::cout << "8. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}
void mostrarMenuReportes() {
    int opcion;
    do {
        std::cout << "Menu de reportes" << std::endl;
        std::cout << "1. Árbol B con aviones disponibles" << std::endl;
        std::cout << "2. Lista de aviones en mantenimiento" << std::endl;
        std::cout << "3. Árbol binario de búsqueda con las horas de vuelo de cada piloto" << std::endl;
        std::cout << "4. Tabla hash de pilotos" << std::endl;
        std::cout << "5. Grafo dirigido con las rutas" << std::endl;
        std::cout << "6. Matriz dispersa de vuelos y ciudades" << std::endl;
        std::cout << "7. Regresar al menu principal" << std::endl;
        std::cout << "Ingrese una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                // Generar reporte de árbol B con aviones disponibles
                generarReporteArbolB();

                break;
            case 2:
                // Generar reporte de lista de aviones en mantenimiento
                //generarReporteListaMantenimiento();
                break;
            case 3:
                // Generar reporte de árbol binario de búsqueda con las horas de vuelo de cada piloto
                //generarReporteArbolBinario();
                break;
            case 4:
                // Generar reporte de tabla hash de pilotos
               // generarReporteTablaHash();
                break;
            case 5:
                // Generar reporte de grafo dirigido con las rutas
               // generarReporteGrafoDirigido();
                break;
            case 6:
                // Generar reporte de matriz dispersa de vuelos y ciudades
               // generarReporteMatrizDispersa();

                break;
            case 7:
                std::cout << "Regresando al menu principal..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 7);
}

int main() {
    ArbolB arbolAviones(5);
    ListaCircularDoble listaMantenimiento;
    ArbolBinarioBusqueda arbolPilotos;
    TablaHash tablaPilotos(18);
    Grafo grafoRutas;
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                cargarAviones("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/aviones.json", arbolAviones, listaMantenimiento);
                break;
            case 2:
                cargarPilotos("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/piloto.json", arbolPilotos, tablaPilotos);
                break;
            case 3:

                cargarRutas("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/rutas.txt", grafoRutas);
                break;
            case 4:
                procesarMovimientos("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/movimientos.txt", arbolAviones, listaMantenimiento);
                break;
            case 5:
                // Llamar a función para recomendar ruta más corta
                break;
            case 6:
                // Llamar a función para generar reportes
                break;
            case 7:
                // Llamar a función para generar reportes
                mostrarMenuReportes();
                break;
            case 8:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 8);
    return 0;
}

