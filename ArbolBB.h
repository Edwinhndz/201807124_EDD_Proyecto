#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "Nodo.h"

class ArbolBB
{
private:
    /* data */
    Nodo *raiz;
    ofstream archivo;
    int nodoDato;

public:
    int recorrido = 0;
    ArbolBB(/* args */);
    bool estaVacio();
    void insertar(int horas, string name, string nacion, string id, string vuelo, string licencia);
    Nodo *insertarNodo(Nodo *nodoPtr, int horas, string name, string nacion, string id, string vuelo, string licencia);
    void buscar(int dato);
    int buscarNodo(int dato, Nodo *nodoPtr);

    void RecorridoPre();
    void RecorridoPre(Nodo *nodoPtr);
    void RecorridoIn();
    void RecorridoIn(Nodo *nodoPtr);
    void RecorridoPost();
    void RecorridoPost(Nodo *nodoPtr);


    void generarReporte();
    void imprimirNodo(Nodo *nodoPtr);
    void imprimirNodoId(Nodo *nodoPtr);

    void SetRaiz();
    Nodo *GetRaiz();
    ~ArbolBB();
};

ArbolBB::ArbolBB(/* args */)
{
    raiz = nullptr;
}

bool ArbolBB::estaVacio()
{
    return (raiz == nullptr);
}

void ArbolBB::insertar(int horas, string name, string nacion, string id, string vuelo, string licencia)
{
    cout << "Horas en insertar: " << horas << "\n";
    raiz = insertarNodo(raiz, horas, name, nacion, id, vuelo, licencia);
}

Nodo *ArbolBB::insertarNodo(Nodo *nodoPtr, int horas, string name, string nacion, string id, string vuelo, string licencia)
{

    if (nodoPtr == nullptr)
    {

        Nodo *nuevo = new Nodo();
        nodoPtr = nuevo;
        nuevo->setHoras(horas);
        nuevo->setNombre(name);
        nuevo->setNacionalidad(nacion);
        nuevo->setNumero_de_id(id);
        nuevo->setVuelo(vuelo);
        nuevo->setTipo_de_licencia(licencia);

        cout << "insertando raiz con: " << horas << "\n";
    }
    else if (horas < nodoPtr->getHoras())
    {
        nodoPtr->setIzq(insertarNodo(nodoPtr->getIzq(), horas, name, nacion, id, vuelo, licencia));
        cout << "insertando izq con: " << horas << "\n";
    }
    else if (horas > nodoPtr->getHoras())
    {
        nodoPtr->setDer(insertarNodo(nodoPtr->getDer(), horas, name, nacion, id, vuelo, licencia));
        cout << "insertando der con: " << horas << "\n";
    }
    else if (horas == nodoPtr->getHoras())
    {
        nodoPtr->setDer(insertarNodo(nodoPtr->getDer(), horas, name, nacion, id, vuelo, licencia));
        cout << "insertando der igual raiz con: " << horas << "\n";
    }
    else
    {
        cout << "ninguno de los casos";
    }
    return nodoPtr;
}

void ArbolBB::buscar(int dato)
{
    cout << "Recorrido del nodo encontrado: " << buscarNodo(dato, raiz) << ", " << recorrido;
}

int ArbolBB::buscarNodo(int dato, Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        cout << "Nodo no encontrado\n";
        return 0;
    }
    else if (dato == nodoPtr->getHoras())
    {
        recorrido++;
        return nodoPtr->getHoras();
    }
    else if (dato < nodoPtr->getHoras())
    {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getIzq());
    }
    else if (dato > nodoPtr->getHoras())
    {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getDer());
    }
}

void ArbolBB::RecorridoPre()
{
    RecorridoPre(raiz);
}

void ArbolBB::RecorridoPre(Nodo *nodoPtr)
{
    if (nodoPtr != nullptr)
    {
        // PREORDEN
        cout << "Nombre: " << nodoPtr->getNombre() << ", Horas de vuelo: " << nodoPtr->getHoras() << endl;
        RecorridoPre(nodoPtr->getIzq());
        RecorridoPre(nodoPtr->getDer());

    }
}

