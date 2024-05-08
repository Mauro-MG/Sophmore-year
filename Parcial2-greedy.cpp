#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> H={25,26,12,18,6,30,15};
vector<int> M={30,5,90,81,22,40,41,30};
vector<int> diffe;

void casamientos(vector<int>& M, vector<int>& H){
    sort(H.rbegin(),H.rend());
    sort(M.begin(),M.end());
    int m=M.size();
    vector<int>::iterator itB,itA;
        for (int i = 0; i < m; i++) {
    auto it = min_element(M.begin(), M.end(), [h = H[i]](int a, int b) {
        return abs(a - h) < std::abs(b - h);
    });

    M.erase(it);
}

    
}

int main(){
    int tama=M.size();
    int rest=0;
    rest=H.size()-tama;
    casamientos(M,H);
    if(tama-H.size()==0||rest-tama<0){
        cout<<0;
    }
    if(rest-tama>0){
        cout<<H.size()-tama<<" "<<H[H.size()-1]<<endl;
    }
    return 0;
}