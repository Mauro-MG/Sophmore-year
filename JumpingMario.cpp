#include <iostream>
using namespace std;

int main(){
    int hj=0, lj=0, ns=8, saltos[50];
    for(int i=0; i<ns;i++){
        cin>>saltos[i];
    }

    for(int j=0; j<ns; j++){
        if(saltos[j]>saltos[j+1]){
            hj++;
        }else if(saltos[j]<saltos[j+1]){
            lj++;
        }
    }
    cout<<hj<<" "<<lj<<endl;
    return 0;
}