#include<bits/stdc++.h>
using namespace std;

struct Item {
    int weight, profit;
    double ratio;
};

struct Node {
    int level;
    int weight;
    int profit;
    double bound;
    string status;
};

bool cmp(Item a, Item b) {
    return a.ratio > b.ratio;
}

double bound(int level, int weight, int profit, int capacity, const vector<Item>& items, int n) {
    if (weight >= capacity) return 0;

    double result = profit;
    int totalWeight = weight;
    for (int i = level; i < n; ++i) {
        if (totalWeight + items[i].weight <= capacity) {
            totalWeight += items[i].weight;
            result += items[i].profit;
        } else {
            int remain = capacity - totalWeight;
            result += items[i].ratio * remain;
            break;
        }
    }
    return result;
}

void knapsackBranchAndBound(const vector<int>& weights, const vector<int>& profits, int capacity) {
    int n = weights.size();
    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        items[i] = {weights[i], profits[i], (double)profits[i] / weights[i]};
    }

    sort(items.begin(), items.end(), cmp);

    queue<Node> q;
    vector<Node> table; // to store for display

    double globalUB = -1e9;
    Node u, v;
    u.level = 0;
    u.weight = 0;
    u.profit = 0;
    u.bound = bound(0, 0, 0, capacity, items, n);
    u.status = "e-node";
    globalUB = max(globalUB, u.bound);
    q.push(u);
    table.push_back(u);

    while (!q.empty()) {
        u = q.front(); q.pop();

        if (u.level == n) continue;

        // Include the next item
        v.level = u.level + 1;
        v.weight = u.weight + items[u.level].weight;
        v.profit = u.profit + items[u.level].profit;
        v.bound = bound(v.level, v.weight, v.profit, capacity, items, n);
        v.status = "e-node";

        if (v.weight <= capacity && v.bound > globalUB) {
            globalUB = max(globalUB, v.bound);
        }

        table.push_back(v);
        if (v.bound > globalUB) v.status = ""; // pruned
        else q.push(v);

        // Exclude the next item
        v.level = u.level + 1;
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v.level, v.weight, v.profit, capacity, items, n);
        v.status = "";

        if (v.bound > globalUB) {
            v.status = "e-node";
            q.push(v);
            globalUB = max(globalUB, v.bound);
        }

        table.push_back(v);
    }

    // Print table
    cout << left << setw(10) << "Level"
         << setw(25) << "Current weight of bag"
         << setw(25) << "Current profit of bag"
         << setw(15) << "Upper Bound"
         << setw(10) << "Cost"
         << setw(20) << "Global UB"
         << "Status" << endl;

    globalUB = -1e9;
    for (const auto& node : table) {
        globalUB = max(globalUB, node.bound);
        cout << left << setw(10) << node.level
             << setw(25) << node.weight
             << setw(25) << node.profit
             << setw(15) << fixed << setprecision(2) << node.bound
             << setw(10) << -(int)node.bound
             << setw(20) << fixed << setprecision(2) << globalUB
             << node.status << endl;
    }
}

int main() {
    vector<int> weights = {2, 4, 6, 9};
    vector<int> profits = {10, 10, 12, 18};
    int capacity = 15;

    knapsackBranchAndBound(weights, profits, capacity);
    return 0;
}
