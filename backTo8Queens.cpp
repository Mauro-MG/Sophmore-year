#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <sstream>


using namespace std;

#define FOR( i, L, U ) for(int i=(int)L ; i<=(int)U ; i++ )
#define FORD( i, U, L ) for(int i=(int)U ; i>=(int)L ; i-- )
#define SQR(x) ((x)*(x))

#define INF INT_MAX


#define READ(filename)  freopen(filename, "r", stdin);
#define WRITE(filename)  freopen(filename, "w", stdout);

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<char> vc;
typedef vector<string> vs;
typedef vector<vector<int> > vvi;
typedef vector<vector<int> > vvc;
typedef map<int, int> mii;
typedef map<string, int> msi;
typedef map<int, string> mis;
typedef map<string, string> mss;
typedef map<string, char> msc;

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define N 9
int t[N];
int n[N];
int mn;
bool isPromising(int r,int c){
    for(int i=1;i<c;i++)if(r==n[i]||abs(r-n[i])==abs(c-i))return false;
    return true;
}
void NQueen(int col){
    for(int i=1;i<9;i++){
        if(isPromising(i,col)){
            n[col]=i;
            if(col==8){
                int newmin = 0;
                for(int j=1;j<9;j++){
                newmin +=(t[j]!=n[j]);
                }

                mn = min(mn,newmin);
            }
            else NQueen(col+1);
        }
    }
}
int main()
{
    int cs=1;
    READ("input.txt");
    WRITE("output.txt");
    while(scanf("%d %d %d %d %d %d %d %d", &t[1],&t[2],&t[3],&t[4],&t[5],&t[6],&t[7],&t[8])==8){
        mn=INF;
        NQueen(1);
        printf("Case %d: %d\n",cs++,mn);
    }
	return 0;
}