#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define MAX 1000000
vector<int> P; //{2,3,5,7...}
vector<int> S;

int NOD(int n)
{
   int i=0;
   int contador=0, nd=1;
   while(n>1)
   {
      if(n%P[i]==0)
      {
         n=n/P[i];     
         contador++;
      }
      else
      {
         i++;
         nd = nd * (contador+1);
         contador=0;
      }
   }
   nd = nd * (contador+1);
   return nd;
}

int main() {
   //primos
   for(int n=2;n<MAX;n++)
   {
      bool primo=true;
      for(int i=2;primo && i<=sqrt(n);i++)
         if(n%i==0)
            primo=false;
      if(primo)
         P.push_back(n);
   }

   S.push_back(1);
   for(int i=1;S.back()<=MAX;i++)
      S.push_back(S[i-1]+NOD(S[i-1]));

   int A=3000,B=4000;
   vector<int>::iterator itB,itA;
   itA=lower_bound(S.begin(),S.end(),A);
   itB=upper_bound(itA,S.end(),B);
   cout<<itB-itA;
}