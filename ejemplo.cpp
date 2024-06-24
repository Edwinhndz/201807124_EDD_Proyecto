/*
  Name: Representacion enlazada de un grafo
  Author:   Joel Fernandez
  Date: 01/12/12 23:43
  Web: http://codebotic.blogspot.com
  Description: programa que muestra un grafo en su forma enlazada
*/

#include <iostream>
using namespace std;

struct nodo{
            char nombre;//nombre del vertice o nodo
            struct nodo *sgte;
            struct arista *ady;//puntero hacia la primera arista del nodo
            };
struct arista{
              struct nodo *destino;//puntero al nodo de llegada
              struct arista *sgte;
              };
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista

Tnodo p;//puntero cabeza

void menu();
void insertar_nodo();
void agrega_arista(Tnodo &, Tnodo &, Tarista &);
void insertar_arista();
void vaciar_aristas(Tnodo &);
void eliminar_nodo();
void eliminar_arista();
void mostrar_grafo();
void mostrar_aristas();


/*                        Funcion Principal
---------------------------------------------------------------------*/
int main(void)
{   p=NULL;
    int op;     // opcion del menu


    system("color 0b");

    do
    {
        menu();
        cin>>op;

        switch(op)
        {
            case 1:
                    insertar_nodo();
                    break;
            case 2: insertar_arista();
                    break;
            case 3: eliminar_nodo();
                    break;
            case 4: eliminar_arista();
                    break;
            case 5: mostrar_grafo();
                    break;
            case 6: mostrar_aristas();
                    break;

            default: cout<<"OPCION NO VALIDA...!!!";
                     break;


        }

        cout<<endl<<endl;

    }while(op!=7);
    return 0;
}

/*                          Menu
---------------------------------------------------------------------*/
void menu()
{
    cout<<"\n\tREPRESENTACION DE GRAFOS DIRIGIDOS\n\n";
    cout<<" 1. INSERTAR UN NODO                 "<<endl;
    cout<<" 2. INSERTAR UNA ARISTA              "<<endl;
    cout<<" 3. ELIMINAR UN NODO                 "<<endl;
    cout<<" 4. ELIMINAR UNA ARISTA              "<<endl;
    cout<<" 5. MOSTRAR  GRAFO                   "<<endl;
    cout<<" 6. MOSTRAR ARISTAS DE UN NODO       "<<endl;
    cout<<" 7. SALIR                            "<<endl;

    cout<<"\n INGRESE OPCION: ";
}

/*                      INSERTAR NODO AL GRAFO
---------------------------------------------------------------------*/
void insertar_nodo()
{
    Tnodo t,nuevo=new struct nodo;
    cout<<"INGRESE VARIABLE:";
    cin>>nuevo->nombre;
    nuevo->sgte = NULL;
    nuevo->ady=NULL;

    if(p==NULL)
     {
        p = nuevo;
        cout<<"PRIMER NODO...!!!";
      }
    else
     {
        t = p;
        while(t->sgte!=NULL)
         {
            t = t->sgte;
          }
        t->sgte = nuevo;
        cout<<"NODO INGRESADO...!!!";
      }

 }

/*                      AGREGAR ARISTA
    funcion que utilizada para agregar la arista a dos nodos
---------------------------------------------------------------------*/
void agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo)
{
    Tarista q;
    if(aux->ady==NULL)
    {   aux->ady=nuevo;
        nuevo->destino=aux2;
        cout<<"PRIMERA ARISTA....!";
    }
    else
    {   q=aux->ady;
        while(q->sgte!=NULL)
            q=q->sgte;
        nuevo->destino=aux2;
        q->sgte=nuevo;
        cout<<"ARISTA AGREGADA...!!!!";
    }

}
/*                      INSERTAR ARISTA
    funcion que busca las posiciones de memoria de los nodos
    y hace llamado a agregar_arista para insertar la arista
---------------------------------------------------------------------*/
void insertar_arista()
{   char ini, fin;
    Tarista nuevo=new struct arista;
    Tnodo aux, aux2;

    if(p==NULL)
     {
         cout<<"GRAFO VACIO...!!!!";
         return;
     }
    nuevo->sgte=NULL;
    cout<<"INGRESE NODO DE INICIO:";
    cin>>ini;
    cout<<"INGRESE NODO FINAL:";
    cin>>fin;
    aux=p;
    aux2=p;
    while(aux2!=NULL)
    {
        if(aux2->nombre==fin)
        {
            break;
        }

        aux2=aux2->sgte;
    }
    while(aux!=NULL)
    {
        if(aux->nombre==ini)
        {
            agrega_arista(aux,aux2, nuevo);
            return;
        }

        aux = aux->sgte;
    }
}

