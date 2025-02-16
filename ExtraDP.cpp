#include <bits/stdc++.h>
using namespace std;

void coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    
    for (int c : coins) {
        for (int j = c; j <= amount; j++) {
            if (dp[j - c] != INT_MAX)
                dp[j] = min(dp[j], dp[j - c] + 1);
        }
    }
    
    cout << "Minimum coins required: " << (dp[amount] == INT_MAX ? -1 : dp[amount]) << endl;
}

int matrixChain(vector<int>& p, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + p[i-1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][n-1];
}

const int INF = 1e9;
int tsp(int mask, int pos, vector<vector<int>>& dist, vector<vector<int>>& dp, int n) {
    if (mask == (1 << n) - 1) return dist[pos][0];
    if (dp[mask][pos] != -1) return dp[mask][pos];
    
    int ans = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0)
            ans = min(ans, dist[pos][city] + tsp(mask | (1 << city), city, dist, dp, n));
    }
    return dp[mask][pos] = ans;
}

void floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist = graph;
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    for (auto row : dist) {
        for (int val : row)
            cout << (val == INT_MAX ? "INF" : to_string(val)) << " ";
        cout << endl;
    }
}

int optimalBST(vector<int>& keys, vector<int>& freq, int n) {
    vector<vector<int>> cost(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) cost[i][i] = freq[i];
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;
            int sum = 0;
            for (int k = i; k <= j; k++) sum += freq[k];
            
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r-1] : 0) + ((r < j) ? cost[r+1][j] : 0) + sum;
                cost[i][j] = min(cost[i][j], c);
            }
        }
    }
    return cost[0][n-1];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    coinChange(coins, amount);
    
    vector<int> p = {1, 2, 3, 4};
    cout << "Minimum multiplication cost: " << matrixChain(p, p.size()) << endl;
    
    vector<vector<int>> dist = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    cout << "Minimum cost: " << tsp(1, 0, dist, dp, n) << endl;
    
    vector<vector<int>> graph = {{0, 3, INT_MAX, 5}, {2, 0, INT_MAX, 4}, {INT_MAX, 1, 0, INT_MAX}, {INT_MAX, INT_MAX, 2, 0}};
    floydWarshall(graph, graph.size());
    
    vector<int> keys = {10, 20, 30};
    vector<int> freq = {34, 8, 50};
    cout << "Optimal BST cost: " << optimalBST(keys, freq, keys.size()) << endl;
    
    return 0;
}
