#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include "Vertice.h"
#include "Pila.h"
using namespace std;
template <typename T>
class Grafo{
    public:
    bool insertaVertice(T info);
    bool insertaArco(int origen, int destino);
    bool borraVertice(int posicion);
    bool borraArco(int origen, int posicion);
    void recorridoAnchura();
    void recorridoProfundidad();
    void despliegaInformacion();



    private:
    ListaEncadenada<Vertice<T>> listaVertices;

};



template <typename T>
inline bool Grafo<T>::insertaVertice(T info)
{
    bool bandera;
    Vertice<T> auxiliar(info);
    bandera=listaVertices.insertarElementoFinal(auxiliar);
    return bandera;
}

    template <typename T>
    inline bool Grafo<T>::insertaArco(int origen, int destino)
    {
        Vertice<T>* auxiliar=nullptr;
        bool bandera;
        int tamanio;
        ListaEncadenada<int>* ady;
        tamanio=listaVertices.tamanio();
        if((origen<=tamanio)&&(destino<=tamanio)&&(tamanio!=0)){
            auxiliar=listaVertices.obtenerElementoEnPosicion(origen);
            ady=auxiliar->traeAdyacencias();
            bandera=ady->insertarElementoFinal(destino);
        }else{
            bandera=false;
        }
        return bandera;
    }

template <typename T>
inline bool Grafo<T>::borraVertice(int posicion)
{
    bool bandera;
    int tamanio;
    tamanio= listaVertices.tamanio();
    if(posicion<=tamanio){
        bandera=true;
        listaVertices.borrarElemento(posicion);
    }
    else{
        bandera=false;
    }
    return bandera;
}

template <typename T>
inline bool Grafo<T>::borraArco(int origen, int posicion)
{
    Vertice<T> auxiliar;
    bool bandera;
    int tamanio;
    ListaEncadenada<T>* ady;
    tamanio=listaVertices.tamanio();
    if((origen <= tamanio) && (posicion <= tamanio) && (tamanio != 0)){
        auxiliar=listaVertices.obtenerElementoEnPosicion(origen);
        ady=auxiliar->traeAdyacencias();
        bandera=ady->borrarElemento(posicion);
    }else{
        bandera=false;
    }
    return bandera;
}

template <typename T>
inline void Grafo<T>::recorridoAnchura()
{

    Vertice<T> *nodo, *vecino, *nodito;
    ListaEncadenada<Vertice<T>*> fila;  
    ListaEncadenada<int>* adyacencias;
    for(int i=0;i<listaVertices.tamanio();i++){
        listaVertices.obtenerElementoEnPosicion(i)->asignaEstado(0);
    }
    for(int j=0;j<listaVertices.tamanio();j++){
        nodo=listaVertices.obtenerElementoEnPosicion(j);
        if(nodo->traeEstado()==0){
        fila.insertarElementoFinal(nodo);
        while(!fila.estaVacia()){
            nodito=*fila.traerDatosInicio();
            cout<<nodito->traeInformacion()<<endl;
            fila.borrarElementoInicio();
            nodito->asignaEstado(1);
            adyacencias= nodito->traeAdyacencias();
            for(int k=0;k<adyacencias->tamanio();k++){
                vecino=listaVertices.obtenerElementoEnPosicion(*adyacencias->obtenerElementoEnPosicion(k));
                if(vecino->traeEstado()==0){
                fila.insertarElementoFinal(vecino);
                vecino->asignaEstado(2);
                vecino=listaVertices.obtenerElementoEnPosicion(*adyacencias->obtenerElementoEnPosicion(k));
                }
            }
            
                    
        }
        

        }
            
    }
}

template <typename T>
inline void Grafo<T>::recorridoProfundidad()
{
    Vertice<T> *nodo, *vecino, *nodito;
    ListaEncadenada<Vertice<T>*> pila;  
    ListaEncadenada<int>* adyacencias;
    for(int p=0;p<listaVertices.tamanio();p++){
        listaVertices.obtenerElementoEnPosicion(p)->asignaEstado(0);
    }
    for(int j=0;j<listaVertices.tamanio();j++){
        nodo=listaVertices.obtenerElementoEnPosicion(j);
        if(nodo->traeEstado()==0){
        pila.insertarElementoInicio(nodo);
        while(!pila.estaVacia()){
            nodito=*pila.traerDatosInicio();
            if(nodito->traeEstado()==1){
                pila.borrarElementoInicio();
            }
            if(nodo->traeEstado()==1&&nodito->traeEstado()==0){
                if(nodito->traeEstado()!=1){
                    cout<<nodito->traeInformacion()<<endl;
                }
                pila.borrarElementoInicio();
                nodito->asignaEstado(1);
                adyacencias=nodito->traeAdyacencias();
                for(int k=0;k<adyacencias->tamanio();k++){
                    vecino=listaVertices.obtenerElementoEnPosicion(*adyacencias->obtenerElementoEnPosicion(k));
                    if(vecino->traeEstado()==0){
                        pila.insertarElementoInicio(vecino);
                }
            }
        }
            if(nodo->traeEstado()==0){
            pila.borrarElementoInicio();
            cout<<nodo->traeInformacion()<<endl;
            nodo->asignaEstado(1);
            adyacencias=nodo->traeAdyacencias();
            for(int k=0;k<adyacencias->tamanio();k++){
                vecino=listaVertices.obtenerElementoEnPosicion(*adyacencias->obtenerElementoEnPosicion(k));
                if(vecino->traeEstado()==0){
                pila.insertarElementoInicio(vecino);
                }
            }
        }
        }
        
        }
    }

}

template <typename T>
inline void Grafo<T>::despliegaInformacion()
{
    Vertice<T>* auxiliar;
    int tamanio;
    ListaEncadenada<int>* ady;
    int tamAdy;
    tamanio=listaVertices.tamanio();
    for(int i=0;i<tamanio;i++){
        auxiliar=*listaVertices.obtenerElementoEnPosicion(i);
        cout<<"Informacion del vertice "<<i+1<<auxiliar.traeInformacion()<<endl;
        ady=auxiliar.traeAdyacencias();
        tamAdy=ady->tamanio();
        for(int j=1;j<tamAdy;j++){
            cout<<"Arco con vertice no "<<(ady->obtenerElementoEnPosicion(j))<<endl;
        }

    }

}

#endif