/*          FUNCION PARA BORRAR TODAS LAS ARISTAS DE UN NODO
    esta funcion es utilizada al borrar un nodo pues si tiene aristas
    es nesesario borrarlas tambien y dejar libre la memoria
---------------------------------------------------------------------*/
void vaciar_aristas(Tnodo &aux)
{
    Tarista q,r;
    q=aux->ady;
    while(q->sgte!=NULL)
    {
        r=q;
        q=q->sgte;
        delete(r);
    }
}
/*                      ELIMINAR NODO
    funcion utilizada para eliminar un nodo del grafo
    pero para eso tambien tiene que eliminar sus aristas por lo cual
    llama a la funcion vaciar_aristas para borrarlas
---------------------------------------------------------------------*/
void eliminar_nodo()
{   char var;
    Tnodo aux,ant;
    aux=p;
    cout<<"ELIMINAR UN NODO\n";
    if(p==NULL)
     {
         cout<<"GRAFO VACIO...!!!!";
         return;
     }
    cout<<"INGRESE NOMBRE DE VARIABLE:";
    cin>>var;

    while(aux!=NULL)
    {
        if(aux->nombre==var)
        {
            if(aux->ady!=NULL)
                vaciar_aristas(aux);

            if(aux==p)
            {

                    p=p->sgte;
                    delete(aux);
                    cout<<"NODO ELIMINADO...!!!!";
                    return;



            }
            else
            {
                ant->sgte = aux->sgte;
                delete(aux);
                cout<<"NODO ELIMINADO...!!!!";
                return;
            }
        }
        else
        {
            ant=aux;
            aux=aux->sgte;
         }
    }

}

/*                      ELIMINAR ARISTA
    funcion utilizada para eliminar una arista
---------------------------------------------------------------------*/
void eliminar_arista()
{
char ini, fin;
    Tnodo aux, aux2;
    Tarista q,r;
    cout<<"\n ELIMINAR ARISTA\n";
    cout<<"INGRESE NODO DE INICIO:";
    cin>>ini;
    cout<<"INGRESE NODO FINAL:";
    cin>>fin;
    aux=p;
    aux2=p;
    while(aux2!=NULL)
    {
        if(aux2->nombre==fin)
        {
            break;
        }
        else
        aux2=aux2->sgte;
    }
     while(aux!=NULL)
    {
        if(aux->nombre==ini)
        {
            q=aux->ady;
            while(q!=NULL)
            {
                if(q->destino==aux2)
                {
                    if(q==aux->ady)
                        aux->ady=aux->ady->sgte;
                    else
                        r->sgte=q->sgte;
                    delete(q);
                    cout<<"ARISTA  "<<aux->nombre<<"----->"<<aux2->nombre<<" ELIMINADA.....!!!!";
                    return;
                }
            }
            r=q;
            q=q->sgte;
        }
        aux = aux->sgte;
    }
}
/*                      MOSTRAR GRAFO
    funcion que imprime un grafo en su forma enlazada
---------------------------------------------------------------------*/
void mostrar_grafo()
{   Tnodo ptr;
    Tarista ar;
    ptr=p;
    cout<<"NODO|LISTA DE ADYACENCIA\n";

    while(ptr!=NULL)
    {   cout<<"   "<<ptr->nombre<<"|";
        if(ptr->ady!=NULL)
        {
            ar=ptr->ady;
            while(ar!=NULL)
            {   cout<<" "<<ar->destino->nombre;
                ar=ar->sgte;
             }

        }
        ptr=ptr->sgte;
        cout<<endl;
    }
}

/*                      MOSTRAR ARISTAS
    funcion que muestra todas las aristas de un nodo seleccionado
---------------------------------------------------------------------*/
void mostrar_aristas()
{
    Tnodo aux;
    Tarista ar;
    char var;
    cout<<"MOSTRAR ARISTAS DE NODO\n";
    cout<<"INGRESE NODO:";
    cin>>var;
    aux=p;
    while(aux!=NULL)
    {
        if(aux->nombre==var)
        {
            if(aux->ady==NULL)
            {   cout<<"EL NODO NO TIENE ARISTAS...!!!!";
                return;
             }
            else
            {
                cout<<"NODO|LISTA DE ADYACENCIA\n";
                cout<<"   "<<aux->nombre<<"|";
                ar=aux->ady;

                while(ar!=NULL)
                {
                    cout<<ar->destino->nombre<<" ";
                    ar=ar->sgte;
                }
                cout<<endl;
                return;
            }
        }
        else
        aux=aux->sgte;
    }
}