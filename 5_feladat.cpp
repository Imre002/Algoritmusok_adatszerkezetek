#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to, cost;
};

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int start, int n, const vector<vector<Edge>>& graph) {
    vector<int> dist(n + 1, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int newDist = dist[u] + edge.cost;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                pq.push({newDist, v});
            }
        }
    }

    return dist;
}

int main() {
    int cases;
    cin >> cases;

    while (cases--) {
        int P, Q;
        cin >> P >> Q;

        vector<vector<Edge>> graph(P + 1);
        vector<vector<Edge>> reverseGraph(P + 1);

        for (int i = 0; i < Q; ++i) {
            int u, v, cost;
            cin >> u >> v >> cost;
            graph[u].push_back({v, cost});
            reverseGraph[v].push_back({u, cost});
        }

        vector<int> distFromCCS = dijkstra(1, P, graph);
        vector<int> distToCCS = dijkstra(1, P, reverseGraph);

        long long totalCost = 0;
        for (int i = 2; i <= P; ++i) {
            totalCost += distFromCCS[i] + distToCCS[i];
        }

        cout << totalCost << endl;
    }

    return 0;
}
