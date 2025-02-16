#include <bits/stdc++.h>
using namespace std;

void minCoins(int amount) {
    vector<int> coins = {10, 5, 1};
    vector<int> result;
    for (int coin : coins) {
        while (amount >= coin) {
            amount -= coin;
            result.push_back(coin);
        }
    }
    cout << "Minimum coins required: " << result.size() << endl;
}

int minCabs(vector<pair<int, int>>& persons) {
    vector<int> times;
    for (auto p : persons) {
        times.push_back(p.first);
        times.push_back(-p.second);
    }
    sort(times.begin(), times.end(), [](int a, int b) { return abs(a) < abs(b); });
    int cabs = 0, maxCabs = 0;
    for (int time : times) {
        cabs += (time > 0) ? 1 : -1;
        maxCabs = max(maxCabs, cabs);
    }
    return maxCabs;
}

double fractionalKnapsack(vector<pair<int, int>> items, int W) {
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        return (double)a.first / a.second > (double)b.first / b.second;
    });
    double maxProfit = 0;
    for (auto item : items) {
        if (W >= item.second) {
            maxProfit += item.first;
            W -= item.second;
        } else {
            maxProfit += (double)item.first * W / item.second;
            break;
        }
    }
    return maxProfit;
}

struct Job {
    char id;
    int deadline;
    int profit;
};

bool jobComparison(Job a, Job b) {
    return a.profit > b.profit;
}

int jobScheduling(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end(), jobComparison);
    int maxDeadline = 0;
    for (auto job : jobs) maxDeadline = max(maxDeadline, job.deadline);
    vector<bool> slots(maxDeadline, false);
    int totalProfit = 0;
    for (auto job : jobs) {
        for (int j = job.deadline - 1; j >= 0; j--) {
            if (!slots[j]) {
                slots[j] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }
    return totalProfit;
}

int main() {
    minCoins(17);
    vector<pair<int, int>> persons = {{1, 4}, {2, 6}, {5, 7}, {3, 8}};
    cout << "Minimum cabs required: " << minCabs(persons) << endl;
    vector<pair<int, int>> items = {{60, 10}, {100, 20}, {120, 30}};
    cout << "Maximum profit in knapsack: " << fractionalKnapsack(items, 50) << endl;
    vector<Job> jobs = {{'a', 4, 20}, {'b', 1, 10}, {'c', 1, 40}, {'d', 1, 30}};
    cout << "Maximum job profit: " << jobScheduling(jobs) << endl;
    return 0;
}
