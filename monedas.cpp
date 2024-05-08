#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

void cambio(int M[], int S[], int cantidad){
    for(size_t i=4; i >=0&&cantidad==0;i--){

        int moneda=M[i];
        if(cantidad<moneda){
            continue;
        }
        S[i]=cantidad/moneda;
        cantidad-=S[i]*moneda;
    }


}

int main(){
    int M[5]={1,2,5,10,20};
    int S[5]={0,0,0,0,0};
    int cantidad;
    cin>>cantidad;
    cambio(M,S, cantidad);
    for(int i=0;i<5;i++){
        if(S[i]!=0){
            cout<<"Dar "<<S[i]<<" monedas de "<<M[i]<<endl;
        }
    }

    return 0;
}