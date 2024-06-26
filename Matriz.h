#include <iostream>
#include <string.h>
using namespace std;
#include "Nodom.h"

class Matriz
{
private:
    /* data */
public:
    Nodom* root;
    Matriz(/* args */);
    Nodom* buscarFila(int fila, Nodom* inicio);
    Nodom* buscarColumna(int columna, Nodom* inicio);
    Nodom* crearFila(int fila);
    Nodom* crearColumna(int columna);
    void insertar(string dato, int fila, int columna);
    ~Matriz();
};

Matriz::Matriz(/* args */)
{
    root = new Nodom("Root",-1, -1); //-1 y -1 para encabezado root
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

Nodom* Matriz::crearFila(int fila)
{
    Nodom* f = new Nodom("Fila", fila, -1);
    Nodom* aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

Nodom* Matriz::crearColumna(int columna)
{
    Nodom* c = new Nodom("Columna", -1, columna);
    Nodom* aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::insertar(string dato, int fila, int columna)
{
    Nodom* nodoDato = new Nodom(dato, fila, columna);
    Nodom* nodoFila; //Para saber en que fila insertar
    Nodom* nodoColumna; //Para saber en que columna insertar

    nodoFila = buscarFila(fila, root);
    nodoColumna = buscarColumna(columna, root);

    //REVISAMOS SI EXISTEN LOS ENCABEZADOS
    /*if (nodoFila == nullptr)
    {
        nodoFila = crearFila(fila);
    }
    if (nodoColumna == nullptr)
    {
        nodoColumna = crearColumna(columna);
    }*/

   if (nodoFila == nullptr && nodoColumna == nullptr) //Caso 1
   {
        nodoFila = crearFila(fila);
        nodoColumna = crearColumna(columna);
   }
   else if (nodoFila != nullptr && nodoColumna == nullptr) //Caso 2
   {
        nodoColumna = crearColumna(columna);
   }
   else if (nodoFila == nullptr && nodoColumna != nullptr)
   {
        nodoFila = crearFila(fila);
   }


    //INSERTAR NODODATO EN LAS CABECERAS
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

   //Insertando nodoDato en la cabecera fila
   Nodom* auxFila = nodoFila;
   while (auxFila != nullptr)
   {
        if (auxFila->getSiguiente() == nullptr) //Encontre el último nodo (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxFila->setSiguiente(nodoDato);
            nodoDato->setAnterior(auxFila);
            break;
        }
        auxFila = auxFila->getSiguiente();
   }

   //Insertando nodoDato en la cabecera columna
   Nodom* auxColumna = nodoColumna;
   while (auxColumna != nullptr)
   {
        if (auxColumna->getAbajo() == nullptr) //Encontre el último nodo (puede ser la misma cabecera)
        {
            //Hacemos los enlaces correspondientes
            auxColumna->setAbajo(nodoDato);
            nodoDato->setArriba(auxColumna);
            break;
        }
        auxColumna = auxColumna->getAbajo();  
   }





}

Matriz::~Matriz()
{
}