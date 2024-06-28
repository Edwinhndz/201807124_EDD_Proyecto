#include <iostream>
using namespace std;

//REPRESENTA UN NODO EN EL GRAFO
class Vertice
{
private:
    /* data */
    string nombre; //nombre de vértice
    int numVertice; //número de vértice
    int distancia; //distancia desde el vértice origen
public:
    Vertice(/* args */);
    string getNombre(){
        return this->nombre;
    }
    void setNombre(string nombre){
        this->nombre = nombre;
    }
    bool esIgual(string nombre);
    Vertice(string nombre, int n, int distancia);

    ~Vertice();
};

Vertice::Vertice(/* args */)
{
}

Vertice::Vertice(string nombre, int n, int distancia)
{
    this->nombre = nombre;
    this->numVertice = n;
    this->distancia = distancia;
}


//Devuelve TRUE si dos vertices tienen el mismo nombre
bool Vertice::esIgual(string nombre)
{
    //Comparamos el nombre del vértice "actual" con el nombre del vértice que se quiere agregar
    return (this->nombre == nombre);
}


Vertice::~Vertice()
{
}