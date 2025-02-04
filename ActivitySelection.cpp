#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int,int> a1,pair<int,int> a2){
    return a1.second<a2.second;
}
void activitySelection(vector<pair<int,int>> &activities){
    sort(activities.begin(),activities.end(),cmp);
    cout<<"Selected Activities:\n";
    int lastSelected=0;
    cout<<"("<<activities[lastSelected].first<<", "<<activities[lastSelected].second<<")\n";
    for(int i=1;i<activities.size();i++){
        if(activities[i].first>=activities[lastSelected].second){
            cout<<"("<<activities[i].first<<", "<<activities[i].second<<")\n";
            lastSelected=i;
        }
    }
}

int main() {
    vector<pair<int,int>> activities={{1, 3},{2, 5},{3, 9},{6, 8},{5, 7},{8, 9}};
    activitySelection(activities);
    return 0;
}