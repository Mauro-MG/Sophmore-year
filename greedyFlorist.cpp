#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int getMinimumCost(int k, vector<int> c) {
    sort(c.begin(), c.end());
    reverse(c.begin(), c.end());
    int sum = 0;
    vector<pair<int,int>> v(k, {1, 0}); 
    
    for (int i = 0; i < k; i++) {
        sum += c[i];
    }
    for (int i = k; i < c.size();) {
        int j = 0;
        while (j < k && i < c.size()) {
            v[j].second = v[j].second + 1;
            sum += (v[j].first + v[j].second) * c[i];
            j++;
            i++;
        }
    }
    return sum;
}
int main() {
    vector<int> c={1,2,3,5,7,8,9};
    int k=3;
    getMinimumCost(k,c);
    
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void casamientos(vector<int>& M, vector<int>& H){
    sort(H.rbegin(), H.rend());
    sort(M.begin(), M.end());
    
    for(int j = 0; j < H.size(); j++){
        auto itB = lower_bound(M.begin(), M.end(), H[j]);
        
        if(itB != M.end()) {
            int diff = abs(*itB - H[j]); 
            cout << "Found match: " << *itB << " from M and " << H[j] << " from H with difference " << diff << endl;
        } else {
            cout << "No suitable match found for " << H[j] << " from H in M" << endl;
        }
    }
}

int main() {
    vector<int> M = {5, 8, 2, 10, 3};
    vector<int> H = {4, 7, 9};

    casamientos(M, H);

    return 0;
}
