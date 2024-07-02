#include <iostream>
#include <string.h>
#include <fstream>
#include "NodoM.h"
#include <sstream>
using namespace std;

class Matriz
{
private:
    /* data */
public:
    Nodom *root;
    int filas = 1;
    int columnas = 1;
    Matriz(/* args */);
    Nodom *buscarFila(int fila, Nodom *inicio);
    Nodom *buscarColumna(int columna, Nodom *inicio);
    Nodom *crearFila(int fila, string ciudad, string piloto);
    Nodom *crearColumna(int columna, string vuelo);
    void imprmir();
    void CabecerasF(string vuelo, string piloto);
    void CabecerasC(string ciudad, string vuelo);
    void insertar(string dato, int fila, int columna, string vuelo, string ciudad);
    string regresarciudad(string);
    void agregarPiloto(string piloto, string vuelo);
    Nodom *regresarFila(string vuelo);
    Nodom *regresarColumna(string ciudad);
    Nodom *buscarPiloto(string piloto);
    void generarReporte();
    void eliminarPiloto(string piloto);
    string indiceCiudad(int columna);
    string indiceVuelo(int fila);
    void imprimirColumnas();
    void imprimirFilas();
    bool buscarPiloto2(int i, int j);
    void EliminarPiloto(string piloto);

    Nodom *regresarCE(string vuelo);
    Nodom *regresarFE(string piloto);
    int cacheCiudad(string vuelo);
    Nodom *Eliminado(string vuelo);
    void ActualizarColumnas();
    void ActualizarFilas();
    int RecorridoFilas();
    int RecorridoColumnas();

    ~Matriz();
};

Matriz::Matriz(/* args */)
{
    root = new Nodom("Root", 0, 0, "", ""); //-1 y -1 para encabezado root
}

Nodom *Matriz::buscarFila(int fila, Nodom *inicio)
{
    Nodom *aux = inicio; // inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getFila() == fila)
        {
            return aux; // Si se encuentra la cabecera fila, la retorno
        }
        aux = aux->getAbajo();
    }
    return nullptr; // Si no la encuentra quiere decir que no existe la cabecera fila
}

Nodom *Matriz::buscarColumna(int columna, Nodom *inicio)
{
    Nodom *aux = inicio; // inicio puede ser el root
    while (aux != nullptr)
    {
        if (aux->getColumna() == columna)
        {
            return aux; // Si se encuentra la cabecera columna, la retorno
        }
        aux = aux->getSiguiente();
    }
    return nullptr; // Si no la encuentra quiere decir que no existe la cabecera columna
}

Nodom *Matriz::crearFila(int fila, string vuelo, string piloto)
{
    Nodom *f = new Nodom(piloto, fila, -1, vuelo, " ");
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
    }
    aux->setAbajo(f);
    f->setArriba(aux);
    return f;
}

Nodom *Matriz::crearColumna(int columna, string ciudad)
{
    Nodom *c = new Nodom("Columna", 0, columna, " ", ciudad);
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
    }
    aux->setSiguiente(c);
    c->setAnterior(aux);
    return c;
}

void Matriz::CabecerasF(string vuelo, string piloto)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        if (vuelo == aux->getVuelo())
        {
            // cout << "Ya existe el vuelo" << endl;
            return;
        }
    }
    Nodom *nuevo = new Nodom(piloto, filas, 0, vuelo, " ");
    aux->setAbajo(nuevo);
    nuevo->setArriba(aux);
    filas++;
}

void Matriz::CabecerasC(string ciudad, string vuelo)
{
    Nodom *aux = root;
    bool bandera = false;

    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        // cout << "comparando " << ciudad << " con " << aux->getCiudad() << endl;
        if (ciudad == aux->getCiudad())
        {
            // cout << "Ya existe la ciudad" << endl;
            bandera = true;
        }
    }

    if (bandera)
    {
        string vuelos = aux->getVuelo() + "," + vuelo;
        aux->setVuelo(vuelos);
        return;
    }
    else
    {

        Nodom *nuevo = new Nodom("Columna", 0, columnas, vuelo, ciudad);
        aux->setSiguiente(nuevo);
        nuevo->setAnterior(aux);
        // cout << "Guardando: " << aux->getSiguiente()->getCiudad() << endl;
        columnas++;
    }
}

