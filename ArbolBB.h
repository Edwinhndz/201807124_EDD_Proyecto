#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "Nodo.h"

class ArbolBB
{
private:
    /* data */
    Nodo *raiz;
    ofstream archivo;
    int nodoDato;

public:
    int recorrido = 0;
    ArbolBB(/* args */);
    bool estaVacio();
    void insertar(int horas, string name, string nacion, string id, string vuelo, string licencia, Nodo *padre);
    Nodo *insertarNodo(Nodo *nodoPtr, int horas, string name, string nacion, string id, string vuelo, string licencia, Nodo *padre);
    void buscar(int dato);
    int buscarNodo(int dato, Nodo *nodoPtr);

    void RecorridoPre();
    void RecorridoPre(Nodo *nodoPtr);
    void RecorridoIn();
    void RecorridoIn(Nodo *nodoPtr);
    void RecorridoPost();
    void RecorridoPost(Nodo *nodoPtr);

    void generarReporte();
    void imprimirNodo(Nodo *nodoPtr);
    void imprimirNodoId(Nodo *nodoPtr);
    void eliminarNodo(Nodo *nodoPtr, string id, int horas);
    void eliminar(Nodo *nodoPtr);

    //metodos para eliminar
    Nodo EncontrarMax(Nodo *nodoPtr);
    int GetHorasByID(string id);
    int GetHorasByID(Nodo *nodoPtr, string id);
    void EliminarNodo(string id);
    Nodo *BorrarNodo(Nodo *root, int horas_de_vuelo); 

    void SetRaiz();
    Nodo *GetRaiz();
    ~ArbolBB();
};

ArbolBB::ArbolBB(/* args */)
{
    raiz = nullptr;
}

//elminar

Nodo ArbolBB::EncontrarMax(Nodo *nodoPtr){
    while(nodoPtr->getDer() != NULL) {
        nodoPtr= nodoPtr->getDer();
    }
    return *nodoPtr;
}

int ArbolBB::GetHorasByID(string numero_de_id){
    return GetHorasByID(raiz, numero_de_id);
}

int ArbolBB::GetHorasByID(Nodo *root, string numero_de_id) {
    if (root == nullptr) {
        return -1; // Árbol vacío o llegamos a una hoja, retorna -1 como indicador de no encontrado
    }

    // Busca en el subárbol izquierdo
    
    int leftResult = GetHorasByID(root->getIzq() , numero_de_id);
    if (leftResult != -1) {
        return leftResult;
    }

    // Verifica el nodo actual
    if (root->getNumero_de_id() == numero_de_id) {
        return root->getHoras();
    }

    // Busca en el subárbol derecho
    return GetHorasByID(root->getDer(), numero_de_id);
}

void ArbolBB::EliminarNodo(string numero_de_id) 
{
    int horas_de_vuelo = ArbolBB::GetHorasByID(numero_de_id);
    cout << horas_de_vuelo << endl;
    raiz = BorrarNodo(raiz, horas_de_vuelo);
}

Nodo *ArbolBB::BorrarNodo(Nodo *root, int horas_de_vuelo) {
    
	if(root == nullptr){
    return root;
    } else if(horas_de_vuelo < root->getHoras() ){
        root->setIzq(BorrarNodo(root->getIzq(),horas_de_vuelo));
    }else if (horas_de_vuelo > root->getHoras()) {
        root->setDer(BorrarNodo(root->getDer(),horas_de_vuelo));
    }
	// Wohoo... I found you, Get ready to be deleted	
	else {
		// Case 1:  No child
		if(root->getIzq() == nullptr && root->getDer() == nullptr ) { 
			delete root;
			root = nullptr;
		}

		//Case 2: One child 
		else if(root->getIzq() == nullptr) {
			Nodo *temp = root;
			root = root->getDer();
			delete temp;
		}
		else if(root->getDer() == nullptr) {
			Nodo *temp = root;
			root = root->getIzq();
			delete temp;
		}
		// case 3: 2 children
		else { 
			Nodo temp = EncontrarMax(root->getIzq());
            // Copiamos todos los atributos relevantes
            root->setHoras( temp.getHoras());
            root->setNumero_de_id(temp.getNumero_de_id());
            root->setNombre( temp.getNombre());
            root->setNacionalidad(temp.getNacionalidad());
            root->setVuelo(temp.getVuelo());
            root->setTipo_de_licencia(temp.getTipo());
            // Eliminar el nodo duplicado en el subárbol izquierdo
            root = BorrarNodo(root->getIzq(), temp.getHoras());
		}
	}
	return root;
}

