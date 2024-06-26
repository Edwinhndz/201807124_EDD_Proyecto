#include <iostream>
#include <string>
using namespace std;

class NodoAd
{
private:
    /* data */
    NodoAd *sig;
    NodoAd *ruta;
    int distancia;
    string ciudad;
public:
    NodoAd(/* args */);
    ~NodoAd();
};

NodoAd::NodoAd(/* args */)
{
}

NodoAd::~NodoAd()
{
}

