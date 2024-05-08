#include <iostream>
using namespace std;
#include <string>
int sacargrados(int arreglo[]){
    int acum=0;
    if(arreglo[0]>arreglo[1]){
        acum+=(arreglo[0]-arreglo[1])*9;
    }else if(arreglo[0]<arreglo[1]){
        acum+=(arreglo[0]+40-arreglo[1])*9;
    }
    if(arreglo[1]>arreglo[2]){
        acum+=(arreglo[2]+40-arreglo[1])*9;
    }else if(arreglo[1]<arreglo[2]){
        acum+=(arreglo[2]-arreglo[1])*9;
    }
    if(arreglo[2]>arreglo[3]){
        acum+=(arreglo[3]+40-arreglo[2])*9;
    }else if(arreglo[2]<arreglo[3]){
        acum+=(arreglo[2]+40-arreglo[3])*9;
    }
    return acum+1080;
}
int main() {
    int arr[4],i=1;

    while(arr[0]!=0||arr[1]!=0||arr[2]!=0||arr[3]!=0) {
        cout<<"Caso "<<i<<": ";
        cin>>arr[0]>>arr[1]>>arr[2]>>arr[3];
        if(arr[0]==0&&arr[1]==0&&arr[2]==0&&arr[3]==0){
            break;
        }
        int grados=sacargrados(arr);
        cout<<grados<<endl;
        i++;
    }   

    return 0;
}
/* Mauro Montelongo Gallegos #595821
   Jose Humberto Moreno Fernandez #596055
Damos nuestra palabra que hemos realizado esta actividad con integridad academica    */
