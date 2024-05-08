#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int M[8][8];
int soluciones=0;
int solucion[8][8];
bool primeraSolucionEncontrada = false;
int movimientosAgregarReina = 0;
int movimientosQuitarReina = 0;

bool sePuedeColocar(int f, int c)
{
  for(int i=0;i<c;i++) //evalua la fila
   if(M[f][i]==1)
     return false;
  for(int i=1;f-i>=0 && c-i>=0;i++) //Diagonal arriba
   if(M[f-i][c-i]==1)
     return false;
  for(int i=1;f+i<8 && c-i>=0;i++){ //Diagonal abajo
   if(M[f+i][c-i]==1)
     return false;}
  movimientosAgregarReina++;   
  return true;
}

void reinas(int col)
{
  if(col==8)
  {
   soluciones++;
   if(!primeraSolucionEncontrada){
    for (int f = 0; f < 8; f++) {
      for (int c = 0; c < 8; c++) {
        solucion[f][c] = M[f][c];
      }
    }
    primeraSolucionEncontrada=true;
   }
   
   return;
  }
  for(int fil=0;fil<8;fil++)
  {
   if(sePuedeColocar(fil,col))
   {
     M[fil][col]=1; //Poner reina
     reinas(col+1);
     //else
     M[fil][col]=0; //Quitar reina
     movimientosQuitarReina++;
   }
  }
  return; //false;
}

int main() {
  reinas(0);
  for (int f = 0; f < 8; f++) {
    for (int c = 0; c < 8; c++) {
      if (solucion[f][c] == 1) {
        cout << "[R]";
      } else {
        cout << "[ ]";
      }
    }
    cout << endl;
  }
  cout<<movimientosAgregarReina<<endl;
  cout<<movimientosQuitarReina<<endl;

}