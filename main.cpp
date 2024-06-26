// g++ main.cpp -o main
// g++ -std=c++11 -o ejec main.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include "json.hpp"
#include "ListaDobleC.h"
#include "ArbolBB.h"

using namespace std;

using json = nlohmann::json;

void CargaPilotos(string pilotoss, ArbolBB *arbol)
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

        arbol->insertar(e, a, b, c, d, g, nullptr);
    }
};

void Mantenimineto(string vuelo, string registro, string modelo, string aerolinea, string destino, string estado, ListaCircular *lista){
    lista->insertarFinal(0,vuelo, registro, modelo, aerolinea, destino, estado);
}

void CargaAviones(string avionesss, ListaCircular *lista)

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

        if(i == "Mantenimiento"){
            Mantenimineto(a, b, c, h, d, i, lista);
        }else if(i == "Disponible"){
            cout << "Disponible" << endl;
        }

        conteo++;
    }
};

void Disponibles(){

}



void CargaRutas(){
    ifstream archivo("city.txt");

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo de commandos." << endl;
        return;
    }

    string linea;

    int i = 1;
    while (getline(archivo, linea))
    {
        cout << "-------------------------" << i << endl;
        cout << linea << endl;
        cout << "-------------------------" << i << endl;
        i++;
         if(linea == ""){
            cout << "linea vacia:"<< linea <<";" << endl;
        }
        else if (linea != "")
        {
            stringstream split(linea);
            string ciudad1, ciudad2, km;
            cout << "-------------------------" << endl;
            getline(split, ciudad1, '/');
            cout << "Ciudad Origen: " << ciudad1 << "\n";
            getline(split, ciudad2, '/');
            cout << "Ciudad Destino: " << ciudad2 << "\n";
            getline(split, km, ',');
            km.pop_back();
            cout << "Kmts: |" << km << "|" << "\n";
        }

    }
}

int main()
{
    // estructuras
    ArbolBB *arbol = new ArbolBB();
    arbol->SetRaiz();
    ListaCircular *lista = new ListaCircular();

    int choice;
    int choiceRecorridos;
    system("color 0b");
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
            CargaAviones("aviones3.json", lista);
            break;
        case 2:
            // Code for option 2

            CargaPilotos("pilotos.json", arbol);
            break;
        case 3:
            // Code for option 3
            CargaRutas();
            break;
        case 4:
            // Code for option 4
            arbol->EliminarNodo("P369121518");
            break;
        case 5:
            // Code for option 5

            cout << "Recorridos:" << endl;
            cout << "1. PreOrden" << endl;
            cout << "2. InOrden" << endl;
            cout << "3. PostOrden" << endl;
            cout << "Eliga una opcion:  (1-3): ";
            cin >> choiceRecorridos;

            switch (choiceRecorridos)
            {
            case 1:
                cout << "Recorrido PreOrden" << endl;
                cout << endl;
                arbol->RecorridoPre();
                cout << endl;
                break;
            case 2:
                cout << "Recorrido InOrden" << endl;
                cout << endl;
                arbol->RecorridoIn();
                cout << endl;
                break;
            case 3:
                cout << "Recorrido PostOrden" << endl;
                cout << endl;
                arbol->RecorridoPost();
                cout << endl;
                /* code */
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
            break;

        case 6:
            // Code for option 6
            break;
        case 7:
            // Code for option 7
            cout << "Generando Reportes " << endl;
            arbol->generarReporte();
            lista->generarReporte2();
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