void ArbolBB::RecorridoIn()
{
    RecorridoIn(raiz);
}

void ArbolBB::RecorridoIn(Nodo *nodoPtr)
{

    if(nodoPtr == nullptr){
        return;
    }else{
        // INORDEN
        RecorridoIn(nodoPtr->getIzq());
        cout << "Nombre: " << nodoPtr->getNombre() << ", Horas de vuelo: " << nodoPtr->getHoras() << endl;
        RecorridoIn(nodoPtr->getDer()); 
    }
}

void ArbolBB::RecorridoPost()
{
    RecorridoPost(raiz);
}

void ArbolBB::RecorridoPost(Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        return;
    }
    else
    {
        // POSTORDEN
        RecorridoPost(nodoPtr->getIzq());
        RecorridoPost(nodoPtr->getDer());
        cout << "Nombre: " << nodoPtr->getNombre() << ", Horas de vuelo: " << nodoPtr->getHoras() << endl;
    }
}

void ArbolBB::generarReporte()
{
    if (ArbolBB::estaVacio())
    {
    }
    else
    {
        archivo.open("grafica_arbol.dot", ios::out);
        archivo << "digraph G { " << endl;

        imprimirNodo(raiz);

        archivo << " }";
        archivo.close();
        system("dot -Tpng grafica_arbol.dot -o grafica_arbol.png");
        system("open grafica_arbol.png");
    }
}

void ArbolBB::imprimirNodo(Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        return;
    }

    if (nodoPtr->getIzq() != nullptr)
    {
        string id;
        string label = "";

        id = nodoPtr->getNumero_de_id();
        nodoDato = nodoPtr->getHoras();
        label = id + "[label =\"" + to_string(nodoPtr->getHoras()) + "\"];\n";
        archivo << label;
        archivo << id;

        archivo << "->";
        nodoDato = nodoPtr->getIzq()->getHoras();

        id = nodoPtr->getIzq()->getNumero_de_id();
        label = id + "[label =\"" + to_string(nodoPtr->getIzq()->getHoras()) + "\"];\n";
        archivo << id;
        archivo << ";\n";
        archivo << label;
    }
    imprimirNodo(nodoPtr->getIzq());

    if (nodoPtr->getDer() != nullptr)
    {

        string id;
        string label = "";

        nodoDato = nodoPtr->getHoras();
        id = nodoPtr->getNumero_de_id();
        label = id + "[label =\"" + to_string(nodoPtr->getHoras()) + "\"];\n";
        archivo << label;

        archivo << id;
        archivo << "->";
        nodoDato = nodoPtr->getDer()->getHoras();
        id = nodoPtr->getDer()->getNumero_de_id();
        label = id + "[label =\"" + to_string(nodoPtr->getDer()->getHoras()) + "\"];\n";
        archivo << id;
        archivo << ";\n";
        archivo << label;
    }
    imprimirNodo(nodoPtr->getDer());
}

void ArbolBB::imprimirNodoId(Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        return;
    }

    if (nodoPtr->getIzq() != nullptr)
    {
        nodoDato = nodoPtr->getHoras();
        archivo << nodoDato;
        archivo << "->";
        nodoDato = nodoPtr->getIzq()->getHoras();
        archivo << nodoDato;
        archivo << ";\n";
    }
    imprimirNodo(nodoPtr->getIzq());

    if (nodoPtr->getDer() != nullptr)
    {
        nodoDato = nodoPtr->getHoras();
        archivo << nodoDato;
        archivo << "->";
        nodoDato = nodoPtr->getDer()->getHoras();
        archivo << nodoDato;
        archivo << ";\n";
    }
    imprimirNodo(nodoPtr->getDer());
}

void ArbolBB::SetRaiz()
{
    this->raiz = nullptr;
}

Nodo *ArbolBB::GetRaiz()
{
    return this->raiz;
}

ArbolBB::~ArbolBB()
{
}