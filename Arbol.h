#ifndef ARBOL_H
#define ARBOL_H
#include "Nodo.h"
#include "Pila.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
template <typename T>
class Arbol{
    public:
    Arbol();
    T visitaNodo(Nodo<T>* nodito);
    bool esHoja(Nodo<T>* nodito);
    Nodo<T>* obtenerRaiz();
    Nodo<T>* predecesor(Nodo<T>* nodito);
    void recorridoInOrden(Nodo<T>* nodito);
    bool agregarNodo(Nodo<T>* raiz, T info);
    void recorridoPostOrden(Nodo<T>* nodito);
    Nodo<T>* Sucesor(Nodo<T>* nodito);
    bool borrarNodo(T info);
    void recorridoPreOrden(Nodo<T>* nodito);
    void recorrerArbol(Nodo<T>* nodo);
    void cargardatosArbol(string nombrearchivo);
    void preOrden(Nodo<T>* &nodo, ifstream& archivo);
    void postOrden(Pila<T> &pilaa, Nodo<T>* &nodo);

    private:
    Nodo<T>* raiz;

};

template <class T>
 T Arbol<T>::visitaNodo(Nodo<T>* nodito)
{
    if(nodito!=nullptr){
        nodito->obtieneInformacion();
    }
}
template <class T>
Arbol<T>::Arbol()
{
  raiz=nullptr;
}
template <class T>
bool Arbol<T>::esHoja(Nodo<T>* nodito)
{
    bool bandera;
    Nodo<T>* hijoIzquierdo;
    Nodo<T>* hijoDerecho;
    bandera=false;
    if(nodito==nullptr){
        bandera=false;
    }else{
        hijoIzquierdo = nodito->obtieneIzquierda();
        hijoDerecho = nodito->obtieneDerecha();
        if(hijoIzquierdo==nullptr && hijoDerecho==nullptr){
            bandera=true;
        }
    }
    return bandera;
}
template <typename T>
Nodo<T>* Arbol<T> :: obtenerRaiz(){
    return raiz;
}
template <typename T>
Nodo<T>* Arbol<T>::predecesor(Nodo<T>* nodito)
{
    Nodo<T>* auxiliar = nodito;     

    if(auxiliar!= NULL){
        auxiliar= auxiliar->obtieneIzquierda(); 
        if(auxiliar!= NULL)
        {
            while(auxiliar->obtieneDerecha() != NULL)
            {
                auxiliar= auxiliar->obtieneDerecha(); 
            }
        }
    }
    return auxiliar;
}
template <typename T>
void Arbol<T>::recorridoInOrden(Nodo<T>* nodito){
    recorridoInOrden(nodito->obtieneIzquierda());
    visitarNodo(nodito);
    recorridoInOrden(nodito->obtieneDerecha());
}

template <typename T>
inline bool Arbol<T>::agregarNodo(Nodo<T> *raiz, T info)
{
    
  Nodo<T>* nuevoNodo;
  bool bandera;
  Nodo<T>* auxiliar;
  Nodo<T>* hijo;

  
  nuevoNodo = new Nodo<T>(info);

 
  if (nuevoNodo == nullptr){
    bandera = false;
    } else {
    bandera = true;
    }
    
    if (bandera == true){
        if (raiz == nullptr){       
        raiz = nuevoNodo;
        } else {
            auxiliar = nuevoNodo;
            while (!esHoja(auxiliar)){
                if (nuevoNodo->obtieneInformacion() < auxiliar->obtieneInformacion()){      
                    hijo = auxiliar->obtieneIzquierda();
                    if(hijo==nullptr){
                      auxiliar->asignaIzquierda(nuevoNodo);
                    }
                } else {
                    hijo = auxiliar->obtieneDerecha();
                    if (hijo == nullptr){
                        auxiliar->asignaDerecha(nuevoNodo);
                    }
                  }
                hijo = auxiliar;
            }
                  if (auxiliar != nullptr){
        if (nuevoNodo->obtieneInformacion() < auxiliar->obtieneInformacion()){
          auxiliar->asignaIzquierda(nuevoNodo);
        } else {
          auxiliar->asignaDerecha(nuevoNodo);
          }
      }
          }
    }
      
  return bandera;
}
template <class T>
void Arbol<T>:: recorridoPostOrden(Nodo<T>* nodito){
    if (nodito!=nullptr) {
        recorridoPostOrden(nodito->obtenerIzquierda());
        recorridoPostOrden(nodito->obtenerDerecha());
        nodito->obtieneInformacion();
    }
}
template <typename T>
Nodo<T>* Arbol<T>::Sucesor(Nodo<T>* nodito)
{
  Nodo<T>* auxiliar = nodito;
  if (auxiliar!=nullptr){
    auxiliar=auxiliar->obtieneDerecha();
    if(auxiliar != nullptr){
      while (auxiliar->obtieneIzquierda()!= nullptr){
        auxiliar=auxiliar->obtieneIzquierda();
      }
    }
  }
  return auxiliar;
}
template <typename T>
inline bool Arbol<T>::borrarNodo(T info)
{
  Nodo<T>* auxiliar;
  bool bandera;
  Nodo<T>* padre;
  Nodo<T>* hijo_izq;
  Nodo<T>* hijo_der;
  Nodo<T>* predecesor;
  T infoPredecesor;
  int cantHijos;
  raiz = auxiliar;

  if (auxiliar == nullptr)
  {
    bandera = false;
  }
  else
  {
    while (auxiliar != nullptr && auxiliar->obtieneInformacion() != info)
      {
        if (info < auxiliar->obtieneInformacion())
        {
          auxiliar = auxiliar->obtieneIzquierda();
        }
        else 
        {
          auxiliar = auxiliar->obtieneDerecha();  
        }
      }
    if (auxiliar == nullptr)
    {
      bandera = false;
    }
    else 
    {
      hijo_izq = auxiliar->obtieneIzquierda();
      hijo_der = auxiliar->obtieneDerecha();
      cantHijos = auxiliar->cantidadHijos();
      if (cantHijos == 0)
      {
        padre = padre(info);
        if (padre == nullptr)
        {
          delete raiz;
          raiz = nullptr;
        }
        else 
        {
          if (auxiliar->obtieneInformacion() < padre->obtieneInformacion())
          {
            padre->asignaIzquierda(nullptr);
          }
          else 
          {
            padre->asignaDerecha(nullptr);
          }
          delete auxiliar;
        }
      }
      if (cantHijos == 1)
      {
        padre = padre(info);
        if (padre == nullptr)
        {
          delete raiz;
          if (hijo_izq == nullptr)
          {
            raiz = hijo_der;
          }
          else 
          {
            raiz = hijo_izq;
          }
        }
        else
          {
            if (info < padre->obtieneInformacion())
            {
              if (hijo_izq == nullptr)
              {
                padre->asignaIzquierda(hijo_der);
              }
              else 
              {
                padre->asignaIzquierda(hijo_izq);
              }
            }
            else 
            {
              if (hijo_izq == nullptr)
              {
                padre->asignaDerecha(hijo_der);
              }
              else 
              {
                padre->asignaDerecha(hijo_izq);
              }
              delete auxiliar;
            }
          } 
      }
      if (cantHijos == 2)
      {
        predecesor = predecesor(auxiliar);
        infoPredecesor = predecesor->obtieneInformacion();
        borrarNodo(predecesor);
        auxiliar->asignaInformacion(infoPredecesor);
      }
    }
  }
}

