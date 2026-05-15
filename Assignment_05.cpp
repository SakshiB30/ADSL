// Represent a given graph using adjacency matrix to perform DFS and using adjacency list to perform BFS. Use the map of the area around the college as the graph. Identify the prominent landmarks as nodes and perform DFS and BFS on that. Analyze time and space complexity.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define V 5   // number of landmarks

string landmarks[V] = {
    "College", "Library", "Canteen", "Hostel", "BusStop"
};

// ---------- ADJ MATRIX ----------
int adjMatrix[V][V] = {0};

// ---------- ADJ LIST ----------
vector<int> adjList[V];

// ---------- ADD EDGE ----------
void addEdge(int u, int v) {
    adjMatrix[u][v] = adjMatrix[v][u] = 1;
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

// ---------- DISPLAY MATRIX ----------
void displayMatrix() {
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// ---------- DISPLAY LIST ----------
void displayList() {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < V; i++) {
        cout << landmarks[i] << " -> ";
        for (int j : adjList[i]) {
            cout << landmarks[j] << " ";
        }
        cout << endl;
    }
}

// ---------- DFS ----------
bool visitedDFS[V];

void DFS(int node) {
    cout << landmarks[node] << " ";
    visitedDFS[node] = true;

    for (int i = 0; i < V; i++) {
        if (adjMatrix[node][i] == 1 && !visitedDFS[i]) {
            DFS(i);
        }
    }
}

// ---------- BFS ----------
void BFS(int start) {
    bool visited[V] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << landmarks[node] << " ";

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// ---------- MAIN ----------
int main() {
    int choice, u, v, start;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Road (Edge)\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Display Adjacency List\n";
        cout << "4. Perform DFS (Matrix)\n";
        cout << "5. Perform BFS (List)\n";
        cout << "6. Exit\n";

        cout << "\nLandmarks:\n";
        for (int i = 0; i < V; i++) {
            cout << i << " -> " << landmarks[i] << endl;
        }

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter two nodes (u v): ";
            cin >> u >> v;
            addEdge(u, v);
            cout << "Edge added!\n";
            break;

        case 2:
            displayMatrix();
            break;

        case 3:
            displayList();
            break;

        case 4:
            cout << "Enter start node: ";
            cin >> start;

            for (int i = 0; i < V; i++)
                visitedDFS[i] = false;

            cout << "DFS Traversal: ";
            DFS(start);
            cout << endl;
            break;

        case 5:
            cout << "Enter start node: ";
            cin >> start;

            cout << "BFS Traversal: ";
            BFS(start);
            cout << endl;
            break;
        }

    } while (choice != 6);

    cout << "Program exited.\n";
    return 0;
}