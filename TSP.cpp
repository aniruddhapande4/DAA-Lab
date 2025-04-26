// Traveling Salesman Problem (TSP) using Dynamic Programming with Bitmasking
// Author: Aniruddha Pande
// Description: Finds the shortest route visiting all cities once and returning to the start

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Recursive function to compute the minimum cost path
int findMinCost(int visitedMask, int currentCity, int n,
                vector<vector<int>> &distanceMatrix, vector<vector<int>> &dp) {

    // All cities have been visited, return to starting city (0)
    if (visitedMask == (1 << n) - 1) {
        return distanceMatrix[currentCity][0];
    }

    // Return the result if already calculated
    if (dp[currentCity][visitedMask] != -1) {
        return dp[currentCity][visitedMask];
    }

    int minCost = INT_MAX;

    // Try all unvisited cities and take the minimum cost path
    for (int nextCity = 0; nextCity < n; nextCity++) {
        if ((visitedMask & (1 << nextCity)) == 0) {
            int newMask = visitedMask | (1 << nextCity);
            int newCost = distanceMatrix[currentCity][nextCity] + 
                          findMinCost(newMask, nextCity, n, distanceMatrix, dp);

            minCost = min(minCost, newCost);
        }
    }

    // Save and return the result
    return dp[currentCity][visitedMask] = minCost;
}

// Function to initiate the TSP algorithm
int solveTSP(vector<vector<int>> &distanceMatrix) {
    int n = distanceMatrix.size();

    // Memoization table: dp[currentCity][visitedMask]
    vector<vector<int>> dp(n, vector<int>((1 << n), -1));

    // Start from city 0 with only city 0 visited (mask = 1)
    return findMinCost(1, 0, n, distanceMatrix, dp);
}

int main() {
    // Distance matrix representing the cost between each pair of cities
    vector<vector<int>> distanceMatrix = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int result = solveTSP(distanceMatrix);
    cout << "Minimum cost to complete the tour: " << result << endl;

    return 0;
}
