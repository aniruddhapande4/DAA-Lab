#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int> arr={1000,11,445,1,330,3000};
    int size=arr.size();
    int maxi=arr[0];
    int mini=arr[0];
    int count=0;
    for(int i=1;i<size;i++){
        maxi=max(maxi,arr[i]);
        mini=min(mini,arr[i]);
        count+=2;
    }
    cout<<"Minimum element is "<<mini<<endl;
    cout<<"Maximum element is "<<maxi<<endl;
    cout<<"Number of Comparisons : "<<count<<endl;
    cout<<"Number of Comparisons (2n-2) : "<<((2*size)-2)<<endl;
    return 0;
}
