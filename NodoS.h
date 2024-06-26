#include <iostream>
using namespace std;

class NodoS
{
private:
    /* data */
    int dato;
    string nombre;
    string nacionalidad;
    string numero_de_id;
    string vuelo;
    string tipo_de_licencia;
    int horas_de_vuelo;
    NodoS *anterior;
    NodoS *siguiente;
public:
    NodoS(int dato, string id);
    NodoS *getSiguiente();
    NodoS *getAnterior();
    void setSiguiente(NodoS *siguiente);
    void setAnterior(NodoS *anterior);
    int getDato();
    void setDato(int dato);

    //setters y getters
 
    void setNumero_de_id(string id);
    string getNumero_de_id();



    ~NodoS();
};

NodoS::NodoS(int dato, string id)
{
    this->dato = dato;
    this->numero_de_id = id;
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

void NodoS::setDato(int dato){
    this->dato = dato;
}

void NodoS::setNumero_de_id(string id){
    this->numero_de_id = id;
}

string NodoS::getNumero_de_id(){
    return this->numero_de_id;
}

NodoS::~NodoS()
{
}