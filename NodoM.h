#include <iostream>
#include <string>
using namespace std;

class Nodom
{
private:
    /* data */
    string dato;
    int fila, columna;
    Nodom* anterior;
    Nodom* siguiente;
    Nodom* arriba;
    Nodom* abajo;

public:
    Nodom(/* args */);
    Nodom(string dato, int fila, int columna);

    string getDato();
    void setDato(string dato);
    int getFila();
    void setFila(int fila);
    int getColumna();
    void setColumna(int columna);

    Nodom* getAnterior();
    void setAnterior(Nodom* anterior);
    Nodom* getSiguiente();
    void setSiguiente(Nodom* siguiente);
    Nodom* getArriba();
    void setArriba(Nodom* arriba);
    Nodom* getAbajo();
    void setAbajo(Nodom* abajo);
    ~Nodom();
};

Nodom::Nodom(/* args */)
{

}

Nodom::Nodom(string dato, int fila, int columna)
{
    this->dato = dato;
    this->fila = fila;
    this->columna = columna;
    anterior = siguiente = arriba = abajo = nullptr;
}

Nodom* Nodom::getAnterior()
{
    return anterior;
}

void Nodom::setAnterior(Nodom* anterior)
{
    this->anterior = anterior;
}


Nodom* Nodom::getSiguiente()
{
    return siguiente;
}

void Nodom::setSiguiente(Nodom* siguiente)
{
    this->siguiente = siguiente;
}



Nodom* Nodom::getArriba()
{
    return arriba;
}

void Nodom::setArriba(Nodom* arriba)
{
    this->arriba = arriba;
}


Nodom* Nodom::getAbajo()
{
    return abajo;
}

void Nodom::setAbajo(Nodom* abajo)
{
    this->abajo = abajo;
}

int Nodom::getFila(){
    return fila;
}

void Nodom::setFila(int fila)
{
    this->fila = fila;
}

int Nodom::getColumna()
{
    return columna;
}

void Nodom::setColumna(int columna)
{
    this->columna = columna;
}

string Nodom::getDato(){
    return dato;
}

void Nodom::setDato(string dato)
{
    this->dato = dato;
}

Nodom::~Nodom()
{
}