Nodom *Matriz::regresarFila(string vuelo)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        if (vuelo == aux->getVuelo())
        {
            return aux;
        }
    }
    return nullptr;
}

Nodom *Matriz::regresarColumna(string ciudad)
{
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        if (ciudad == aux->getCiudad())
        {
            return aux;
        }
    }
    return nullptr;
}

Nodom *Matriz::regresarFE(string piloto)
{
    Nodom *aux = root;
    Nodom *aux2 = aux;

    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        aux2 = aux;
        while (aux2->getSiguiente() != nullptr)
        {
            aux2 = aux2->getSiguiente();
            if (aux2->getDato() == piloto)
            {
                return aux2;
            }
        }
    }
    return nullptr;
}

string Matriz::regresarciudad(string vuelo)
{
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();

        string lectura;
        stringstream ss(aux->getVuelo());
        while (getline(ss, lectura, ','))
        {
            if (vuelo == lectura)
            {
                return aux->getCiudad();
            }
        }
    }
    return "";
}

void Matriz::agregarPiloto(string piloto, string vuelo)
{
    Nodom *ifila = regresarFila(vuelo);
    string ciudad = regresarciudad(vuelo);
    Nodom *jcolumna = regresarColumna(ciudad);
    if (ciudad == "")
    {
        cout << "No existe la ciudad, no se puede hacer enlace del piloto sin destino" << endl;
        return;
    }
    else
    {
        Nodom *nuevo = new Nodom(piloto, ifila->getFila(), jcolumna->getColumna(), vuelo, ciudad);

        // validar si la fila no tiene un elemento conectado ya
        if (ifila->getSiguiente() == nullptr)
        {
            ifila->setSiguiente(nuevo);
            nuevo->setAnterior(ifila);
        }
        else
        {
            Nodom *aux = ifila;
            while (aux->getSiguiente() != nullptr)
            {
                aux = aux->getSiguiente();
            }
            aux->setSiguiente(nuevo);
            nuevo->setAnterior(aux);
        }

        // validar si la columna no tiene un elemento conectado ya
        if (jcolumna->getAbajo() == nullptr)
        {
            jcolumna->setAbajo(nuevo);
            nuevo->setArriba(jcolumna);
        }
        else
        {
            Nodom *aux = jcolumna;
            while (aux->getAbajo() != nullptr)
            {
                aux = aux->getAbajo();
            }
            aux->setAbajo(nuevo);
            nuevo->setArriba(aux);
        }
    }
}

Nodom *Matriz::regresarCE(string vuelo)
{
    Nodom *aux = root;
    //cout << "buscando: " << vuelo << endl;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        //cout << "ciudad: ";
        //cout << aux->getCiudad() << " vuelos : " << aux->getVuelo() << endl;
        size_t found = aux->getVuelo().find(',');
        if (found == 4)
        {
            
            cout << "varias ciudades;" << endl;
            string lectura;
            stringstream ss(aux->getVuelo());
            while (getline(ss, lectura, ','))
            {
                if (vuelo == lectura)
                {
                    return aux;
                }
            }

            
        }else{
            if(vuelo == aux->getVuelo()){
                cout << "solo un vuelo va a la ciudad " << aux->getCiudad() << endl;
                return aux;
            }
        }
    }
    return nullptr; // si no encontro la ciudad 
}

int Matriz::cacheCiudad(string vuelo)
{
   Nodom *aux = root;
    //cout << "buscando: " << vuelo << endl;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        //cout << "ciudad: ";
        //cout << aux->getCiudad() << " vuelos : " << aux->getVuelo() << endl;
        size_t found = aux->getVuelo().find(',');
        if (found == 4)
        {
            
            cout << "varias ciudades;" << endl;
            string lectura;
            stringstream ss(aux->getVuelo());
            while (getline(ss, lectura, ','))
            {
                if (vuelo == lectura)
                {
                    return 1;
                }
            }

            
        }else{
            if(vuelo == aux->getVuelo()){
                //cout << "solo un vuelo va a la ciudad " << aux->getCiudad() << endl;
                return 0;
            }
        }
    }
    return -1; // si no encontro la ciudad 
}

Nodom *Matriz::Eliminado(string vuelo){
    Nodom *aux = root;
    //cout << "buscando: " << vuelo << endl;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        Nodom *aux2 = aux;
        while (aux2->getAbajo() != nullptr)
        {
            aux2 = aux2->getAbajo();
            if (vuelo == aux2->getVuelo())
            {
                return aux2;
            }
        } 

    }
    return nullptr; // si no encontro la ciudad 
}

