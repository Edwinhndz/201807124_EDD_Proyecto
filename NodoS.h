#include <iostream>
using namespace std;

class NodoS
{
private:
    /* data */
    int dato;
    NodoS *anterior;
    NodoS *siguiente;
public:
    NodoS(int dato);
    NodoS *getSiguiente();
    NodoS *getAnterior();
    void setSiguiente(NodoS *siguiente);
    void setAnterior(NodoS *anterior);
    int getDato();
    void setDato(int dato);
    ~NodoS();
};

NodoS::NodoS(int dato)
{
    this->dato = dato;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

NodoS* NodoS::getSiguiente(){
    return this->siguiente;
}

NodoS* NodoS::getAnterior(){
    return this->anterior;
}

void NodoS::setSiguiente(NodoS *siguiente){
    this->siguiente = siguiente;
}

void NodoS::setAnterior(NodoS *anterior){
    this->anterior = anterior;
}

int NodoS::getDato(){
    return this->dato;
}


NodoS::~NodoS()
{
}