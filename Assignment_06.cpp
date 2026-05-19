// Represent a city's utility grid network using an adjacency list graph. Simulate power flow analysis using Dijkstra's algorithm. Add an option to display all reachable power stations within a specified time limit for maintenance. Find time complexity

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define V 6

// ---------- GRAPH ----------
vector<pair<int,int>> adj[V]; // {neighbor, weight}

string station[V] = {
    "Plant", "Sub1", "Sub2", "Sub3", "Sub4", "Sub5"
};

// ---------- ADD EDGE ----------
void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// ---------- DISPLAY GRAPH ----------
void displayGraph() {
    for (int i = 0; i < V; i++) {
        cout << station[i] << " -> ";
        for (auto x : adj[i]) {
            cout << "(" << station[x.first] << "," << x.second << ") ";
        }
        cout << endl;
    }
}

// ---------- DIJKSTRA ----------
vector<int> dijkstra(int src) {
    vector<int> dist(V, 1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ---------- REACHABLE WITHIN TIME ----------
void reachableStations(vector<int> dist, int limit) {
    cout << "Stations within time " << limit << ":\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] <= limit)
            cout << station[i] << " (Time: " << dist[i] << ")\n";
    }
}

// ---------- MAIN ----------
int main() {
    int choice, u, v, w, src, limit;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Transmission Line\n";
        cout << "2. Display Network\n";
        cout << "3. Run Dijkstra (Power Flow)\n";
        cout << "4. Stations within Time Limit\n";
        cout << "5. Exit\n";

        cout << "\nStations:\n";
        for (int i = 0; i < V; i++) {
            cout << i << " -> " << station[i] << endl;
        }

        cout << "Enter choice: ";
        cin >> choice;

        static vector<int> dist;

        switch (choice) {

        case 1:
            cout << "Enter u v weight: ";
            cin >> u >> v >> w;
            addEdge(u, v, w);
            break;

        case 2:
            displayGraph();
            break;

        case 3:
            cout << "Enter source station: ";
            cin >> src;
            dist = dijkstra(src);

            cout << "Shortest time from " << station[src] << ":\n";
            for (int i = 0; i < V; i++) {
                cout << station[i] << " = " << dist[i] << endl;
            }
            break;

        case 4:
            cout << "Enter time limit: ";
            cin >> limit;
            reachableStations(dist, limit);
            break;

        }

    } while (choice != 5);

    return 0;
}

