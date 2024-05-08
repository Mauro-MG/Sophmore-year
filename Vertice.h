#ifndef VERTICE_H
#define VERTICE_H
#include <iostream>
#include "ListaEncadenada.h"
using namespace std;
template <typename T>
class Vertice{
    public:
    Vertice();
    Vertice(T info);
    void asignaInformacion(T info);
    T traeInformacion();
    void asignaEstado(int edo);
    int traeEstado();
    ListaEncadenada<int>* traeAdyacencias();


    private:
    T informacion;
    ListaEncadenada<int> lista_adyacensias;
    int estado;

};


template <typename T>
inline Vertice<T>::Vertice()
{
    estado=0;
}

template <typename T>
inline Vertice<T>::Vertice(T info)
{
    informacion=info;
    estado=0;
}

template <typename T>
void Vertice<T>::asignaInformacion(T info)
{
    informacion=info;
}

template <typename T>
inline T Vertice<T>::traeInformacion()
{
    return informacion;
}

template <typename T>
 void Vertice<T>::asignaEstado(int edo)
{
    estado=edo;
}

template <typename T>
inline int Vertice<T>::traeEstado()
{
    return estado;
}

template <typename T>
inline ListaEncadenada<int>* Vertice<T>::traeAdyacencias()
{
    return &lista_adyacensias;
}
#endif
