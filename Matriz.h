#include <iostream>
#include <fstream>
// #include <ofstream>
#include <string>
#include "NodoM.h"

using namespace std;

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
    void generarDot(string nombreArchivo);
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
#include <fstream>

void Matriz::generarDot(string nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        archivo << "digraph G {" << endl;
        archivo << "node [shape=record];" << endl;
        
        // Crear nodo root
        archivo << "-1[label=\"root\",group=1,shape=box];" << endl;

        // Imprimir cabeceras de fila
        Nodom* fila = root->getAbajo();
        while (fila != nullptr) {
            archivo << fila->getFila() << "[label=\"Fila " << fila->getFila() << "\",group=1,shape=box];" << endl;
            fila = fila->getAbajo();
        }

        // Imprimir cabeceras de columna
        Nodom* columna = root->getSiguiente();
        int group = 2;
        while (columna != nullptr) {
            archivo << "columna" << columna->getColumna() << "[label=\"Columna " << columna->getColumna() << "\",group=" << group << ",shape=box];" << endl;
            columna = columna->getSiguiente();
            group++;
        }

        // Conectar nodo root con cabeceras de fila y columna
        fila = root->getAbajo();
        archivo << "-1 -> ";
        while (fila != nullptr) {
            archivo << fila->getFila();
            fila = fila->getAbajo();
            if (fila != nullptr) {
                archivo << " -> ";
            }
        }
        archivo << ";" << endl;

        columna = root->getSiguiente();
        archivo << "-1 -> ";
        while (columna != nullptr) {
            archivo << "columna" << columna->getColumna();
            columna = columna->getSiguiente();
            if (columna != nullptr) {
                archivo << " -> ";
            }
        }
        archivo << ";" << endl;

        // Recorremos filas y creamos nodos de datos
        fila = root->getAbajo();
        while (fila != nullptr) {
            Nodom* nodo = fila->getSiguiente();
            while (nodo != nullptr) {
                archivo << "\"" << nodo->getFila() << "," << nodo->getColumna() << "\"[label=\"" << nodo->getDato() << "\",shape=box,group=" << (nodo->getColumna() + 1) << "];" << endl;
                nodo = nodo->getSiguiente();
            }
            fila = fila->getAbajo();
        }

        // Conectar cabeceras de fila con sus nodos
        fila = root->getAbajo();
        while (fila != nullptr) {
            archivo << fila->getFila() << " -> ";
            Nodom* nodo = fila->getSiguiente();
            while (nodo != nullptr) {
                archivo << "\"" << nodo->getFila() << "," << nodo->getColumna() << "\"";
                nodo = nodo->getSiguiente();
                if (nodo != nullptr) {
                    archivo << " -> ";
                }
            }
            archivo << ";" << endl;
            fila = fila->getAbajo();
        }

        // Conectar cabeceras de columna con sus nodos
        columna = root->getSiguiente();
        while (columna != nullptr) {
            archivo << "columna" << columna->getColumna() << " -> ";
            Nodom* nodo = columna->getAbajo();
            while (nodo != nullptr) {
                archivo << "\"" << nodo->getFila() << "," << nodo->getColumna() << "\"";
                nodo = nodo->getAbajo();
                if (nodo != nullptr) {
                    archivo << " -> ";
                }
            }
            archivo << ";" << endl;
            columna = columna->getSiguiente();
        }

        // Alinear nodos en el mismo nivel
        archivo << "{rank=same; -1";
        columna = root->getSiguiente();
        while (columna != nullptr) {
            archivo << " ; columna" << columna->getColumna();
            columna = columna->getSiguiente();
        }
        archivo << "; }" << endl;

        fila = root->getAbajo();
        while (fila != nullptr) {
            archivo << "{rank=same; " << fila->getFila();
            Nodom* nodo = fila->getSiguiente();
            while (nodo != nullptr) {
                archivo << " ; \"" << nodo->getFila() << "," << nodo->getColumna() << "\"";
                nodo = nodo->getSiguiente();
            }
            archivo << "; }" << endl;
            fila = fila->getAbajo();
        }

        archivo << "}" << endl;
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

Matriz::~Matriz()
{
}
