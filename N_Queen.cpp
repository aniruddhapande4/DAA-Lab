#include<bits/stdc++.h>
using namespace std;

int placeQueens(int i, vector<int> &cols, vector<int> &leftDiagonal, vector<int> &rightDiagonal, vector<int> &cur){
    int n=cols.size();
    if(i==n) return 1;
    for(int j=0;j<n;j++){
        if(cols[j] || rightDiagonal[i+j] || leftDiagonal[i-j+n-1]) continue;
        cols[j]=1;
        rightDiagonal[i+j]=1; 
        leftDiagonal[i-j+n-1]=1;
        cur.push_back(j);
        if(placeQueens(i+1,cols,leftDiagonal,rightDiagonal,cur)) return 1;
        cur.pop_back();
        cols[j]=0;
        rightDiagonal[i+j]=0; 
        leftDiagonal[i-j+n-1]=0;        
    }
    return 0;
}

vector<int> nQueen(int n){
    vector<int> cols(n,0);
    vector<int> leftDiagonal(n*2,0);
    vector<int> rightDiagonal(n*2,0);
    vector<int> cur;
    if(placeQueens(0,cols,leftDiagonal,rightDiagonal,cur))return cur;
    else return {-1};
}

void printBoard(vector<int> &solution,int n){
    if(solution[0]==-1){
        cout<<"No solution exists.\n";
        return;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(solution[i]==j) cout<<" Q ";
            else cout<<" . ";
        }
        cout<<"\n";
    }
}

int main(){
    int n;
    cout<<"Enter the size of the board (n): ";
    cin>>n; 
    vector<int> ans=nQueen(n);
    printBoard(ans,n);
    return 0;
}
