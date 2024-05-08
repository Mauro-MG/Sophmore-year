#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int S[9][9];
vector<bool> numeros(9,false);
bool  SolveSudoku (){
    bool encontrado=false;
    int f,c;
    for( f=0;f<9&&!encontrado;f++){
        for( c=0;c<9&&!encontrado;c++){
            if(S[f][c]==0){
                encontrado=true;
                
            }
        }
    }
    if(!encontrado){
        return true;
    }
    f--;
    c--;
    for(int i=0;i<9;i++){
        if(S[f][i]>0){
            numeros[S[f][i]]=true;
        }
        if(S[i][c]>0){
            numeros[S[i][c]]=true;
        }

    }
    int x=(int)(c/3)*3,y=(int)(f/3)*3;
    for(int i=x;i<x+3;i++){
        for(int j=y;i<y+3;j++){
            if(S[j][i]>0){
            numeros[S[j][i]]=true;
            }
        }


    }
    for(int i=0;i<9;i++){
        if(numeros[i]==false){
            cout<<i<<" , ";
        }
    }
    return true;

}

int main(){
    int casos;
    char N;
    cin>>casos;
    for(int k=0;k<casos;k++){

        for(int f=0;f<9;f++){
            for(int c=0;c<9;c++){
                cin>>N;
                S[f][c]=N-'0';
                cout<<S[f][c]<<" ";
            }
        }
        SolveSudoku();
    }

}