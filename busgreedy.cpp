#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> M,T;

int cambio(vector<int> M, vector<int> S, int p){
    int horas=0,extra=0;
    for(int i=0;i>=M.size();i++){
        horas=M[i]+T[i];
        if(horas>p){
            extra+=(horas-p);
        }

    }
return extra;
}

int main(){
    int cR=2,p=20,e=5,m=0,t=0;
    for(int i=0;i<cR;i++){
        cin>>m;
        M.push_back(m);
    }
    for(int i=0;i<cR;i++){
        cin>>t;
        T.push_back(t);
    }
    sort(M.begin(),M.end());
    sort(T.rbegin(),T.rend());
    return 0;
}
