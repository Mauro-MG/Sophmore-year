#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    map<int,string> M;
    M[10]="Hola";
    M[110]="CP";
    M[10]="Hola";
    map<int,string>::iterator it;
    for(it=M.begin();it!=M.end();it++){
        cout<<"En "<<it->first<<" hay "<<it->second<<endl;
    }
    return 0;
}