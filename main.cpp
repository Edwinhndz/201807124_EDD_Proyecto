// g++ main.cpp -o main
// g++ -std=c++11 -o ejec main.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "json.hpp"
#include "ListaDobleC.h"

using namespace std;

using json = nlohmann::json;

void CargaPilotos(string pilotoss)
{

    // Abrir el archivo JSON

    ifstream archivo(pilotoss);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo de aviones." << endl;
        return;
    }

    // Leer el contenido del archivo JSON
    json pilotos;
    archivo >> pilotos;

    // Recorrer los pilotos y mostrar sus detalles
    int conteo = 1;
    for (const auto &piloto : pilotos)
    {
        cout << "-------------------------" << conteo << endl;
        cout << "Nombre: " << piloto["nombre"] << endl;
        string a = piloto["nombre"];
        cout << "Nacionalidad: " << piloto["nacionalidad"] << endl;
        string b = piloto["nacionalidad"];
        cout << "Numero de id: " << piloto["numero_de_id"] << endl;
        string c = piloto["numero_de_id"];
        cout << "Vuelo: " << piloto["vuelo"] << endl;
        string d = piloto["vuelo"];
        cout << "Horas de vuelo: " << piloto["horas_de_vuelo"] << endl;
        int e = piloto["horas_de_vuelo"];
        cout << "Tipo de licencia: " << piloto["tipo_de_licencia"] << endl;
        string g = piloto["tipo_de_licencia"];
        cout << "-------------------------" << conteo << endl;
        conteo++;
    }
};

void CargaAviones(string avionesss)

// void IngresoEquipaje();
{
    // Abrir el archivo JSON
    ifstream archivo(avionesss);

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo de aviones." << endl;
        return;
    }

    // Leer el contenido del archivo JSON
    json aviones;
    archivo >> aviones;

    // Recorrer los pilotos y mostrar sus detalles
    int conteo = 1;
    for (const auto &avion : aviones)
    {
        cout << "-------------------------" << conteo << endl;
        cout << "Vuelo: " << avion["vuelo"] << endl;
        string a = avion["vuelo"];
        cout << "numero de registro: " << avion["numero_de_registro"] << endl;
        string b = avion["numero_de_registro"];
        cout << "Modelo: " << avion["modelo"] << endl;
        string c = avion["modelo"];
        cout << "aerolinea: " << avion["aerolinea"] << endl;
        string h = avion["aerolinea"];
        cout << "ciudad destino: " << avion["ciudad_destino"] << endl;
        string d = avion["ciudad_destino"];
        cout << "Estado: " << avion["estado"] << endl;
        string i = avion["estado"];
        cout << "-------------------------" << conteo << endl;
        conteo++;
    }
};

int main()
{
    int choice;

    do
    {
        cout << "-----------------------------------------" << endl;
        cout << "Menu:" << endl;
        cout << "1. Carga de aviones" << endl;
        cout << "2. Carga de pilotos" << endl;
        cout << "3. Carga de rutas" << endl;
        cout << "4. Carga de movimientos" << endl;
        cout << "5. Consulta de horas de vuelo" << endl;
        cout << "6. Recomendar ruta" << endl;
        cout << "7. Visualizar reporte" << endl;
        cout << "8. Salir" << endl;
        cout << "Eliga una opcion:  (1-8): ";
        cin >> choice;
        cout << "-----------------------------------------" << endl;
        cout << endl;

        switch (choice)
        {
        case 1:
            // Code for option 1
            CargaAviones("aviones2.json");
            break;
        case 2:
            // Code for option 2
            CargaPilotos("pilotos2.json");
            break;
        case 3:
            // Code for option 3
            break;
        case 4:
            // Code for option 4
            break;
        case 5:
            // Code for option 5
            break;
        case 6:
            // Code for option 6
            break;
        case 7:
            // Code for option 7
            break;
        case 8:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 8);

    return 0;
}
