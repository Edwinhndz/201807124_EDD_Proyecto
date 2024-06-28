#include <iostream>
#include "ListaSimple.h"
using namespace std;

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
    void Insertar(int valor, string id);
    void imprimirTabla();
    void EliminarId(string id, int valor);
    void GenerateDot();
    ~TablaHash();
};

TablaHash::TablaHash(/* args */)
{
    tamTabla = 18;
    tabla = new ListaSimple[18];
    for (int i = 0; i < tamTabla; i++)
    {
        // cout << tabla->estaVacia() << endl;
    }
    numElementos = 0;
}

int TablaHash::Clave(int valor)
{
    int i;
    i = (int)(valor % tamTabla);
    // cout << "Llave asignada: " << i << endl;
    return i;
}

void TablaHash::Insertar(int valor, string id)
{
    int indice = Clave(valor);
    tabla[indice].insertarFinal(valor, id);
}

void TablaHash::imprimirTabla()
{
    for (int i = 0; i < tamTabla; i++)
    {
        cout << "[" << i << "] -> ";
        tabla[i].visualizarLista();
    }
}

void TablaHash::EliminarId(string id, int valor)
{
    int indice = Clave(valor);
    for (int i = 0; i < tamTabla; i++)
    {
        tabla[i].EliminarId(id);
    }
}

void TablaHash::GenerateDot()
{
    ofstream archivo("TablaHash.dot");
    if (archivo.is_open())
    {
        archivo << "digraph G {" << endl;
        archivo << "rankdir=LR;" << endl;
        archivo << "\n node [shape=box];" << endl;
        // creacion de nodos indices
        for (int i = 0; i < tamTabla; i++)
        {
            archivo << "node" << i << "[label=\"";
            archivo << "" << i << "\" shape=box];" << endl;
        }
        archivo <<"{rank =same; node0 node1 node2 node3 node4 node5 node6 node7 node8 node9 node10 node11 node12 node13 node14 node15 node16 node17}";
        
        // conexcion de los indices 0->17
        for (int i = 0; i < tamTabla; i++)
        {

            
            if (i + 1 < tamTabla)
            {
                archivo << "node" << i << " -> ";
                archivo << "node" << i + 1 << ";" << endl;
            }
        }

        archivo << endl;

        for (int i = 0; i < tamTabla; i++)
        {

            if (!tabla[i].estaVacia())
            {
                NodoS *actual = tabla[i].getPrimero();
                string idAnterior = "";

                while (actual != nullptr)
                {
                    archivo << actual->getNumero_de_id() <<" [label=\""<< actual->getNumero_de_id() << "\" , shape=box];" << endl;
                    
                    actual = actual->getSiguiente();
                }
            }
        }

        // conexiones de nodos de la listas
        for (int i = 0; i < tamTabla; i++)
        {
            if (!tabla[i].estaVacia())
            {
                NodoS *actual = tabla[i].getPrimero();
                string idAnterior = "";
                int conteo = 0;
                archivo << "node" << i << " -> ";

                while (actual != nullptr)
                {
                    archivo << actual->getNumero_de_id();
                    
                    if(actual->getSiguiente() != nullptr){
                        archivo << " -> ";
                        idAnterior = actual->getNumero_de_id();
                    }

                    actual = actual->getSiguiente();
                    conteo++;
                }
                archivo << ";" << endl;
            }
        }

        archivo << "}" << endl;
        archivo.close();
    }
    system("dot -Tpng TablaHash.dot -o TablaHash.png");
    system("open TablaHash.png");
}

TablaHash::~TablaHash()
{
}