void Matriz::EliminarPiloto(string piloto)
{
    Nodom *ifila = root;

    while(ifila->getAbajo() != nullptr){
        ifila = ifila->getAbajo();
        if(ifila->getDato() == piloto){
            cout << "Fila encontrado" << endl;
            break;
        }
    }

    Nodom *jcolumna = regresarCE(ifila->getVuelo());


    Nodom *eliminar = Eliminado(ifila->getVuelo());
    int varios = cacheCiudad(ifila->getVuelo());


    cout << "--------------------------------" << endl;
    cout << "PROBANDO ACSESO A CABECERAS" << endl;
    cout << "Fila: " << ifila->getVuelo() << endl;
    cout << "Columna: " << jcolumna->getCiudad() << endl;
    cout << "piloto: " << eliminar->getDato() << endl;
    cout << "cache: " << varios << endl;
    cout << "--------------------------------" << endl;
    


    if (ifila == nullptr)
    {
        cout << "No se encontro el piloto" << endl;
        return;
    }
    else
    {
        if (varios == 0)
        {
            
            //punteros evianto iFila que es la fila que se va

            if(jcolumna->getSiguiente() == nullptr && ifila->getAbajo()==nullptr)
            {
                cout << "ambas orillas"<< endl;
                //apuntar a null
                Nodom *tempF = ifila->getArriba();
                Nodom *tempC = jcolumna->getAnterior();

                tempF->setAbajo(nullptr);
                tempC->setSiguiente(nullptr);
                

                
            }else if (jcolumna->getSiguiente() == nullptr && ifila->getAbajo() !=nullptr)
            {
               cout << "columna orilla" << endl;
                Nodom *tempF = ifila->getArriba();
                Nodom *tempC = jcolumna->getAnterior();

                Nodom *puntF = ifila->getAbajo();
                tempF->setAbajo(puntF);
                puntF->setArriba(tempF);
                tempC->setSiguiente(nullptr);
              
                
              
            }else if (jcolumna->getSiguiente() != nullptr && ifila->getAbajo() == nullptr)
            {   
                cout << "fila orilla" << endl;
                Nodom *tempF = ifila->getArriba();
                Nodom *tempC = jcolumna->getAnterior();

                Nodom *puntC = jcolumna->getSiguiente();

                tempC->setSiguiente(puntC);
                puntC->setAnterior(tempC);

                tempF->setAbajo(nullptr);

                delete ifila;
                delete jcolumna;
              

            }else if (jcolumna->getSiguiente() != nullptr && ifila->getAbajo() != nullptr){
                cout << "ninguna orilla" << endl;
                Nodom *tempF = ifila->getArriba();
                Nodom *tempC = jcolumna->getAnterior();

                Nodom *puntF = ifila->getAbajo();
                Nodom *puntC = jcolumna->getSiguiente();

                tempF->setAbajo(puntF);
                puntF->setArriba(tempF);

                tempC->setSiguiente(puntC);
                puntC->setAnterior(tempC);

                delete jcolumna;
                delete ifila;

            }

            
         }else if(varios == 1)
         {
           
            Nodom *Recorrer = jcolumna;
            string lectura;
            int veces = 0;
            stringstream ss(jcolumna->getVuelo());
            cout << "ifila piloto: " << ifila->getDato()<< " vuelo: " << ifila->getVuelo() << endl;

            while(getline(ss,lectura,',')){//para encontrar el piloto en la columna
                Recorrer = Recorrer->getAbajo();
                //cout << "piloto: " << Recorrer->getDato()  << "vuelo: " << Recorrer->getVuelo()<< " Buscando a:" << eliminar->getVuelo() << " lectura: "<< lectura<< endl;
                if(Recorrer->getVuelo() == eliminar->getVuelo()){
                    break;
                }
            }
            
            // Nodom *AX =jcolumna;
            // while(AX->getAbajo() != nullptr){
            //     AX = AX->getAbajo();
            //     if(AX->getVuelo() == eliminar->getVuelo()){
            //         cout<< "AQUI ES"<< endl;
            //         break;
            //     }
            // }
           

            if(Recorrer->getAbajo() != nullptr)
            {
                cout << "Caso 1 varios" << endl; 

                Nodom *PilotoAntes = Recorrer->getArriba();
                Nodom *PilotoDespues = Recorrer->getAbajo();

                PilotoAntes->setAbajo(PilotoDespues);
                PilotoDespues->setArriba(PilotoAntes);
                if(ifila->getAbajo() == nullptr)
                {
                    cout << "fila orilla varios a misma ciudad" << endl;
                    Nodom *tempF = ifila->getArriba();
                    tempF->setAbajo(nullptr);

                    delete ifila;
                    delete Recorrer;
                }else if(ifila->getAbajo() != nullptr)
                {
                    cout << "ninguna orilla varios a misma ciudad" << endl;
                    Nodom *tempF = ifila->getArriba();
                    Nodom *puntF = ifila->getAbajo();

                    tempF->setAbajo(puntF);
                    puntF->setArriba(tempF);
                    delete ifila;
                    delete Recorrer;
                }

            }else if (Recorrer->getAbajo() == nullptr)
            {
                cout << "Caso 2 varios" << endl;
                cout << "piloto: " << Recorrer->getDato() << endl;

                Nodom *pilotoArriba = Recorrer->getArriba();
                
                pilotoArriba->setAbajo(nullptr);

                if(ifila->getAbajo()==nullptr)
                {   
                    cout << "fila orilla varios a misma ciudad" << endl;
                    Nodom *tempF = ifila->getArriba();

                    tempF->setAbajo(nullptr);
                    delete ifila;

                }else if(ifila->getAbajo() != nullptr)
                {

                    cout << "ninguna orilla varios a misma ciudad" << endl;
                    Nodom *tempF = ifila->getArriba();
                    Nodom *puntF = ifila->getAbajo();

                    tempF->setAbajo(puntF);
                    puntF->setArriba(tempF);
                    delete ifila;
                    delete Recorrer;
                }
                
            }

        }

    }
}

