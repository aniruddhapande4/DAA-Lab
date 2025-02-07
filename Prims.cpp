#include<bits/stdc++.h>
using namespace std;

void spanningTree(int V, int E, vector<vector<int>> &edges) {
    vector<vector<int>> adj[V];
    for(int i=0;i<E;i++){
        int u=edges[i][0];
        int v=edges[i][1];
        int wt=edges[i][2];
        adj[u].push_back({v,wt});
        adj[v].push_back({u,wt});
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<bool> visited(V,false);
    int res=0;
    pq.push({0,0});
    vector<pair<int,int>> mstEdges;
    while(!pq.empty()){
        auto p=pq.top();
        pq.pop();
        int wt=p.first;  
        int u=p.second;  
        if(visited[u]==true){
            continue;  
        }
        res+=wt; 
        visited[u]=true;  
        for(auto v:adj[u]){
            if(visited[v[0]]==false){
                pq.push({v[1],v[0]});
                mstEdges.push_back({u,v[0]});
            }
        }
    }
    cout<<"Edges in the Minimum Spanning Tree:\n";
    for(auto &edge:mstEdges) {
        cout<<"("<<edge.first <<", "<<edge.second<<")\n";
    }
    cout<<"Total weight of the Minimum Spanning Tree: "<<res<<endl; 
}

int main(){
    int V,E;
    cout<<"Enter the number of vertices: ";
    cin>>V;
    cout<<"Enter the number of edges: ";
    cin>>E;
    vector<vector<int>> edges(E, vector<int>(3));
    cout<<"Enter the edges (u v wt):\n";
    for(int i=0;i<E;i++){
        cin>>edges[i][0]>>edges[i][1]>>edges[i][2];
    }
    spanningTree(V, E, edges);
    return 0;
}