//fin eliminar

bool ArbolBB::estaVacio()
{
    return (raiz == nullptr);
}

void ArbolBB::insertar(int horas, string name, string nacion, string id, string vuelo, string licencia, Nodo *padre)
{
    cout << "Horas en insertar: " << horas << "\n";
    raiz = insertarNodo(raiz, horas, name, nacion, id, vuelo, licencia, padre);
}

Nodo *ArbolBB::insertarNodo(Nodo *nodoPtr, int horas, string name, string nacion, string id, string vuelo, string licencia, Nodo *padre)
{

    if (nodoPtr == nullptr)
    {

        Nodo *nuevo = new Nodo();
        nodoPtr = nuevo;
        nuevo->setHoras(horas);
        nuevo->setNombre(name);
        nuevo->setNacionalidad(nacion);
        nuevo->setNumero_de_id(id);
        nuevo->setVuelo(vuelo);
        nuevo->setTipo_de_licencia(licencia);
        nuevo->setPadre(padre);

        cout << "insertando raiz con: " << horas << "\n";
    }
    else if (horas < nodoPtr->getHoras())
    {
        nodoPtr->setIzq(insertarNodo(nodoPtr->getIzq(), horas, name, nacion, id, vuelo, licencia, padre));
        cout << "insertando izq con: " << horas << "\n";
    }
    else if (horas > nodoPtr->getHoras())
    {
        nodoPtr->setDer(insertarNodo(nodoPtr->getDer(), horas, name, nacion, id, vuelo, licencia, padre));
        cout << "insertando der con: " << horas << "\n";
    }
    else if (horas == nodoPtr->getHoras())
    {
        nodoPtr->setDer(insertarNodo(nodoPtr->getDer(), horas, name, nacion, id, vuelo, licencia, padre));
        cout << "insertando der igual raiz con: " << horas << "\n";
    }
    else
    {
        cout << "ninguno de los casos";
    }
    return nodoPtr;
}

void ArbolBB::buscar(int dato)
{
    cout << "Recorrido del nodo encontrado: " << buscarNodo(dato, raiz) << ", " << recorrido;
}

int ArbolBB::buscarNodo(int dato, Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        cout << "Nodo no encontrado\n";
        return 0;
    }
    else if (dato == nodoPtr->getHoras())
    {
        recorrido++;
        return nodoPtr->getHoras();
    }
    else if (dato < nodoPtr->getHoras())
    {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getIzq());
    }
    else if (dato > nodoPtr->getHoras())
    {
        recorrido++;
        return buscarNodo(dato, nodoPtr->getDer());
    }
}

void ArbolBB::RecorridoPre()
{
    RecorridoPre(raiz);
}

void ArbolBB::RecorridoPre(Nodo *nodoPtr)
{
    if (nodoPtr != nullptr)
    {
        // PREORDEN
        cout << "Nombre: " << nodoPtr->getNombre() << ", Horas de vuelo: " << nodoPtr->getHoras() << endl;
        RecorridoPre(nodoPtr->getIzq());
        RecorridoPre(nodoPtr->getDer());
    }
}

void ArbolBB::RecorridoIn()
{
    RecorridoIn(raiz);
}

void ArbolBB::RecorridoIn(Nodo *nodoPtr)
{

    if (nodoPtr == nullptr)
    {
        return;
    }
    else
    {
        // INORDEN
        RecorridoIn(nodoPtr->getIzq());
        cout << "Nombre: " << nodoPtr->getNombre() << ", Horas de vuelo: " << nodoPtr->getHoras() << endl;
        RecorridoIn(nodoPtr->getDer());
    }
}

void ArbolBB::RecorridoPost()
{
    RecorridoPost(raiz);
}