void Matriz::ActualizarColumnas()
{
    Nodom *aux = root;
    int conteo =1;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        aux->setColumna(conteo);
        conteo++;
    }
}

void Matriz::ActualizarFilas()
{
    Nodom *aux = root;
    int conteo =1;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        aux->setFila(conteo);
        conteo++;
    }
}

int Matriz::RecorridoFilas(){
    Nodom *aux = root;
    int conteo =1;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        aux->setFila(conteo);
        conteo++;
    }
    return conteo;
}

int Matriz::RecorridoColumnas(){
    Nodom *aux = root;
    int conteo = 1;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        aux->setColumna(conteo);
        conteo++;
    }
    return conteo;
}

Nodom *Matriz::buscarPiloto(string piloto)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        while (aux->getSiguiente() != nullptr)
        {
            aux = aux->getSiguiente();
            if (aux->getDato() == piloto)
            {
                return aux;
            }
        }
    }
    return nullptr;
}

bool Matriz::buscarPiloto2(int i, int j)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        while (aux->getSiguiente() != nullptr)
        {
            aux = aux->getSiguiente();
            if (aux->getFila() == i && aux->getColumna() == j)
            {
                return true;
            }
        }
    }
    return false;
}

void Matriz::eliminarPiloto(string piloto)
{
    Nodom *aux = buscarPiloto(piloto);

    if (aux == nullptr)
    {
        cout << "No se encontro el piloto" << endl;
        return;
    }
    else
    {
        Nodom *ifila = regresarFila(aux->getVuelo());
        Nodom *jcolumna = regresarColumna(aux->getCiudad());
    }
}

string Matriz::indiceCiudad(int columna)
{
    Nodom *aux = root;
    while (aux->getSiguiente() != nullptr)
    {
        aux = aux->getSiguiente();
        if (aux->getColumna() == columna)
        {
            return aux->getCiudad();
        }
    }
    return "";
}

string Matriz::indiceVuelo(int fila)
{
    Nodom *aux = root;
    while (aux->getAbajo() != nullptr)
    {
        aux = aux->getAbajo();
        if (aux->getFila() == fila)
        {
            return aux->getVuelo();
        }
    }
    return "";
}

