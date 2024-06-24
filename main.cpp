#include <iostream>
#include "estructuras/ArbolB.h"
#include "estructuras/ArbolBinarioBusqueda.h"
#include "estructuras/TablaHash.h"
#include "estructuras/MatrizDispersa.h"
#include "estructuras/Grafo.h"
#include "estructuras/ListaCircularDoble.h"
#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include <fstream>


using json = nlohmann::json;

void cargarAviones(const std::string& nombreArchivo, ArbolB& arbolAviones, ListaCircularDoble& listaMantenimiento) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    json jsonData;
    archivo >> jsonData;

    for (const auto& avionJson : jsonData["aviones"]) {
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

    json jsonData;
    archivo >> jsonData;

    for (const auto& pilotoJson : jsonData["pilotos"]) {
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

    std::string linea;
    while (std::getline(archivo, linea)) {
        Ruta ruta = Ruta::fromString(linea);
        grafoRutas.agregarRuta(ruta);
    }
}

void procesarMovimientos(const std::string& nombreArchivo, ArbolB& arbolAviones, ListaCircularDoble& listaMantenimiento) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string comando, numeroRegistro, estado;
        iss >> comando >> numeroRegistro >> estado;

        if (comando == "MantenimientoAviones") {
            if (estado == "Disponible") {
                // Mover de lista de mantenimiento al árbol B
                Avion* avion = listaMantenimiento.buscarYEliminar(numeroRegistro);
                if (avion) {
                    avion->setEstado("Disponible");
                    arbolAviones.insertar(*avion);
                    delete avion;
                }
            } else if (estado == "Mantenimiento") {
                // Mover del árbol B a la lista de mantenimiento
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
void mostrarMenu() {
    std::cout << "=== Sistema de Gestión de Aeropuerto ===" << std::endl;
    std::cout << "1. Cargar archivos de entrada" << std::endl;
    std::cout << "2. Gestionar aviones" << std::endl;
    std::cout << "3. Gestionar pilotos" << std::endl;
    std::cout << "4. Gestionar rutas" << std::endl;
    std::cout << "5. Recomendar ruta más corta" << std::endl;
    std::cout << "6. Generar reportes" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

int main() {
    ArbolB arbolAviones(5);  // Árbol B de orden 5
    ListaCircularDoble listaMantenimiento;
    ArbolBinarioBusqueda arbolPilotos;
    TablaHash tablaPilotos(18);  // Tamaño inicial 18
    Grafo grafoRutas;
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                // Llamar a función para cargar archivos

                break;
            case 2:
                // Llamar a función para gestionar aviones
                break;
            case 3:
                // Llamar a función para gestionar pilotos
                break;
            case 4:
                // Llamar a función para gestionar rutas
                break;
            case 5:
                // Llamar a función para recomendar ruta más corta
                break;
            case 6:
                // Llamar a función para generar reportes
                break;
            case 7:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 7);

    return 0;
}

