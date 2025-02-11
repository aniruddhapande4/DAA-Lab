#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> profit={1,2,5,6};
    vector<int> weight={2,3,4,5};
    int W=8;

    int n=weight.size();
    vector<vector<int>> dp(n+1,vector<int>(W+1));

    for(int i=0;i<=n;i++){
        for(int w=0;w<=W;w++){
            if(i==0 || w==0) dp[i][w]=0;
            else if(weight[i-1]<=w) dp[i][w]=max(profit[i-1]+dp[i-1][w-weight[i-1]],dp[i-1][w]);
            else dp[i][w]=dp[i-1][w];
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=W;j++){
            cout<<dp[i][j]<<"\t";
        }
        cout<<endl;
    }
    return 0;
}
