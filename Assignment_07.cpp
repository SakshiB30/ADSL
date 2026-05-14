// You run a delivery service with multiple warehouses, and you want to establish delivery routes between them. The delivery company charges different rates for each route, and you aim to minimize the total cost of connecting all your warehouses. Solve this problem by suggesting appropriate data structures for efficient route management and cost minimization. Find time complexity.

#include<iostream>
using namespace std;

#define ROW 10
#define COL 10
#define infi 9999

class prims {
    int graph[ROW][COL], nodes;
public:
    void createGraph();
    void primsAlgo();
};


void prims::createGraph() {
    int i, j;
    cout << "Enter Total Warehouses: ";
    cin >> nodes;
    cout << "\nEnter Adjacency Matrix: \n";
    for (i = 0; i < nodes; i++) {
        for (j = i; j < nodes; j++) {
            cout << "Enter distance between " << i << " and " << j << endl;
            cin >> graph[i][j];
            graph[j][i] = graph[i][j];
        }
    }

    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            if (graph[i][j] == 0)
                graph[i][j] = infi;    //fill infinity where path is not present
        }
    }
    // Represent graph with Adjancy matrix
}


void prims::primsAlgo() {
    int selected[ROW], i, j, ne=0;
    int min = 0, x, y;
    int cost = 0;
    for (i = 0; i < nodes; i++)
        selected[i] = 0;

    selected[0] = 1;        //starting vertex is always node-0

    
    while (ne < nodes - 1) {
        min = infi;

        for (i = 0; i < nodes; i++) {
            if (selected[i] == 1) {
                for (j = 0; j < nodes; j++) {
                    if (selected[j] == 0) {
                        if (min > graph[i][j]) {
                            min = graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        selected[y] = 1;
        cout << "\n" << x << " --> " << y;
        cost += graph[x][y];
        ne++;
    }
    cout << "\nTotal cost is: " << cost << endl;
}

int main() {
    prims MST;
    cout << "\nPrims Algorithm to connect several Warehouses\n";
    MST.createGraph();
    cout<<"The Edges are \n ";
    MST.primsAlgo();
}

