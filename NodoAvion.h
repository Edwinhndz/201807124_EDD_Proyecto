#include <iostream>
#include <string>
using namespace std;

class NodoA
{
private:
    /* data */
    int dato;
    string vuelo;
    string registro;
    string modelo;
    string destino;
    int anio;
    int capacidad;
    int pesoMax;
    string aerolinea;
    string estado;


    NodoA *anterior;
    NodoA *siguiente;

public:
    NodoA(int dato);
    NodoA *getSiguiente();
    NodoA *getAnterior();
    void setSiguiente(NodoA *siguiente);
    void setAnterior(NodoA *anterior);
    int getDato();
    void setDato(int dato);

    string getVuelo();
    void setVuelo(string vuelo);
    string getRegistro();
    void setRegistro(string registro);
    string getModelo();
    void setModelo(string modelo);
    string getDestino();
    void setDestino(string destino);
    int getAnio();
    void setAnio(int anio);
    int getCapacidad();
    void setCapacidad(int capacidad);
    int getPesoMax();
    void setPesoMax(int pesoMax);
    string getAerolinea();
    void setAerolinea(string linea);
    string getEstado();
    void setEstado(string estado);

    ~NodoA();
};

NodoA::NodoA(int dato)
{
    this->dato = dato;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

int NodoA::getDato(){
    return this->dato;
}

void NodoA::setDato(int dato){
    this->dato = dato;
}

string NodoA::getVuelo(){
    return this->vuelo;
}

void NodoA::setVuelo(string vuelo){
    this->vuelo = vuelo;
}

string NodoA::getRegistro(){
    return this->registro;
}

void NodoA::setRegistro(string registro){
    this->registro = registro;
}

string NodoA::getModelo(){
    return this->modelo;
}

void NodoA::setModelo(string modelo){
    this->modelo = modelo;
}

string NodoA::getDestino(){
    return this->destino;
}

void NodoA::setDestino(string destino){
    this->destino = destino;
}

int NodoA::getAnio(){
    return this->anio;
}

void NodoA::setAnio(int anio){
    this->anio = anio;
}

int NodoA::getCapacidad(){
    return this->capacidad;
}

void NodoA::setCapacidad(int capacidad){
    this->capacidad = capacidad;
}

int NodoA::getPesoMax(){
    return this->pesoMax;
}

void NodoA::setPesoMax(int pesoMax){
    this->pesoMax = pesoMax;
}

string NodoA::getAerolinea(){
    return this->aerolinea;
}

void NodoA::setAerolinea(string aerolinea){
    this->aerolinea = aerolinea;
}

string NodoA::getEstado(){
    return this->estado;
}

void NodoA::setEstado(string estado){
    this->estado = estado;
}


NodoA* NodoA::getSiguiente(){
    return this->siguiente;
}

NodoA* NodoA::getAnterior(){
    return this->anterior;
}

void NodoA::setSiguiente(NodoA *siguiente){
    this->siguiente = siguiente;
}

void NodoA::setAnterior(NodoA *anterior){
    this->anterior = anterior;
}




NodoA::~NodoA()
{
}