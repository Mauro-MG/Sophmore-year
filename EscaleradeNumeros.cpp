#include <iostream>
using namespace std;
int encuentraCoord(int x, int y){
    if(x%2 == 0){
        if(y+2==x){
            cout<<x<<endl;
        }else{
            if(x==0){
                cout<<x<<endl;
            }else{
            cout<<"nada"<<endl;

            }
        }
    }else{
        if(y+2==x){
            cout<<x<<endl;
        }else{
            cout<<"nada"<<endl;
        }
    }
}
int main(){
    int x,y,n;
    cout<<"Introduzca el numero de casos"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
    cout<<"Introduzca las coordenadas"<<endl;
    cin>>x>>y;
    encuentraCoord(x,y);
    }
    
    return 0;
}