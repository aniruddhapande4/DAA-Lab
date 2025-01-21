#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int> arr={1000,11,445,1,330,3000};
    int size=arr.size();
    int maxi=INT_MIN;
    int mini=INT_MAX;
    for(auto &val:arr){
        maxi=max(maxi,val);
        mini=min(mini,val);
    }
    cout<<"Minimum element is "<<mini<<endl;
    cout<<"Maximum element is "<<maxi<<endl;
    return 0;
}