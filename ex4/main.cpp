#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

void dijkstra(vector<vector<int>>& graph, int src, vector<int>& dist, vector<int>& path) {
    int n = graph.size();
    dist.assign(n, INT_MAX);
    path.assign(n, -1);

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < n; v++) {
            if (u != v && graph[u][v] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
                path[v] = u;
            }
        }
    }
}

void printPath(vector<int>& path, int v) {
    if (path[v] == -1) {
        cout << v;
        return;
    }
    printPath(path, path[v]);
    cout << " -> " << v;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x != -1) {
                graph[i][j] = x;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        vector<int> dist, path;
        dijkstra(graph, i, dist, path);
        cout << "Node " << i << ":\n";
        for (int j = 0; j < n; j++) {
            cout << "Distance from " << i << " to " << j << " = ";
            if (dist[j] == INT_MAX) {
                cout << "infinity\n";
            } else {
                cout << dist[j] << "\n";
                if (i != j) {
                    cout << "Path: ";
                    printPath(path, j);
                    cout << "\n";
                }
            }
        }
        cout << "\n";
    }

    return 0;
}