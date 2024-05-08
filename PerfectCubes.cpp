#include <iostream>
using namespace std;
#include <cmath>
int main(){
    int a=0,b=0,c=0;
    for(int i=6;i<100;i++){
        for(a=0,b=a+1,c=b+1;(a*a*a+b*b*b+c*c*c)!=i*i*i;a++,b++,c++){
            if(a<b&&b<c&&a<c&&((a*a*a+b*b*b+c*c*c)==i*i*i)){
                cout<<"Cube= "<<i<<" "<<"Triple= "<<a<<" "<<b<<" "<<c<<endl;
        }
    }
}
    return 0;
}
