#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout << "SwiftCargo Multistage Route Optimizer " << endl;
    cout << "--------------------------------------------------" << endl;

    int stages;
    cout << "Enter total number of stages: " << endl;
    cin >> stages;

    vector<int> nodes(stages);
    cout << "Enter nodes in each stage (" << stages << " values): " << endl;
    for (int i = 0; i < stages; i++) {
        cin >> nodes[i];
    }

    int edges;
    cout << "Enter number of connections: " << endl;
    cin >> edges;

    vector<vector<pair<int, int>>> graph;
    int totalNodes = accumulate(nodes.begin(), nodes.end(), 0);
    graph.resize(totalNodes);

    cout << "Enter edges as: from to cost" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        if (u >= 0 && u < totalNodes && v >= 0 && v < totalNodes)
            graph[u].push_back({v, c});
    }

    vector<int> dist(totalNodes, INT_MAX);
    vector<int> parent(totalNodes, -1);

    // Assuming first stage node 0 is the source
    dist[0] = 0;
    for (int u = 0; u < totalNodes; u++) {
        for (auto &edge : graph[u]) {
            int v = edge.first;
            int cost = edge.second;
            if (dist[u] != INT_MAX && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                parent[v] = u;
            }
        }
    }

    cout << "\nMinimum cost from Stage-0 node 0:" << endl;
    for (int i = 0; i < totalNodes; i++) {
        if (dist[i] == INT_MAX)
            cout << "Node " << i << " → Unreachable" << endl;
        else
            cout << "Node " << i << " →0 Cost = " << dist[i] << endl;
    }

    int src;
    cout << "\nEnter a source node (Stage 0) to view route (-1 to skip): " << endl;
    cin >> src;

    if (src >= 0 && src < totalNodes) {
        cout << "Enter destination node: " << endl;
        int dest;
        cin >> dest;
        if (dist[dest] == INT_MAX) {
            cout << "No available route from " << src << " to " << dest << endl;
        } else {
            vector<int> path;
            for (int v = dest; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());

            cout << "\n Optimal Route: ";
            for (int v : path)
                cout << v << (v == dest ? "" : " -> ");
            cout << "\nTotal Cost = " << dist[dest] << endl;
        }
    }

    cout << "\n-----------------------------------------------" << endl;
    cout << "Optimization complete. Thank you for using SwiftCargo!" << endl;
    return 0;
}
