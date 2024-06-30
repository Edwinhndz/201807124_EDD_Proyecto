#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
#include "NodoM.h"

class Matriz
{
private:
    /* data */
public:
    int i=1;
    int j=1;
    Nodom* root;
    
    Matriz(/* args */);
    int getI();
    int getJ();
    Nodom* getRoot();
    Nodom* buscarFila(int fila, Nodom* inicio);
    Nodom* buscarColumna(int columna, Nodom* inicio);
    void crearFila(string vuelo);
    void crearColumna(string cuidad);
    void generarDot();
    void insertar(string dato, int fila, int columna, string vuelo, string destino);
    ~Matriz();
};

Matriz::Matriz(/* args */)
{
    root = new Nodom("Root", 0, 0); //-1 y -1 para encabezado root
}

int Matriz::getI()
{
    return i;
}

int Matriz::getJ()
{
    return j;
}

void Matriz::crearFila(string vuelo)
{   
    Nodom *cc =new Nodom(vuelo, i, 0);
    Nodom *aux = this->root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
    }
    aux->setAbajo(cc);
    cc->setArriba(aux);
    i++;
}

void Matriz::crearColumna(string cuidad)
{
    Nodom* c = new Nodom(cuidad, 0, j);
    Nodom* aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    j++;
}

void Matriz::insertar(string dato, int fila, int columna, string vuelo, string destino)
{
    cout <<" y aca" << endl;
    Nodom* nodoDato = new Nodom(dato, fila, columna);
    Nodom* nodoFila; //Para saber en que fila insertar
    Nodom* nodoColumna; //Para saber en que columna insertar

    cout << "pre de buscar "<<endl;

    nodoFila = buscarFila(fila, root);
    nodoColumna = buscarColumna(columna, root);

    cout << "post de buscar "<<endl;
    if((nodoFila == nullptr) && (nodoColumna == nullptr))
    {
        cout << "No existe el vuelo ni el destino" << endl;
    }else if ((nodoFila == nullptr) && (nodoColumna != nullptr))
    {
        cout << "No existe el vuelo" << endl;
    }else if((nodoFila != nullptr) && (nodoColumna == nullptr))
    {
        cout << "No existe el destino" << endl;
    }else if((nodoFila != nullptr) && (nodoColumna != nullptr))
    {
        nodoFila->setSiguiente(nodoDato);
        nodoDato->setAnterior(nodoFila);
        nodoColumna->setAbajo(nodoDato);
        nodoDato->setArriba(nodoColumna);
    }
}


Nodom* Matriz::buscarFila(int fila, Nodom* inicio)
{
    Nodom* aux = inicio; //inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getFila() == fila)
        {
            return aux; //Si se encuentra la cabecera fila, la retorno
        }
        aux = aux->getAbajo();
    }
    return nullptr; //Si no la encuentra quiere decir que no existe la cabecera fila
}

Nodom* Matriz::buscarColumna(int columna, Nodom* inicio)
{
    Nodom* aux = inicio; //inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getColumna() == columna)
        {
            return aux; //Si se encuentra la cabecera columna, la retorno
        }
        aux = aux->getSiguiente();
    }
    return nullptr; //Si no la encuentra quiere decir que no existe la cabecera columna
}


void Matriz::generarDot()
{
    if(root == nullptr)
    {
        cout << "No hay datos en la matriz" << endl;
        return;
    }else
    {
        ofstream archivo;
        archivo.open("grafica_Matriz.dot", ios::out);
        archivo << "digraph G { " << endl;
        archivo << "node [shape=box];" << endl;

        archivo <<"/*--------------Cabezeras Horizontales--------------*/" << endl;
        Nodom* auxColumnas = root;

        archivo << "X0[label=\"Root\"];" << endl;
        //Recorriendo las cabezeras horizontales
        while (auxColumnas->getSiguiente() != nullptr)
        {
            auxColumnas = auxColumnas->getSiguiente();
            archivo << "J" << auxColumnas->getColumna() << "[label=\"" << auxColumnas->getDato() << "\"];" << endl;
        }
        //Recorriendo las cabezeras verticales
        Nodom* auxFilas = root;
        while (auxFilas->getAbajo() != nullptr)
        {
            auxFilas = auxFilas->getAbajo();
            archivo << "I" << auxFilas->getFila() << "[label=\"" << auxFilas->getDato() << "\"];" << endl;
        }

        archivo << endl <<"}" << endl << "}";
        archivo.close();
        system("dot -Tpng grafica_Matriz.dot -o grafica_Matriz.png");
        system("open grafica_Matriz.png");
    }


}


Nodom* Matriz::getRoot()
{
    return root;
}

Matriz::~Matriz()
{
}