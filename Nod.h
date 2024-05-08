#ifndef NOD_H
#define NOD_H
#include <iostream>
using namespace std;
template <typename T>
class ListaEncadenada;

template <typename T>
class Nod
{
    friend class ListaEncadenada<T>;
public:
    Nod(T e);

private:
    T informacion;
    Nod<T>* siguiente;
};

template <typename T>

Nod<T>::Nod(T e) 
{ 
    informacion = e; 
    siguiente = nullptr;
}
#endif 