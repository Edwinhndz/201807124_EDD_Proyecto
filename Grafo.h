#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm> 
#include "Vertice.h"
using namespace std;

const int INFINITO = 1000000; // Define un valor grande para representar infinito

class Grafo
{
private:
    /* data */
    int numVertices; //número de vértices actuales en el grafo
    int maxVertices; //número máximo de vértices en el grafo
    Vertice* vertices; //arreglo de vértices
    int** matrizAdy; //matriz de adyacencia

    ofstream archivo;
    string arco;
public:
    Grafo(/* args */);

    Grafo(int max);
    int getNumVertices(); //Obtiene el número de vértices
    void setNumVertices(int n); //Establecer el número de vértices

    void nuevoVertice(string nombre);
    int existeVertice(string nombre); //Comprueba si el nombre recibido se encuentra en la lista de vértices
    void nuevoArco(string nom1, string nom2, int km); //Agrega 1 a la matriz de adyacencia si los 2 vértices existen
    void imprimirMatriz();
    void generarReporte();
    

    int obtenerIndice(string nombre) {
        for (int i = 0; i < numVertices; i++) {
            if (vertices[i].getNombre() == nombre) {
                return i;
            }
        }
        return -1; // Si el vértice no existe
    }

    string obtenerNombre(int indice) {
        if (indice >= 0 && indice < numVertices) {
            return vertices[indice].getNombre();
        }
        return ""; // Si el índice no es válido
    }

    vector<int> dijkstra(string srcNombre) {
        //cout << "en metodo2" <<endl;
        int src = obtenerIndice(srcNombre);
        if (src == -1) {
            cerr << "El vértice de origen no existe." << endl;
            return vector<int>();
        }

        vector<int> dist(maxVertices, INFINITO);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            //cout << "en metodo3" <<endl;
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < maxVertices; v++) {
                if (matrizAdy[u][v] != 0) {
                    int peso = matrizAdy[u][v];
                    if (dist[v] > dist[u] + peso) {
                        dist[v] = dist[u] + peso;
                        pq.push(make_pair(dist[v], v));
                    }
                }
            }
        }

        return dist;
    }

    vector<string> caminoMasCorto(string origen, string destino) {
        //cout <<"en metodo1" <<endl;
        vector<int> dist = dijkstra(origen);
        int dest = obtenerIndice(destino);
        if (dest == -1) {
            cerr << "El vértice de destino no existe." << endl;
            return vector<string>();
        }

        vector<string> camino;
        int current = dest;
        camino.push_back(obtenerNombre(current));
        cout << dest<<endl;

        
    cout << endl;

        while (dist[current] != 0) {
            for (int i = 0; i < maxVertices; i++) {
                if (matrizAdy[i][current] != 0 && dist[current] == dist[i] + matrizAdy[i][current]) {
                    camino.push_back(obtenerNombre(i));
                    current = i;
                    break;
                }
            }
        }

        reverse(camino.begin(), camino.end());
        return camino;
    }


    ~Grafo();
};

Grafo::Grafo(/* args */)
{
}

typedef int* int_m; //para la dimension de la matriz

Grafo::Grafo(int max)
{
    numVertices = 0; //número de vértices en el grafo, cuando se crea el grafo este aún no tiene nodos
    maxVertices = max; //Número máximo de vértices en el grafo
    vertices = new Vertice[max]; //arreglo de vértices
    matrizAdy = new int_m[max]; //arreglo de punteros
    for (int i = 0; i < max; i++)
    {
        matrizAdy[i] = new int[max]; //Completando la matriz de adyacencia
    }

    for (int i = 0; i < maxVertices; i++)
    {
        for (int j = 0; j < maxVertices; j++)
        {
            matrizAdy[i][j] = 0;
        } 
    }
    
    /**/
}

int Grafo::getNumVertices()
{
    return this->numVertices;
}

void Grafo::setNumVertices(int n)
{
    this->numVertices = n;
}

void Grafo::nuevoVertice(string nombre)
{
    bool existe = (existeVertice(nombre) >= 0);
    if (!existe) //Si no existe
    {
        Vertice nuevo = Vertice(nombre,numVertices);
        vertices[numVertices] = nuevo; //Se agrega el nuevo vértice a la lista
        numVertices++;
    }
}

int Grafo::existeVertice(string nombre)
{   //Busca el vértice en el arreglo vértices, retorna -1 si no lo encuentra
    int i = 0;
    bool encontrado = false;
    while (i < numVertices && !encontrado)
    {   //El ciclo se repite mientras no se haya iterado una cantidad mayor o igual al número de toal de vertices existentes
        //Y mientras no se haya encontrado un vértice con el mismo nombre al que se desea agregar
        encontrado = vertices[i].esIgual(nombre); //Falso mientras no se haya encontrado un vértice con el mismo nombre
        if (!encontrado)
        {
            i++;
        }
    }
    //Si 'i' es menor al número total de vértices, quiere decir que lo encontró en alguna de todas las iteraciones
    return (i < numVertices) ? i : -1;
}

void Grafo::nuevoArco(string nom1, string nom2, int km)
{   //Recibe el nombre de los 2 vértices que forman el arco y los busca en el arreglo de vértices
    //Si existen agrego 1 a la matriz de adyacencia
    int vertice1, vertice2;
    vertice1 = existeVertice(nom1);
    vertice2 = existeVertice(nom2);
    if (vertice1 >= 0 && vertice2 >= 0)
    {
        matrizAdy[vertice1][vertice2] = km;  
    }
    else
    {
        cout << "Error, uno de los vértices no existe\n";
    }
}

void Grafo::imprimirMatriz()
{
    for (int i = 0; i < maxVertices; i++)
    {
        for (int j = 0; j < maxVertices; j++)
        {
            cout << " " << matrizAdy[i][j] << " ";
        }  
        cout << endl;
    }
}

void Grafo::generarReporte()
{
   
    if (getNumVertices() == 0) {} //Grafo vacío
    else{
        archivo.open("grafo.dot",ios::out);
        archivo << "digraph G { \n rankdir= LR;\n " << endl;

        for (int i = 0; i < maxVertices; i++)
        {
            for (int j = 0; j < maxVertices; j++)
            {
                if (matrizAdy[i][j] != 0)
                {
                    /* code */
                    arco += vertices[i].getNombre() + " -> " + vertices[j].getNombre() + " [label=\"" + to_string(matrizAdy[i][j]) + "\"]" + ";\n";
                    archivo << arco;
                    arco.clear();
                }
            }  
        }

        archivo << "}";
        archivo.close();
        system("dot -Tpng grafo.dot -o grafo.png");
        system("open grafo.png");
    }
}





Grafo::~Grafo()
{
}