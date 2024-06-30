#include <iostream>
#include <string.h>
#include <fstream>
#include "NodoM.h"
#include <sstream>
using namespace std;

class Matriz
{
private:
    /* data */
public:
    Nodom *root;
    int filas = 1;
    int columnas = 1;
    Matriz(/* args */);
    Nodom *buscarFila(int fila, Nodom *inicio);
    Nodom *buscarColumna(int columna, Nodom *inicio);
    Nodom *crearFila(int fila, string ciudad);
    Nodom *crearColumna(int columna, string vuelo);
    void imprmir();
    void CabecerasF(string vuelo);
    void CabecerasC(string ciudad, string vuelo);
    void insertar(string dato, int fila, int columna, string vuelo, string ciudad);
    string regresarciudad(string);
    void agregarPiloto(string piloto, string vuelo);
    Nodom *regresarFila(string vuelo);
    Nodom *regresarColumna(string ciudad);
    Nodom *buscarPiloto(string piloto);
    void generarReporte();
    void eliminarPiloto(string piloto);
    string indiceCiudad(int columna);
    string indiceVuelo(int fila);
    void imprimirColumnas();
    void imprimirFilas();
    bool buscarPiloto2(int i, int j);
    ~Matriz();
};

Matriz::Matriz(/* args */)
{
    root = new Nodom("Root", 0, 0, "", ""); //-1 y -1 para encabezado root
}

Nodom *Matriz::buscarFila(int fila, Nodom *inicio)
{
    Nodom *aux = inicio; // inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getFila() == fila)
        {
            return aux; // Si se encuentra la cabecera fila, la retorno
        }
        aux = aux->getAbajo();
    }
    return nullptr; // Si no la encuentra quiere decir que no existe la cabecera fila
}

Nodom *Matriz::buscarColumna(int columna, Nodom *inicio)
{
    Nodom *aux = inicio; // inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getColumna() == columna)
        {
            return aux; // Si se encuentra la cabecera columna, la retorno
        }
        aux = aux->getSiguiente();
    }
    return nullptr; // Si no la encuentra quiere decir que no existe la cabecera columna
}

Nodom *Matriz::crearFila(int fila, string vuelo)
{
    Nodom *f = new Nodom("Fila", fila, -1, vuelo, " ");
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

Nodom *Matriz::crearColumna(int columna, string ciudad)
{
    Nodom *c = new Nodom("Columna", 0, columna, " ", ciudad);
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::CabecerasF(string vuelo)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        if (vuelo == aux->getVuelo())
        {
            // cout << "Ya existe el vuelo" << endl;
            return;
        }
    }
    Nodom *nuevo = new Nodom("Fila", filas, 0, vuelo, " ");
    aux->setAbajo(nuevo);
    nuevo->setArriba(aux);
    filas++;
}

void Matriz::CabecerasC(string ciudad, string vuelo)
{
    Nodom *aux = root;
    bool bandera = false;

    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        // cout << "comparando " << ciudad << " con " << aux->getCiudad() << endl;
        if (ciudad == aux->getCiudad())
        {
            // cout << "Ya existe la ciudad" << endl;
            bandera = true;
        }
    }

    if (bandera)
    {
        string vuelos = aux->getVuelo() + "," + vuelo;
        aux->setVuelo(vuelos);
        return;
    }
    else
    {

        Nodom *nuevo = new Nodom("Columna", 0, columnas, vuelo, ciudad);
        aux->setSiguiente(nuevo);
        nuevo->setAnterior(aux);
        // cout << "Guardando: " << aux->getSiguiente()->getCiudad() << endl;
        columnas++;
    }
}

Nodom *Matriz::regresarFila(string vuelo)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        if (vuelo == aux->getVuelo())
        {
            return aux;
        }
    }
    return nullptr;
}

Nodom *Matriz::regresarColumna(string ciudad)
{
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        if (ciudad == aux->getCiudad())
        {
            return aux;
        }
    }
    return nullptr;
}

