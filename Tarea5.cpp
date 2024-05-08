#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
int reinas_iguales( vector<vector<int>>& m1, vector<vector<int>>& m2){
    int reinasiguales=0;
    for( int i=0; i<m1.size(); i++){
        for( int j=0; j<m1.size(); j++){
            if( m1[i][j]==1&&m2[i][j]==1){
                reinasiguales++;
            }
        }
    }
    return reinasiguales;
}
bool sePuedeColocar(int f, int c, vector<vector<int>>& M)
{
  for(int i=0;i<c;i++) //evalua la fila
   if(M[f][i]==1)
     return false;
  for(int i=1;f-i>=0 && c-i>=0;i++) //Diagonal arriba
   if(M[f-i][c-i]==1)
     return false;
  for(int i=1;f+i<M.size() && c-i>=0;i++){ //Diagonal abajo
   if(M[f+i][c-i]==1)
     return false;}
  return true;
}

bool reinasmov(int col,vector<vector<int>>& M)
{
    if(col>=M.size()){
        return true;
    }
    
    for (int fil=0;fil<M.size();fil++){

        if(sePuedeColocar(fil,col,M)){
            M[fil][col]=1; 

            if (reinasmov(col+1,M)){
                return true;
            }else{
                M[fil][col]=0;
            }
        }else{
            M[fil][col]=0;
        }
   }
   return false;
}


int main() {
    int n;
    do  {
        cin >> n;
        if (n == 0){
            break;
        } 
        vector<vector<int>> M(n, vector<int>(n, 0)), aux(n,vector<int>(n,0));
        vector<int> reinas(n,0);
        for (int i = 0; i < n; ++i) {
            cin >> reinas[i];
        }

        for(int j=0; j < n; ++j) {
            int fil=reinas[j]-1;
            M[fil][j]=1;
            aux[fil][j]=1;
        }
        reinasmov(0,M);

        cout<<n-reinas_iguales(M,aux)<<endl;
      

}while(n!=0);
 return 0;
}

/*
  Mauro Montelongo Gallegos 595821
 Jose Humberto Moreno Fernandez 596055

Damos nuestra palabra que hemos realizado esta actividad con integridad académica
*/