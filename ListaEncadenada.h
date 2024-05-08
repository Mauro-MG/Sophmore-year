#ifndef LISTAENCADENADA_H
#define LISTAENCADENADA_H
# include <iostream>
# include "Nod.h"

using namespace std;

// DefiniciÃ³n de la clase Lista Encadenada
template <typename T>
class ListaEncadenada 
{
    
public:
    ListaEncadenada();            // constructor
          // destructor
    bool estaVacia();
    bool insertarElementoInicio(T info);
    void desplegarLista();
    int tamanio();
    int encontrarPosicionElemento(T info);
    void borrarElementoInicio();
    T* traerDatosInicio();
    T obtenerElementoEnPosicion(int posicion);
    void borrarElemento(int posicion);
    void borrarElementoFinal();
    bool insertarElementoFinal(T info);


private:       
    Nod<T>* inicio;        // ptr a objeto inicial de la lista
    Nod<T>* final;
};

template <typename T>
ListaEncadenada<T>::ListaEncadenada()
{
    inicio = nullptr;
}



template <typename T>
bool ListaEncadenada<T>::estaVacia()
{
    return inicio == nullptr;
}

template <typename T>
bool ListaEncadenada<T>::insertarElementoInicio(T info)
{
    Nod<T>* nuevo;
    bool bandera;

    nuevo = new Nod<T>(info);
    bandera = (nuevo != nullptr);

    if (bandera)
    {
        if (inicio == nullptr)
          inicio = nuevo;
        else
        {
            nuevo->siguiente = inicio;
            inicio = nuevo;
        }
    }

    return bandera;
}

template <typename T>
void ListaEncadenada<T>::desplegarLista()
{
    Nod<T>* auxiliar = inicio;
    int indice = 0;

    if (inicio != nullptr)
        do
        {
            indice = indice + 1;
            cout << auxiliar->informacion<<endl;
            auxiliar = auxiliar ->siguiente;
        }while(auxiliar != nullptr);
    else
        cout << "La lista esta vacia"<<endl;
    
}

template <typename T>
int ListaEncadenada<T>::tamanio()
{
    Nod<T>* auxiliar = inicio;
    int indice = 0;

    if (inicio != nullptr)
        do
        {   
            indice = indice + 1;
            auxiliar = auxiliar ->siguiente;
        }while(auxiliar != nullptr);
    
    return indice;
    
}



template <typename T>    
int ListaEncadenada<T>::encontrarPosicionElemento(T info)
{
    Nod<T>* auxiliar = inicio;
    int indice = 1;

 
    while ( (auxiliar != nullptr) and (auxiliar->informacion != info))
    {   
        indice = indice + 1;
        auxiliar = auxiliar ->siguiente;
    };

    if (auxiliar == nullptr)
        indice = 0;

    return indice;
 
}

template <typename T>  
void ListaEncadenada<T>::borrarElementoInicio()
{
  Nod<T>* auxiliar;

  if (inicio != nullptr)
  {
    auxiliar = inicio -> siguiente;
    delete inicio;
    inicio = auxiliar;
  }
}

template <typename T>     
T* ListaEncadenada<T>::traerDatosInicio()
{
  Nod<T>* auxiliar;
  if (inicio != nullptr){   
     return &(inicio -> informacion);
  }

}
template <typename T>
T ListaEncadenada<T>::obtenerElementoEnPosicion(int posicion) {
    Nod<T>* auxiliar = inicio;
    int indice = 0;

    while (auxiliar != nullptr && indice < posicion) {
        auxiliar = auxiliar->siguiente;
        indice++;
    }

    if (auxiliar != nullptr) {
        return (auxiliar->informacion);
    }
}
template <typename T>
void ListaEncadenada<T>::borrarElemento(int posicion) {
    Nod<T>* auxiliar = inicio;
    Nod<T>* anterior=nullptr;
    int tamanio=this->tamanio();
    if(posicion==1){
        inicio=auxiliar->siguiente;
        delete auxiliar;
    }else if(posicion<=tamanio){
        for(int i=0; i<posicion; i++){
            anterior=auxiliar;
            auxiliar=auxiliar->siguiente;
        }
        anterior->siguiente=auxiliar->siguiente;
        delete auxiliar;
        if(posicion==tamanio){
            final=anterior;
        }
    }
}
template <typename T>
void ListaEncadenada<T>::borrarElementoFinal()
{
    Nod<T>* auxiliar = inicio;

    if (inicio != nullptr)
    {
        if (inicio->siguiente == nullptr)
        {  
            delete inicio;
            inicio = nullptr;
        }
        else
        {   while((auxiliar->siguiente)->siguiente != nullptr)
                auxiliar = auxiliar->siguiente;
            delete auxiliar->siguiente;
            auxiliar->siguiente = nullptr;
        }
    }

}

template <typename T>
bool ListaEncadenada<T>::insertarElementoFinal(T info)
{
    Nod<T>* nuevo;
    Nod<T>* auxiliar = inicio;
    bool bandera;

    nuevo = new Nod<T>(info);
    bandera = (nuevo != nullptr);

    if (bandera)
    {
        if (inicio == nullptr)
          inicio = nuevo;
        else
        {
            auxiliar=inicio;
           while(auxiliar->siguiente != nullptr)
                auxiliar = auxiliar->siguiente;
           auxiliar->siguiente = nuevo;
        }
    }

    return bandera;
}

#endif