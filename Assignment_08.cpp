// Given sequence k = k1 <k2 < … <kn of n sorted keys, with a search probability pi for each key ki . Build the Binary search tree that has the least search cost given the access probability for each key? Analyse time complexity

#include <iostream>
#include <climits>
using namespace std;

int sum(int freq[], int i, int j) {

    int s = 0;

    for(int k = i; k <= j; k++) {
        s += freq[k];
    }

    return s;
}

// Function to find optimal BST cost
int optimalBST(int freq[], int n) {

    int cost[50][50];

    // Cost for single key
    for(int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
    }

    // L = length of chain
    for(int L = 2; L <= n; L++) {

        for(int i = 0; i <= n - L; i++) {

            int j = i + L - 1;

            cost[i][j] = INT_MAX;

            // Try each key as root
            for(int r = i; r <= j; r++) {

                int leftnode = 0;
                int rightnode = 0;

                // Left subtree cost
                if(r > i)
                    leftnode = cost[i][r - 1];

                // Right subtree cost
                if(r < j)
                    rightnode = cost[r + 1][j];

                // Total cost
                int totalcost =
                    leftnode +
                    rightnode +
                    sum(freq, i, j);

                // Store minimum
                if(totalcost < cost[i][j]) {
                    cost[i][j] = totalcost;
                }
            }
        }
    }

    return cost[0][n - 1];
}

int main() {

    int n;
    int keys[50];
    int freq[50];

    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter sorted keys:\n";

    for(int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter frequencies:\n";

    for(int i = 0; i < n; i++) {
        cin >> freq[i];
    }

    int result = optimalBST(freq, n);

    cout << "Optimal BST Cost = "
         << result << endl;

    return 0;
}