void Matriz::generarReporte()
{
    ofstream archivo("MatrizD.dot");
    if (archivo.is_open())
    {
        
        cout << "numero de filas: " << filas << " " << to_string(RecorridoFilas()) << endl;
        cout << "numero de columnas: " << columnas << " " << to_string(RecorridoColumnas()) << endl;
        this->columnas = RecorridoColumnas();
        this->filas = RecorridoFilas();
        archivo << "digraph G {" << endl;
        archivo << "bgcolor=skyblue;" << endl;
        archivo << "fontcolor=white;" << endl;
        archivo << "label= \"Matriz Dispersa\";" << endl;
        archivo << "labelloc=\"t\"" << endl;
        archivo << "nodesep=0.5" << endl;
        archivo << "node [shape=box width=1.2 style=filled fillcolor=\"#313638\" fontcolor=white color=transparent]" << endl;
        archivo << " edge [fontcolor=white color=\"#ff5400\"];" << endl;
        archivo << "/*------------Cabeceras Horizontales------------*/" << endl;
        archivo << "node0 [label=\"Root\" group=1];" << endl;

        // columnas
        int conteoNod = 1;
        for (int i = 1; i < columnas; i++)
        {

            archivo << "node" << conteoNod << "[label=\"" << indiceCiudad(i) << "\" group=" << i + 1 << "];" << endl;
            conteoNod++;
        }

        // filas
        archivo << "/*------------Cabeceras Verticales------------*/" << endl;

        for (int i = 1; i < filas; i++)
        {
            if ((i + 1) == filas)
            {
                archivo << "node" << conteoNod << "[label=\"" << indiceVuelo(i) << "\" group=1" << "];" << endl;
                conteoNod++;
            }
            else
            {
                archivo << "node" << conteoNod << "[label=\"" << indiceVuelo(i) << "\" group=1" << "];" << endl;
                conteoNod++;
            }
        }

        // nodos de la matriz
        Nodom *aux = root;
        aux = aux->getSiguiente();

        for (int i = 1; i < columnas; i++)
        {
            archivo << "/*------------columna " << i << "------------*/" << endl;

            Nodom *aux2 = aux;
            // vemos que la columna no este vacia hacia abajo
            while (aux2->getAbajo() != nullptr)
            {
                // recorremos la columna para abajo
                aux2 = aux2->getAbajo();
                archivo << "nodo" << aux2->getFila() << aux2->getColumna() << "[label=\"" << aux2->getDato() << "\" group=" << i + 1 << "];" << endl;
                conteoNod++;
            }

            aux = aux->getSiguiente();
        }

        archivo << "/*------------Relaciones Horizontales------------*/" << endl;
        // cabeceras columnas

        // conexiones izq -> der
        string conexion;
        for (int i = 1; i < columnas; i++)
        {
            if (i == 1)
            {
                conexion += "node0 -> node1 ";
            }
            else
            {
                conexion += " node" + to_string(i - 1) + " -> node" + to_string(i) + " ";
            }
        }
        archivo << conexion << ";" << endl;

        // conexiones der -> izq
        conexion = "";

        for (int i = columnas - 1; i > 0; i--)
        {
            if (i == columnas - 1)
            {
            }
            else
            {
                conexion += "node" + to_string(i + 1) + " -> node" + to_string(i) + " ";
            }
        }
        conexion += " -> node0;";
        archivo << conexion << endl;

        // INTENTO SIN ALGORITMOS

        Nodom *aux3 = root;
        aux3 = aux3->getSiguiente();
        int cache = 0;
        string temp = "";

        for (int i = 1; i < columnas; i++)
        {
            archivo << "/*------------columna enlace:" << i << "------------*/" << endl;

            Nodom *aux2 = aux3;
            // vemos que la columna no este vacia hacia abajo
            while (aux2->getAbajo() != nullptr)
            {
                if (cache != 0)
                {
                    aux2 = aux2->getAbajo();
                    archivo << "nodo" << aux2->getFila() << aux2->getColumna() << " -> " << temp << endl;
                    archivo << temp << " -> nodo" << aux2->getFila() << aux2->getColumna() << endl;
                    temp = "nodo" + to_string(aux2->getFila()) + to_string(aux2->getColumna());
                }
                else if (cache == 0)
                {

                    // recorremos la columna para abajo
                    aux2 = aux2->getAbajo();
                    archivo << "nodo" << aux2->getFila() << aux2->getColumna() << " -> node" << i << endl;
                    archivo << "node" << i << " -> nodo" << aux2->getFila() << aux2->getColumna() << endl;
                    temp = "nodo" + to_string(aux2->getFila()) + to_string(aux2->getColumna());
                    cache += 1;
                }
            }
            aux3 = aux3->getSiguiente();
            cache = 0;
            temp = "";
        }

        // cabeceras filas

        // conexiones arriba -> abajo

        archivo << "/*------------Relaciones Verticales------------*/" << endl;
        conexion = "";

        for (int i = columnas; i < ((filas - 1) + (columnas - 1)); i++)
        {
            if (i == columnas)
            {
                conexion += "node0 -> node" + to_string(i) + " ";
            }
            else
            {
                conexion += " node" + to_string(i - 1) + " -> node" + to_string(i) + " ";
            }
        }
        conexion += " -> node" + to_string((filas - 1) + (columnas - 1));
        archivo << conexion << ";" << endl;
        // conexiones abajo -> arriba

        conexion = "";
        int nodosss = ((filas - 1) + (columnas - 1));
        for (int i = nodosss; i > columnas - 1; i--)
        {
            if (i == ((filas - 1) + (columnas - 1)))
            {
            }
            else
            {
                conexion += "node" + to_string(i + 1) + " -> node" + to_string(i) + " ";
            }
        }

        // sin algoritmo para verticales

        aux3 = root;
        aux3 = aux3->getAbajo();
        cache = 0;
        temp = "";

        for (int i = 1; i < filas; i++)
        {
            archivo << "/*------------Fila enlace:" << i << "------------*/" << endl;

            Nodom *aux2 = aux3;
            // vemos que la fila no este vacia hacia abajo
            while (aux2->getSiguiente() != nullptr)
            {
                if (cache != 0)
                {
                    aux2 = aux2->getSiguiente();
                    archivo << "nodo" << aux2->getFila() << aux2->getColumna() << " -> " << temp << endl;
                    archivo << temp << " -> nodo" << aux2->getFila() << aux2->getColumna() << aux2->getColumna() << endl;
                }
                else if (cache == 0)
                {

                    // recorremos la columna para abajo
                    aux2 = aux2->getSiguiente();
                    archivo << "nodo" << aux2->getFila() << aux2->getColumna() << " -> node" << (i + columnas - 1) << endl;
                    archivo << "node" << (i + columnas - 1) << " -> nodo" << aux2->getFila() << aux2->getColumna() << ";" << endl;

                    temp = "nodo" + to_string(aux2->getFila()) + to_string(aux2->getColumna());
                    cache += 1;
                }
            }
            aux3 = aux3->getAbajo();
            cache = 0;
            temp = "";
        }

        conexion += " -> node0;";
        archivo << conexion << endl;
        conexion = "";
        archivo << "/*------------Encuadre Columnas-----------*/" << endl;
        conexion += "{ rank=same; node0; ";
        for (int i = 1; i < columnas; i++)
        {
            conexion += "node" + to_string(i) + "; ";
        }
        archivo << conexion << "};" << endl;

        conexion = "";

        Nodom *recorrer = root;

        for (int i = 1; i < filas; i++)
        {
            recorrer = recorrer->getAbajo();
            archivo << "/*------------Encuadre Filas-----------*/" << endl;
            conexion += "{ rank=same; node" + to_string(i + columnas - 1) + "; ";

            Nodom *aux = recorrer;
            while (aux->getSiguiente() != nullptr)
            {
                aux = aux->getSiguiente();
                conexion += "nodo" + to_string(aux->getFila()) + to_string(aux->getColumna()) + "; ";
            }

            archivo << conexion << "};" << endl;
            conexion = "";
        }
        archivo << "}";
        archivo.close();
        system("dot -Tpng MatrizD.dot -o MatrizD.png");
        system("open MatrizD.png");
    }
}

void Matriz::imprimirColumnas()
{
    Nodom *aux = root;

    do
    {
        cout << aux->getCiudad() << aux->getFila() << aux->getColumna() << " ";
        aux = aux->getSiguiente();
    } while (aux->getSiguiente() != nullptr);
    cout << aux->getCiudad() << aux->getFila() << aux->getColumna() << " ";
    cout << endl;
}

void Matriz::imprimirFilas()
{
    Nodom *aux = root;

    do
    {
        cout << aux->getVuelo() << aux->getFila() << aux->getColumna() << " ";
        aux = aux->getAbajo();
    } while (aux->getAbajo() != nullptr);
    cout << aux->getVuelo() << aux->getFila() << aux->getColumna() << " ";
    cout << endl;
}

Matriz::~Matriz()
{
}