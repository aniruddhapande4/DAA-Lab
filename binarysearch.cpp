#include<bits/stdc++.h>
#include <random>
using namespace std;

void binarysearch(vector<int> &arr,int &target){
    bool flag=false;
    int low=0,high=arr.size()-1,mid;
    while(low<=high){
        mid=low+((high-low)/2);
        if(arr[mid]==target){
            flag=true;
            break;
        }
        else if(target>arr[mid]){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    if(flag) cout<<"Found the Number"<<endl;
    else cout<<"Number Not Found"<<endl;
}

int main(){
    srand(time(NULL));
    int p=rand()%7;
    long long len=1;
    for(int i=0;i<p;i++) len*=10;
    cout<<"The Length of the Array is : "<<len<<endl;
    vector<int> arr(len);
    for(int i=0;i<len;i++){
        int temp=rand()%len;
        arr[i]=temp;
    }
    sort(arr.begin(),arr.end());
    for(auto &val:arr){
        cout<<val<<" ";
    }
    int target;
    cout<<endl<<"Enter the Number to Find : ";
    cin>>target;
    binarysearch(arr,target);
    for(auto &val:arr){
        cout<<val<<" ";
    }
    return 0;
}