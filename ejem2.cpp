#include <iostream>
#include "ArbolB.h"
#include "NodoAvion.h"

int main() {
    ArbolB<NodoA, 5> t1;
    cout << "Si define el Arbol" << endl;
    t1.Insert(NodoA("A100", "N80", "Modelo1", 180, "Aerolinea1", "Ciudad1", "Estado1"));
    t1.Insert(NodoA("Vuelo2", "N40", "Modelo2", 150, "Aerolinea2", "Ciudad2", "Estado2"));
    t1.Insert(NodoA("Vuelo3", "N10", "Modelo3", 180, "Aerolinea3", "Ciudad3", "Estado3"));
    t1.Insert(NodoA("Vuelo4", "N50", "Modelo4", 250, "Aerolinea4", "Ciudad4", "Estado4"));
    t1.Insert(NodoA("Vuelo5", "N25", "Modelo5", 300, "Aerolinea5", "Ciudad5", "Estado5"));
    t1.Insert(NodoA("Vuelo5", "N55", "Modelo6", 300, "Aerolinea5", "Ciudad5", "Estado5"));
    cout << "Insertado N55" << endl;
    t1.Print();
    t1.Insert(NodoA("Vuelo5", "N60", "Modelo7", 300, "Aerolinea5", "Ciudad5", "Estado5"));
    cout << "Insertado N60" << endl;
    t1.Print();
    t1.Insert(NodoA("Vuelo5", "N15", "Modelo8", 300, "Aerolinea5", "Ciudad5", "Estado5"));
    cout << "Insertado N15" << endl;
    t1.Print();
    t1.Insert(NodoA("Vuelo5", "N88", "Modelo9", 300, "Aerolinea5", "Ciudad5", "Estado5"));
    // t1.Insert(Nodo("Vuelo5", "N13", "Modelo10", 300, "Aerolinea5", "Ciudad5", "Estado5"));
    cout << "Intenta imprimir" << endl;
    t1.Print();
    cout << "imprimir" << endl;
    t1.GenerateDOT("btree_nodo.dot");

    return 0;
}