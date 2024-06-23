#include <iostream>
#include <string>
using namespace std;

class Nodo
{
private:
    /* data */
    int horas;
    string nombre;
    string nacionalidad;
    string numero_de_id;
    string vuelo;
    string tipo_de_licencia;
    Nodo* izq; //Hijo izquierdo
    Nodo* der; //Hijo derecho
public:
    Nodo();
    //getters y setters
    void setHoras(int horas);
    int getHoras();
    string getNombre();
    string getNacionalidad();
    string getNumero_de_id();
    string getVuelo();
    string getTipo();
    void setNombre(string nombre);
    void setNacionalidad(string nacionalidad);
    void setNumero_de_id(string numero_de_id);
    void setVuelo(string vuelo);
    void setTipo_de_licencia(string tipo_de_licencia);


    void setIzq(Nodo* izq);
    Nodo* getIzq();
    void setDer(Nodo* der);
    Nodo* getDer();
    ~Nodo();
};

Nodo::Nodo()
{
    this->izq = nullptr;
    this->der = nullptr;
}

void Nodo::setHoras(int horas)
{
    this->horas = horas;
}

void Nodo::setIzq(Nodo* izq)
{
    this->izq = izq;
}

void Nodo::setDer(Nodo* der)
{
    this->der = der;
}

int Nodo::getHoras()
{
    return this->horas;
}

Nodo* Nodo::getIzq()
{
    return this->izq;
}

Nodo* Nodo::getDer()
{
    return this->der;
}

string Nodo::getNombre()
{
    return this->nombre;
}

void Nodo::setNombre(string nombre)
{
    this->nombre = nombre;
}

string Nodo::getNacionalidad()
{
    return this->nacionalidad;
}

void Nodo::setNacionalidad(string nacionalidad)
{
    this->nacionalidad = nacionalidad;
}

string Nodo::getNumero_de_id()
{
    return this->numero_de_id;
}

void Nodo::setNumero_de_id(string numero_de_id)
{
    this->numero_de_id = numero_de_id;
}

string Nodo::getVuelo()
{
    return this->vuelo;
}

void Nodo::setVuelo(string vuelo)
{
    this->vuelo = vuelo;
}

string Nodo::getTipo()
{
    return this->tipo_de_licencia;
}

void Nodo::setTipo_de_licencia(string tipo_de_licencia)
{
    this->tipo_de_licencia = tipo_de_licencia;
}


Nodo::~Nodo()
{
}