#include <iostream>
using namespace std;
#include "ListaEncadenada.h"
int ordenarAretes(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  int i = 0;
  for (int j = 1; j < n; j++) {
    if (arr[i] != arr[j]) {
      arr[++i] = arr[j];
    }
  }

  return i + 1; 
}
int main(){
    int casos,cant_aretes=0,arete,p1,p2,contarets=0,arr[100],c=0,size=0,n=0;
    ListaEncadenada<int> n_aretes;
    cin>>casos;
    for(int i=0;i<casos;i++){
        cin>>cant_aretes;
        for(int j=0;j<cant_aretes;j++){
            cin>>arete;
            n_aretes.insertarElementoInicio(arete);
        }
        for(int k=0;k<n_aretes.tamanio();k++){
            p1=n_aretes.obtenerElementoEnPosicion(k);
            
            for(int n=0;n<n_aretes.tamanio();n++){
                p2=n_aretes.obtenerElementoEnPosicion(n);
                if(p1==p2){
                    contarets++;
                    
                }    

            }
            if(contarets>1&&contarets%2==0){
                    c++;
                    
            }else if(contarets>1&&contarets%2!=0){
                c++;
                arr[k]=p1;
                n++;
            }else if(contarets=1||contarets%2!=0){
                arr[k]=p1;
                n++;
            }
            contarets=0;
        }
        while(!n_aretes.estaVacia()){
          n_aretes.borrarElementoFinal();
        }
    }
    if(n==0){
        cout<<":)"<<endl;
    }else {
      size=ordenarAretes(arr,n);
      for (int i = 0; i < size-1; i++) {
         cout << arr[i] << " ";
         }
    }
    cout<<endl;
    if(c%2==0){
        cout<<c<<endl;
    }else{
        cout<<c-1<<endl;
    }
    
    return 0;
}