#include <bits/stdc++.h>
using namespace std;

bool cmpEnd(pair<int,int> a1, pair<int,int> a2) {
    return a1.second<a2.second;
}

bool cmpStart(pair<int,int> a1, pair<int,int> a2) {
    return a1.first<a2.first;
}

void activitySelectionByEndTime(vector<pair<int,int>> activities) {
    sort(activities.begin(),activities.end(),cmpEnd);
    cout<<"Selected Activities (Sorted by End Time):\n";
    int lastSelected=0;
    cout<<"("<<activities[lastSelected].first<<", "<<activities[lastSelected].second<<")\n";
    for(int i=1;i<activities.size();i++){
        if(activities[i].first>=activities[lastSelected].second){
            cout<<"("<<activities[i].first<<", "<<activities[i].second<<")\n";
            lastSelected=i;
        }
    }
    cout<<"\n";
}

void activitySelectionByStartTime(vector<pair<int,int>> activities){
    sort(activities.begin(),activities.end(),cmpStart);
    cout<<"Selected Activities (Sorted by Start Time):\n";
    int lastSelected=0;
    cout<<"("<<activities[lastSelected].first<<", "<<activities[lastSelected].second<<")\n";
    for(int i=1;i<activities.size();i++){
        if(activities[i].first>=activities[lastSelected].second){
            cout<<"("<<activities[i].first<<", "<<activities[i].second<<")\n";
            lastSelected=i;
        }
    }
    cout<<"\n";
}

int main(){
    vector<pair<int,int>> activities = {{1, 3}, {2, 5}, {3, 9}, {6, 8}, {5, 7}, {8, 9}};
    activitySelectionByEndTime(activities);
    activitySelectionByStartTime(activities);
    return 0;
}
