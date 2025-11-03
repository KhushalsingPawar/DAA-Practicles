#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Item {
    int weight;
    int utility;
    bool perishable;
};

// DP 0/1 Knapsack
int knapsackDP(const vector<Item>& items, int W, vector<int>& chosenItems) {
    int N = items.size();
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= N; ++i) {
        int wt = items[i - 1].weight;
        int val = items[i - 1].utility;
        for (int w = 0; w <= W; ++w) {
            if (wt <= w)
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - wt] + val);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    chosenItems.clear();
    int w = W;
    for (int i = N; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            chosenItems.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }
    reverse(chosenItems.begin(), chosenItems.end());

    return dp[N][W];
}

// Greedy with perishable priority + small randomness
int knapsackGreedy(vector<Item> items, int W, vector<int>& chosenItems) {
    int totalWeight = 0, totalUtility = 0;
    chosenItems.clear();
    vector<int> indices(items.size());
    for (int i = 0; i < (int)items.size(); ++i) indices[i] = i;

    // Prioritize perishable items + tiny random factor
    srand(time(0));
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        double ratioA = (double)items[a].utility / items[a].weight;
        double ratioB = (double)items[b].utility / items[b].weight;

        if (items[a].perishable) ratioA *= 1.2 + (rand() % 5) * 0.01; // 1.2-1.24
        if (items[b].perishable) ratioB *= 1.2 + (rand() % 5) * 0.01; // 1.2-1.24

        return ratioA > ratioB;
    });

    for (int i : indices) {
        if (totalWeight + items[i].weight <= W) {
            totalWeight += items[i].weight;
            totalUtility += items[i].utility;
            chosenItems.push_back(i);
        }
    }

    return totalUtility;
}

int main() {
    int N, W;
    cout << "Enter number of items and truck capacity (weight): ";
    cin >> N >> W;

    vector<Item> items(N);
    cout << "Enter weight, utility, perishable(1/0) for each item:\n";
    for (int i = 0; i < N; ++i) {
        int w, u, p;
        cin >> w >> u >> p;
        items[i] = {w, u, (bool)p};
    }

    vector<int> chosenDP, chosenGreedy;
    int dpUtility = knapsackDP(items, W, chosenDP);
    int greedyUtility = knapsackGreedy(items, W, chosenGreedy);

    // Display DP results
    int dpWeight = 0;
    cout << "\nDP (Optimal) Utility: " << dpUtility << "\nChosen items (index, perishable, weight): ";
    for (int i : chosenDP) {
        dpWeight += items[i].weight;
        cout << i << "(" << items[i].perishable << "," << items[i].weight << ") ";
    }
    cout << " | Total Weight: " << dpWeight << "\n";

    // Display Greedy results
    int greedyWeight = 0;
    cout << "\nGreedy Utility: " << greedyUtility << "\nChosen items (index, perishable, weight): ";
    for (int i : chosenGreedy) {
        greedyWeight += items[i].weight;
        cout << i << "(" << items[i].perishable << "," << items[i].weight << ") ";
    }
    cout << " | Total Weight: " << greedyWeight << "\n";

    return 0;
}
