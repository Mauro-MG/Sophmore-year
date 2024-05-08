#include <iostream>
using namespace std;
#include <string>
#include "ListaEncadenada.h"
int posicionFinal(string instr, ListaEncadenada <string> lista){
    int p=0, igualque;
    if(instr=="ADELANTE"){
        return p+=1;
    }else if(instr=="ATRAS"){
        return p-=1;
    }else if(instr.substr(0,9)=="IGUAL QUE"){
        igualque=stoi(instr.substr(10,instr.length()));
        if(igualque<=lista.tamanio()){
         return posicionFinal(lista.obtenerElementoEnPosicion(igualque-1),lista);
        }else{
            cout<<"Error la instruccion "<<lista.encontrarPosicionElemento(instr)<<" es invalida"<<endl;
            return 0;
        }
        

    }
}


int main() {
    ListaEncadenada<string> instrucciones;
    ListaEncadenada<int> lista_valoresp;
    string instruccion;
    int numCasos, numInstr, p=0,tama;
   cout<<"Numero de casos ";
    cin>>numCasos;
    for(int i=0; i<numCasos; i++){
        cout<<"Numero de instrucciones ";
        cin>>numInstr;
        getline(cin,instruccion);
        for(int j=0; j<numInstr; j++){
            getline(cin,instruccion);
            instrucciones.insertarElementoFinal(instruccion);
        }
         tama=instrucciones.tamanio();
        for(int k=0;k<instrucciones.tamanio();k++){
            p+=posicionFinal(instrucciones.obtenerElementoEnPosicion(k),instrucciones);
        }
        lista_valoresp.insertarElementoFinal(p);
        p=0;
        while(!instrucciones.estaVacia()){
            instrucciones.borrarElementoFinal();
        }
    }
    lista_valoresp.desplegarLista();
   
 


    return 0;
}
/* Mauro Montelongo Gallegos #595821
   Jose Humberto Moreno Fernandez #596055
Damos nuestra palabra que hemos realizado esta actividad con integridad academica    */
