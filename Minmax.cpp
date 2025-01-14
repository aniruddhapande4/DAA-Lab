#include <bits/stdc++.h>
using namespace std;

pair<int,int> findminmax(vector<int> &arr,int low,int high,pair<int,int> minmax){
    int mid;
    if(low==high) {
        minmax.first=arr[low];
        minmax.second=arr[low];
        return minmax;
    }
    if(high==low + 1){
        if(arr[low]>arr[high]) {
            minmax.second=arr[low];
            minmax.first=arr[high];
        }
        else{
            minmax.second=arr[high];
            minmax.first=arr[low];
        }
        return minmax;
    }
    mid=(low+high)/2;
    pair<int,int> temp1=findminmax(arr,low,mid,minmax);
    pair<int,int> temp2=findminmax(arr,mid+1,high,minmax);
    if(temp1.first<temp2.first) minmax.first=temp1.first;
    else minmax.first=temp2.first;
    if(temp1.second>temp2.second) minmax.second=temp1.second;
    else minmax.second=temp2.second;
    return minmax;
}

int main(){
    vector<int> arr={1000,11,445,1,330,3000};
    int size=arr.size();
    pair<int,int> ans=findminmax(arr,0,size-1,{0,0});
    cout<<"Minimum element is "<<ans.first<<endl;
    cout<<"Maximum element is "<<ans.second<<endl;
    return 0;
}