void Matriz::insertar(string dato, int fila, int columna, string vuelo, string ciudad)
{
    Nodom *nodoDato = new Nodom(dato, fila, columna, vuelo, ciudad);
    Nodom *nodoFila;    // Para saber en que fila insertar
    Nodom *nodoColumna; // Para saber en que columna insertar

    nodoFila = buscarFila(fila, root);
    nodoColumna = buscarColumna(columna, root);

    // REVISAMOS SI EXISTEN LOS ENCABEZADOS
    /*if (nodoFila == nullptr)
    {
        nodoFila = crearFila(fila);
    }
    if (nodoColumna == nullptr)
    {
        nodoColumna = crearColumna(columna);
    }*/

    if (nodoFila == nullptr && nodoColumna == nullptr) // Caso 1
    {
        nodoFila = crearFila(fila, vuelo);
        nodoColumna = crearColumna(columna, ciudad);
    }
    else if (nodoFila != nullptr && nodoColumna == nullptr) // Caso 2
    {
        nodoColumna = crearColumna(columna, ciudad);
    }
    else if (nodoFila == nullptr && nodoColumna != nullptr)
    {
        nodoFila = crearFila(fila, vuelo);
    }

    // INSERTAR NODODATO EN LAS CABECERAS
    /*if (nodoFila->getSiguiente() == nullptr)
    {
        nodoFila->setSiguiente(nodoDato);
        nodoDato->setAnterior(nodoFila);
    }

    if (nodoColumna->getAbajo() == nullptr)
    {
        nodoColumna->setAbajo(nodoDato);
        nodoDato->setArriba(nodoColumna);
    }*/

    // Insertando nodoDato en la cabecera fila
    Nodom *auxFila = nodoFila;
    while (auxFila != nullptr)
    {
        if (auxFila->getSiguiente() == nullptr) // Encontre el último nodo (puede ser la misma cabecera)
        {
            // Hacemos los enlaces correspondientes
            auxFila->setSiguiente(nodoDato);
            nodoDato->setAnterior(auxFila);
            break;
        }
        auxFila = auxFila->getSiguiente();
    }

    // Insertando nodoDato en la cabecera columna
    Nodom *auxColumna = nodoColumna;
    while (auxColumna != nullptr)
    {
        if (auxColumna->getAbajo() == nullptr) // Encontre el último nodo (puede ser la misma cabecera)
        {
            // Hacemos los enlaces correspondientes
            auxColumna->setAbajo(nodoDato);
            nodoDato->setArriba(auxColumna);
            break;
        }
        auxColumna = auxColumna->getAbajo();
    }
}

string Matriz::regresarciudad(string vuelo)
{
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();

        string lectura;
        stringstream ss(aux->getVuelo());
        while (getline(ss, lectura, ','))
        {
            if (vuelo == lectura)
            {
                return aux->getCiudad();
            }
        }
    }
    return "";
}

void Matriz::agregarPiloto(string piloto, string vuelo)
{
    Nodom *ifila = regresarFila(vuelo);
    string ciudad = regresarciudad(vuelo);
    Nodom *jcolumna = regresarColumna(ciudad);
    if (ciudad == "")
    {
        cout << "No existe la ciudad, no se puede hacer enlace del piloto sin destino" << endl;
        return;
    }
    else
    {
        Nodom *nuevo = new Nodom(piloto, ifila->getFila(), jcolumna->getColumna(), vuelo, ciudad);

        // validar si la fila no tiene un elemento conectado ya
        if (ifila->getSiguiente() == nullptr)
        {
            ifila->setSiguiente(nuevo);
            nuevo->setAnterior(ifila);
        }
        else
        {
            Nodom *aux = ifila;
            while (aux->getSiguiente() != nullptr)
            {
                aux = aux->getSiguiente();
            }
            aux->setSiguiente(nuevo);
            nuevo->setAnterior(aux);
        }

        // validar si la columna no tiene un elemento conectado ya
        if (jcolumna->getAbajo() == nullptr)
        {
            jcolumna->setAbajo(nuevo);
            nuevo->setArriba(jcolumna);
        }
        else
        {
            Nodom *aux = jcolumna;
            while (aux->getAbajo() != nullptr)
            {
                aux = aux->getAbajo();
            }
            aux->setAbajo(nuevo);
            nuevo->setArriba(aux);
        }
    }
}

