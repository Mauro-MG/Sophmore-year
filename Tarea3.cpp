#include <iostream>
#include <string>
using namespace std;
int encontrarbloque(int posicion, int& inicio) {
    int bloque = 0;
    int cont_1 = 0, cont_2 = 0, cont_3 = 0, cont_4 = 0, cont_5 = 0, cont_6 = 0, cont_7 = 0, cont_8 = 0,cont_9=0;
    int final = 0, cont_bloques_pasados=0;

    while (final < posicion) {
        bloque++;
        inicio = final + 1;
        if (bloque <= 9) {
            final = final + bloque;
            cont_1=++cont_bloques_pasados;
        } else if (bloque >= 10 && bloque <= 99) {
            cont_2=++cont_bloques_pasados;
            final = final + bloque * 2 - cont_1;
        } else if (bloque >= 100 && bloque <= 999) {
            cont_3=++cont_bloques_pasados;
            final = final + bloque * 3 - (cont_1+cont_2); 
        } else if (bloque >= 1000 && bloque <= 9999) {
            cont_4=++cont_bloques_pasados;
            final = final + bloque * 4 - (cont_1+cont_2+cont_3); 
        } else if (bloque >= 10000 && bloque <= 99999) {
            cont_5=++cont_bloques_pasados;
            final = final + bloque * 5 - (cont_1+cont_2+cont_3+cont_4);
        } else if (bloque >= 100000 && bloque <= 999999) {
            cont_6=++cont_bloques_pasados;
            final = final + bloque * 6 - (cont_1+cont_2+cont_3+cont_4+cont_5); 
        } 
    }

    return bloque;

}


int encontrarDigito(int posicion, int bloque, int inicio){
int ubicacion=0,digito=0;
string j;
for (int i=1; i<=bloque;i++){
  j+=to_string(i);

}

ubicacion=posicion-inicio;

digito=stoi(j.substr(ubicacion,1));

return digito;

}

int main() {
    int inicio=0, casos=0, bloque=0, i=0,x=0;
    cin>>casos;
    for(int k=0; k<casos;k++){
        cin>>i;
        bloque = encontrarbloque(i,inicio);
        cout<<encontrarDigito(i,bloque,inicio)<<endl;
    }

    return 0;
}
/* Mauro Montelongo Gallegos #595821
   Jose Humberto Moreno Fernandez #596055
Damos nuestra palabra que hemos realizado esta actividad con integridad academica    */