template <typename T>
inline void Arbol<T>::recorridoPreOrden(Nodo<T> *nodito)
{
      if (nodito!=nullptr){
        visitaNodo(nodito);
        recorridoPreOrden(nodito->obtieneIzquierda());
        recorridoPreOrden(nodito->obtieneDerecha());
    }
}


template <typename T>
void Arbol<T>::recorrerArbol(Nodo<T>* nodo) {
  string answ;
  if(!esHoja(nodo)){
    string pregunta=nodo->obtieneInformacion();
    cout<<pregunta.substr(0,pregunta.find("."))<<"?";
    cin>>answ;
    if(answ==pregunta.substr(pregunta.find(".")+1)){
      recorrerArbol(nodo->obtieneIzquierda());
    }else{
      recorrerArbol(nodo->obtieneDerecha());
    }
  }else{
    cout<<"Respuesta: "<<nodo->obtieneInformacion()<<endl;
  }
    
}

template <typename T>
inline void Arbol<T>::cargardatosArbol(string nombrearchivo)
{
  ifstream abrirArchivo;
  string recorrido;
  Pila<T> pila;
  abrirArchivo.open(nombrearchivo);
  abrirArchivo >> recorrido;
  if(recorrido=="Preorden"){
    preOrden(raiz,abrirArchivo);
  }else if(recorrido=="Postorden"){
    while(!abrirArchivo.eof()){
      string llenarpila;
      abrirArchivo>>llenarpila;
      pila.mete(llenarpila);
    }
    postOrden(pila, raiz);
  }else if(recorrido=="Inorden"){
    cout<<"Error no es posible el inorden"<<endl;
  }
  
}

template <typename T>
 void Arbol<T>::preOrden(Nodo<T>* &nodo, ifstream& archivo){
    string linea;
    archivo>>linea;
    Nodo<T>* auxiliar1,*auxiliar2;
      if(linea!="Nulo"){
        nodo= new Nodo<T>(linea);
        nodo->asignaInformacion(linea);
        preOrden(auxiliar1, archivo);
        preOrden(auxiliar2, archivo);
        nodo->asignaIzquierda(auxiliar1);
        nodo->asignaDerecha(auxiliar2);
      }else if(linea=="Nulo"){
        nodo=nullptr;
      }

  }
template <typename T>
 void Arbol<T>::postOrden(Pila<T> &pilaa, Nodo<T>* &nodo){
    Nodo<T>* auxiliar1,*auxiliar2;
    string tope=pilaa.tope();
    if(!pilaa.estaVaciaP()){
      if(tope!="Nulo"){
        cout<<pilaa.tope()<<endl;
        nodo= new Nodo<T>(tope);
        nodo->asignaInformacion(tope);
        pilaa.saca();
        postOrden(pilaa, auxiliar1);
        postOrden(pilaa, auxiliar2);
        nodo->asignaDerecha(auxiliar1);
        nodo->asignaIzquierda(auxiliar2);
      }else if(tope=="Nulo"){
        nodo=nullptr;
        pilaa.saca();
      }

        }


  }

#endif