Nodom *Matriz::buscarPiloto(string piloto)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        while (aux->getSiguiente() != nullptr)
        {
            aux = aux->getSiguiente();
            if (aux->getDato() == piloto)
            {
                return aux;
            }
        }
    }
    return nullptr;
}

bool Matriz::buscarPiloto2(int i, int j)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        while (aux->getSiguiente() != nullptr)
        {
            aux = aux->getSiguiente();
            if (aux->getFila() == i && aux->getColumna() == j)
            {
                return true;
            }
        }
    }
    return false;
}

void Matriz::eliminarPiloto(string piloto)
{
    Nodom *aux = buscarPiloto(piloto);

    if (aux == nullptr)
    {
        cout << "No se encontro el piloto" << endl;
        return;
    }
    else
    {
        Nodom *ifila = regresarFila(aux->getVuelo());
        Nodom *jcolumna = regresarColumna(aux->getCiudad());
    }
}

string Matriz::indiceCiudad(int columna)
{
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        if (aux->getColumna() == columna)
        {
            return aux->getCiudad();
        }
    }
    return "";
}

string Matriz::indiceVuelo(int fila)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        if (aux->getFila() == fila)
        {
            return aux->getVuelo();
        }
    }
    return "";
}

void Matriz::generarReporte()
{
    ofstream archivo("MatrizD.dot");
    if (archivo.is_open())
    {
        archivo << "digraph G {" << endl;
        archivo << "bgcolor=skyblue;" << endl;
        archivo << "fontcolor=white;" << endl;
        archivo << "label= \"Matriz Dispersa\";" << endl;
        archivo << "labelloc=\"t\"" << endl;
        archivo << "nodesep=0.5" << endl;
        archivo << "node [shape=box width=1.2 style=filled fillcolor=\"#313638\" fontcolor=white color=transparent]" << endl;
        archivo << " edge [fontcolor=white color=\"#ff5400\"];" << endl;
        archivo << "/*------------Cabeceras Horizontales------------*/" << endl;
        archivo << "node0 [label=\"Root\" group=1];" << endl;

        // columnas
        int conteoNod = 1;
        for (int i = 1; i < columnas; i++)
        {

            archivo << "node" << conteoNod << "[label=\"" << indiceCiudad(i) << "\" group=" << i + 1 << "];" << endl;
            conteoNod++;
        }

        // filas
        archivo << "/*------------Cabeceras Verticales------------*/" << endl;
        for (int i = 1; i < filas; i++)
        {
            if ((i + 1) == filas)
            {
                archivo << "node" << conteoNod << "[label=\"" << indiceVuelo(i) << "\" group=1" << "];" << endl;
                conteoNod++;
            }
            else
            {
                archivo << "node" << conteoNod << "[label=\"" << indiceVuelo(i) << "\" group=1" << "];" << endl;
                conteoNod++;
            }
        }

        // nodos de la matriz
        Nodom *aux = root;
        aux = aux->getSiguiente();

        for (int i = 1; i < columnas; i++)
        {
            archivo << "/*------------columna " << i << "------------*/" << endl;

            Nodom *aux2 = aux;
            // vemos que la columna no este vacia hacia abajo
            while (aux2->getAbajo() != nullptr)
            {
                // recorremos la columna para abajo
                aux2 = aux2->getAbajo();
                archivo << "nodo" << aux2->getFila() << aux2->getColumna() << "[label=\"" << aux2->getDato() << " " << aux2->getFila() << "," << aux2->getColumna() << "\" group=" << i + 1 << "];" << endl;
                conteoNod++;
            }

            aux = aux->getSiguiente();
        }

        archivo << "/*------------Relaciones Horizontales------------*/" << endl;
        // cabeceras columnas

        // conexiones izq -> der
        string conexion;
        for (int i = 1; i < columnas; i++)
        {
            if (i == 1)
            {
                conexion += "node0 -> node1 ";
            }
            else
            {
                conexion += " node" + to_string(i - 1) + " -> node" + to_string(i) + " ";
            }
        }
        archivo << conexion << ";" << endl;

        // conexiones der -> izq
        conexion = "";

        for (int i = columnas - 1; i > 0; i--)
        {
            if (i == columnas - 1)
            {
            }
            else
            {
                conexion += "node" + to_string(i + 1) + " -> node" + to_string(i) + " ";
            }
        }
        conexion += " -> node0;";
        archivo << conexion << endl;

        // conexion de nodos de la matriz horizontal
        for (int i = 1; i < filas ; i++)
        {
            for (int j = 1; j < columnas ; j++)
            {

                cout <<"buscando piloto en: "<< i <<","<< j << " Hay: " << buscarPiloto2(i,j)<< endl;
                if (buscarPiloto2(i, j))
                {
                    // cout << "piloto encontrado en: "<< i <<","<< j << endl;
                    archivo << "nodo" << i << j << " -> node" << (i + (columnas - 1)) << ";" << endl;
                    archivo << "node" << (i + (columnas - 1)) << " -> nodo" << i << j << ";" << endl;
                }
                else
                {
                    // cout << "piloto no encontrado en: "<< i <<","<< j << endl;
                }
            }
        }

        // cabeceras filas

        // conexiones arriba -> abajo

        archivo << "/*------------Relaciones Verticales------------*/" << endl;
        conexion = "";

        for (int i = columnas; i < ((filas - 1) + (columnas - 1)); i++)
        {
            if (i == columnas)
            {
                conexion += "node0 -> node" + to_string(i) + " ";
            }
            else
            {
                conexion += " node" + to_string(i - 1) + " -> node" + to_string(i) + " ";
            }
        }
        conexion += " -> node" + to_string((filas - 1) + (columnas - 1));
        archivo << conexion << ";" << endl;
        // conexiones abajo -> arriba

        conexion = "";
        int nodosss = ((filas - 1) + (columnas - 1));
        for (int i = nodosss; i > columnas - 1; i--)
        {
            if (i == ((filas - 1) + (columnas - 1)))
            {
            }
            else
            {
                conexion += "node" + to_string(i + 1) + " -> node" + to_string(i) + " ";
            }
        }
        conexion += " -> node0;";
        archivo << conexion << endl;
        conexion = "";
        archivo << "/*------------Encuadre-----------*/" << endl;
        conexion += "{ rank=same; node0; ";
        for (int i = 1; i < columnas; i++)
        {
            conexion += "node" + to_string(i) + "; ";
        }
        archivo << conexion << "};" << endl;
    }
}

void Matriz::imprimirColumnas()
{
    Nodom *aux = root;

    do
    {
        cout << aux->getCiudad() << aux->getFila() << aux->getColumna() << " ";
        aux = aux->getSiguiente();
    } while (aux->getSiguiente() != nullptr);
    cout << aux->getCiudad() << aux->getFila() << aux->getColumna() << " ";
    cout << endl;
}

void Matriz::imprimirFilas()
{
    Nodom *aux = root;

    do
    {
        cout << aux->getVuelo() << aux->getFila() << aux->getColumna() << " ";
        aux = aux->getAbajo();
    } while (aux->getAbajo() != nullptr);
    cout << aux->getVuelo() << aux->getFila() << aux->getColumna() << " ";
    cout << endl;
}

Matriz::~Matriz()
{
}