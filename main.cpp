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

using json = nlohmann::json;

void cargarAviones(ArbolB& arbolAviones, ListaCircularDoble& listaMantenimiento) {
    std::ifstream file("aviones.json");
    json j;
    file >> j;

    for (const auto& avion : j) {
        Avion nuevoAvion(
                avion["vuelo"],
                avion["numero_de_registro"],
                avion["modelo"],
                avion["capacidad"],
                avion["aerolinea"],
                avion["ciudad_destino"],
                avion["estado"]
        );

        if (avion["estado"] == "Disponible") {
            arbolAviones.insertar(nuevoAvion);
        } else if (avion["estado"] == "Mantenimiento") {
            listaMantenimiento.insertar(nuevoAvion);
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

