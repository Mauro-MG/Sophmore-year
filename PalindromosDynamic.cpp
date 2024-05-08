#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
map<string,int> M;

bool esPlaindromo(string& s){
    int l=s.length();
    for(int i=0; i<l/2; i++){
        if(s[i]!=s[l-i-1]){
            return false;
        }
    }
    return true;
}
int palindormo(string s){
    int p;
    if(esPlaindromo(s)){
        return 1;

    }
    if(M.find(s)!=M.end()){
        return M[s];
    }
    int pm=2000;
    for (int i=1;i<s.size();i++){
        string s1=s.substr(0,i);
        if(esPlaindromo(s1)){
            p=palindormo(s1)+palindormo(s.substr(i,s.size()-i));
            pm=min(pm,p);
        }
        

    }
    M[s]=pm;
    return pm;
}

int main(){
    int casos;
    string pali;
    cin>>casos;
    for (int i=0;i<casos;i++){
        M.clear();
        cin>>pali;
        cout<<palindormo(pali)<<endl;
    }

    return 0;
}