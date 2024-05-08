#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>>  caminos(20,vector<int>(-1));

int CM(vector<vector<int>>& M, int cInicial, int cFinal){
    if(M[cInicial]==M[cFinal]){
        return 0;
    }else{
        for(int i=cFinal-1;i>0;i--){
            for(int j=cFinal-1;j>0;j--){
                if(M[i][j]!=0){
                    M[i][j]+CM(M,1,i);

                }
        }
        }
    }
}
int main(){
    int a,b,c,numAristas,nodos,CI,CF;
    cin>>nodos>>numAristas;
    vector<vector<int> > M(nodos,vector<int>(0));
    for(int i=0;i<numAristas;i++){
        cin>>a>>b>>c;
        M[a][b]=c;
    }
    for(int i=0;i<nodos;i++){
        caminos[i][i]=0;
    }
    CF=M.size();
    CM(M,1,CF);


    return 0;
}
/*
1 2 2
1 3 4
1 4 3
2 5 7
2 6 4
2 7 6
3 5 3
3 6 2
3 7 4
4 5 4
4 6 1
4 7 5
5 8 1
5 9 4
6 8 6
6 9 3
7 8 3
7 9 3
8 10 3
9 10 4
*/