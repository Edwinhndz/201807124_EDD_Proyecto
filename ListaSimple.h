#include <iostream>
#include "NodoS.h"
#include <string>
using namespace std;

class ListaSimple
{
private:
    /* NECESITAMOS UNA REFERENCIA DEL PRIMER Y ÚLTIMO NodoS DE LA LISTA */
    NodoS *primero, *ultimo;
public:
    ListaSimple(/* args */);
    bool estaVacia();
    void insertarInicio(int dato, string id);
    void insertarFinal(int dato, string id);
    void eliminarInicio();
    void eliminarFinal();
    void visualizarLista();
    void EliminarId(string id);
    
    NodoS *getPrimero();
    NodoS *getUltimo();


    ~ListaSimple();
};

ListaSimple::ListaSimple(/* args */)
{
    primero = ultimo = nullptr;
}

bool ListaSimple::estaVacia()
{
    return (primero == nullptr) && (ultimo == nullptr);
}

NodoS *ListaSimple::getPrimero()
{
    return primero;
}

NodoS *ListaSimple::getUltimo()
{
    return ultimo;
}

void ListaSimple::insertarInicio(int dato, string id)
{
    NodoS *nuevo = new NodoS(dato, id); //Se crea el nuevo NodoS
    if (ListaSimple::estaVacia())
    {
        /* code */
        primero = ultimo = nuevo;
    }
    else
    {
        nuevo->setSiguiente(primero); //Se enlaza el nuevo NodoSS al primero
        primero = nuevo; //Se verifica que el NodoSS creado sea el primero
    }
    
}

void ListaSimple::insertarFinal(int dato,string id)
{
    NodoS *nuevo = new NodoS(dato, id); //Se crea el nuevo NodoS
    
    //nuevo->setNumero_de_id(id);
    if (ListaSimple::estaVacia())
    {
        /* code */
        primero = ultimo = nuevo;
    }
    else
    {
        ultimo->setSiguiente(nuevo); //Se enlaza el último NodoS al nuevo
        ultimo = nuevo; //Se verfica que el NodoS creado sea el último
    }
}

void ListaSimple::eliminarInicio()
{
    if (ListaSimple::estaVacia())
    {
        /* code */
        cout << "La lista está vacía" << endl;
    }
    else
    {
        if (primero == ultimo)
        {
            /* code */
            delete primero;
            primero = ultimo = nullptr;
        }
        else
        {
            NodoS *segundo = primero->getSiguiente();
            delete primero;
            primero = segundo;
        }   
    } 
}

void ListaSimple::eliminarFinal()
{
    if (ListaSimple::estaVacia())
    {
        cout << "La lista está vacía" << endl;
    }
    else{
        NodoS* temporal = primero;
        if (primero == ultimo)
        {
            /* code */
            delete primero;
            primero = ultimo = nullptr;
        }
        else{
            while (temporal != nullptr)
            {
                /* code */
                if (temporal->getSiguiente() == ultimo) //Si el siguiente de temporal es el último, entonces temporal es el antepenultimo
                {
                    /* code */
                    delete ultimo;
                    temporal->setSiguiente(nullptr);
                    ultimo = temporal;
                }
                temporal = temporal->getSiguiente(); //Recorriendo la lista
            }
            
        }
        
    }
    
}

void ListaSimple::visualizarLista()
{
    if (ListaSimple::estaVacia())
    {
        /* code */
        cout << "La lista está vacía" << endl;
    }
    else
    {
        int NodoSDato;
        NodoS *actual = primero;
        while (actual != nullptr)
        {
            /* code */
            NodoSDato = actual->getDato();
            //cout << NodoSDato << endl;
            cout << actual->getNumero_de_id() << (actual->getSiguiente() != nullptr ? " -> ": "\n");
            actual = actual->getSiguiente();
        }
        
    }
    
}

void ListaSimple::EliminarId(string id)
{
    if (ListaSimple::estaVacia())
    {
        cout << "La lista está vacía" << endl;
    }
    else
    {
        NodoS *temporal = primero;
        NodoS *anterior = nullptr;
        while (temporal != nullptr)
        {
            if (temporal->getNumero_de_id() == id)
            {
                if (temporal == primero)
                {
                    if(primero->getSiguiente() == nullptr)
                    {
                        primero = ultimo = nullptr;
                    }else{
                        primero = temporal->getSiguiente();
                    }
                }
                else if (temporal == ultimo)
                {
                    ultimo = anterior;
                    ultimo->setSiguiente(nullptr);
                }
                else
                {
                    anterior->setSiguiente(temporal->getSiguiente());
                }
                delete temporal;
                cout << "Nodo eliminado" << endl;
                return;
            }
            anterior = temporal;
            temporal = temporal->getSiguiente();
        }
        cout << "No se encontró un nodo con el Id especificado" << endl;
    }
}


ListaSimple::~ListaSimple()
{
}