void ArbolBB::RecorridoPost(Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        return;
    }
    else
    {
        // POSTORDEN
        RecorridoPost(nodoPtr->getIzq());
        RecorridoPost(nodoPtr->getDer());
        cout << "Nombre: " << nodoPtr->getNombre() << ", Horas de vuelo: " << nodoPtr->getHoras() << endl;
    }
}

void ArbolBB::generarReporte()
{
    if (ArbolBB::estaVacio())
    {
    }
    else
    {
        archivo.open("grafica_arbol.dot", ios::out);
        archivo << "digraph G { " << endl;

        imprimirNodo(raiz);

        archivo << " }";
        archivo.close();
        system("dot -Tpng grafica_arbol.dot -o grafica_arbol.png");
        system("open grafica_arbol.png");
    }
}

void ArbolBB::imprimirNodo(Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        return;
    }

    if (nodoPtr->getIzq() != nullptr)
    {
        string id;
        string label = "";

        id = nodoPtr->getNumero_de_id();
        nodoDato = nodoPtr->getHoras();
        label = id + "[label =\"" + to_string(nodoPtr->getHoras()) + "\n " + nodoPtr->getNumero_de_id() + "DER\"];\n";
        archivo << label;
        archivo << id;

        archivo << "->";
        nodoDato = nodoPtr->getIzq()->getHoras();

        id = nodoPtr->getIzq()->getNumero_de_id();
        label = id + "[label =\"" + to_string(nodoPtr->getIzq()->getHoras())+ "\n " + nodoPtr->getNumero_de_id() +  "Izq\"];\n";
        archivo << id;
        archivo << ";\n";
        archivo << label;
    }
    imprimirNodo(nodoPtr->getIzq());

    if (nodoPtr->getDer() != nullptr)
    {

        string id;
        string label = "";

        nodoDato = nodoPtr->getHoras();
        id = nodoPtr->getNumero_de_id();
        label = id + "[label =\"" + to_string(nodoPtr->getHoras())+ "\n " + nodoPtr->getNumero_de_id() + "\"];\n";
        archivo << label;

        archivo << id;
        archivo << "->";
        nodoDato = nodoPtr->getDer()->getHoras();
        id = nodoPtr->getDer()->getNumero_de_id();
        label = id + "[label =\"" + to_string(nodoPtr->getDer()->getHoras()) + "\n " + nodoPtr->getNumero_de_id() +  "Der\"];\n";
        archivo << id;
        archivo << ";\n";
        archivo << label;
    }
    imprimirNodo(nodoPtr->getDer());
}

void ArbolBB::imprimirNodoId(Nodo *nodoPtr)
{
    if (nodoPtr == nullptr)
    {
        return;
    }

    if (nodoPtr->getIzq() != nullptr)
    {
        nodoDato = nodoPtr->getHoras();
        archivo << nodoDato;
        archivo << "->";
        nodoDato = nodoPtr->getIzq()->getHoras();
        archivo << nodoDato;
        archivo << ";\n";
    }
    imprimirNodo(nodoPtr->getIzq());

    if (nodoPtr->getDer() != nullptr)
    {
        nodoDato = nodoPtr->getHoras();
        archivo << nodoDato;
        archivo << "->";
        nodoDato = nodoPtr->getDer()->getHoras();
        archivo << nodoDato;
        archivo << ";\n";
    }
    imprimirNodo(nodoPtr->getDer());
}

void ArbolBB::eliminarNodo(Nodo *arbol, string id, int horas)
{
    if (arbol == nullptr)
    {
        return;
    }
    else if (horas < arbol->getHoras())
    {
        eliminarNodo(arbol->getIzq(), id, horas);
    }
    else if (horas > arbol->getHoras())
    {
        eliminarNodo(arbol->getDer(), id, horas);   
    }else if(horas == arbol->getHoras()){
        eliminarNodo(arbol->getDer(), id, horas);
    }else{
        eliminar(arbol);
    }
}

void ArbolBB::eliminar(Nodo *arbol){

}

void ArbolBB::SetRaiz()
{
    this->raiz = nullptr;
}

Nodo *ArbolBB::GetRaiz()
{
    return this->raiz;
}

ArbolBB::~ArbolBB()
{
}