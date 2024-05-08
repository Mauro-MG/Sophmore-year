#ifndef PILA_H
#define PILA_H
#include <iostream>
#include "ListaEncadenada.h"
using namespace std;
template <typename T>
class Pila{
    private:
    ListaEncadenada<T> lista;

    public:
    Pila();
    ~Pila();
    bool mete(T info);
    void saca();
    T tope();
    bool estaVaciaP();
    int encontrar(T info);
    void mostrarPila();
};
template <typename T>
inline Pila<T>::Pila()
{
}
template <typename T>
inline Pila<T>::~Pila()
{
}
template <typename T>
bool Pila<T>::mete(T info)
{
    lista.insertarElementoInicio(info);
}

template <typename T>
 void Pila<T>::saca()
{
    lista.borrarElementoInicio();
}

template <typename T>
 T Pila<T>::tope()
{
    return lista.traerDatosInicio();
}

template <typename T>
 bool Pila<T>::estaVaciaP()
{
    lista.estaVacia();
}

template <typename T>
inline int Pila<T>::encontrar(T info)
{
    return lista.encontrarPosicionElemento(info);
}

template <typename T>
inline void Pila<T>::mostrarPila()
{
    lista.desplegarLista();
}

#endif