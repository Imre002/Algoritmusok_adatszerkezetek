#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 502;

vector<int> adj[MAXN];
int capacity[MAXN][MAXN], parent[MAXN];

int bfs(int s, int t) {
    fill(parent, parent + MAXN, -1);
    parent[s] = s;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v]) {
                parent[v] = u;
                int new_flow = min(flow, capacity[u][v]);
                if (v == t) {
                    return new_flow;
                }
                q.push({v, new_flow});
            }
        }
    }

    return 0;
}

int edmondsKarp(int s, int t) {
    int flow = 0;
    int new_flow;

    while (new_flow = bfs(s, t)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void findMinCut(int s, int n, vector<pair<int, int>>& result) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v] && capacity[u][v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    for (int u = 1; u <= n; ++u) {
        if (visited[u]) {
            for (int v : adj[u]) {
                if (!visited[v] && capacity[v][u] > 0) {
                    result.push_back({u, v});
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    memset(capacity, 0, sizeof(capacity));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        capacity[a][b] = 1;
        capacity[b][a] = 1;
    }

    int max_flow = edmondsKarp(1, n);

    vector<pair<int, int>> result;
    findMinCut(1, n, result);

    cout << max_flow << endl;
    for (auto &p : result) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
