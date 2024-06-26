#include <iostream>
using namespace std;
#include "ListaSimple.h"

class TablaHash
{
private:
    /* data */
    int tamTabla;
    int numElementos;
    ListaSimple *tabla;
public:
    TablaHash(/* args */);
    int Clave(int valor);
    void Insertar(int valor);
    void imprimirTabla();
    ~TablaHash();
};

TablaHash::TablaHash(/* args */)
{
    tamTabla = 18;
    tabla = new ListaSimple[18];
    for (int i = 0; i < tamTabla; i++)
    {
        //cout << tabla->estaVacia() << endl;
    }
    numElementos = 0;    
}

int TablaHash::Clave(int valor)
{
    int i;
    i = (int)(valor % tamTabla);
    //cout << "Llave asignada: " << i << endl;
    return i;
}

void TablaHash::Insertar(int valor)
{
    int indice = Clave(valor);
    tabla[indice].insertarFinal(valor);
}

void TablaHash::imprimirTabla()
{
    for (int i = 0; i < tamTabla; i++)
    {
        cout << "[" << i << "] -> ";
        tabla[i].visualizarLista();
    }
    
}

TablaHash::~TablaHash()
{
}