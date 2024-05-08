#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool sumaMayor( pair<int,int>& it1, pair<int,int>& it2){
    int suma1=it1.first+it1.second;
    int suma2=it2.first+it2.second;
    return suma1>suma2;
}

int main() {
    int N=1,acum_tiempo = 0,tiempoF = 0,I=0,T=0, acum_trabajo=0,dif=0,difmax=0,aux=0;    
    while ( N != 0) {
        cin >> N;
        vector<pair <int,int>> IT;
        
        for (int i = 0; i < N; i++) {
            cin >> I>>T;
            IT.push_back({I,T});
        }

        sort(IT.begin(), IT.end(),sumaMayor);
        
        for (int j = 0; j < 3; j++) {
             aux=acum_tiempo += IT[j].first; 
        }
        for (int j = 0; j < 3; j++) {
            dif = IT[j].second - (acum_tiempo - IT[j].first); 
            difmax = max(difmax, dif); 
            acum_tiempo-=IT[j].first; 
        }
        if(N!=0){
            tiempoF=aux+difmax;
            cout << tiempoF << endl;
        }
        difmax=0;
        dif=0;
        acum_tiempo = 0;
        tiempoF = 0;
        IT.clear();
    }
    
    return 0;
}
/*
  Mauro Montelongo Gallegos 595821
 Jose Humberto Moreno Fernandez 596055

Damos nuestra palabra que hemos realizado esta actividad con integridad académica
*/