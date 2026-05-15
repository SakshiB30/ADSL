// Consider a scenario for a customer support centre that handles different types of service requests: a) Urgent issues (top priority), b) Moderate issues (medium priority), c) Routine inquiries (least priority). Implement a priority queue to manage and process the service requests based on their priority levels. Analyse time complexity

#include <iostream>
#include <queue>
using namespace std;

struct Request {
    string issue;
    int priority;

    bool operator<(const Request& other) const {
        return priority < other.priority;
    }
};

int main() {
    priority_queue<Request> pq;
    int choice, type;
    string issue;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Service Request\n";
        cout << "2. Process Next Request\n";
        cout << "3. Display Pending Requests Count\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter issue description: ";
            cin.ignore();
            getline(cin, issue);

            cout << "Select priority:\n";
            cout << "1. Routine\n2. Moderate\n3. Urgent\n";
            cin >> type;

            pq.push({issue, type});
            cout << "Request added!\n";
            break;

        case 2:
            if (!pq.empty()) {
                Request r = pq.top();
                pq.pop();

                cout << "Processing: " << r.issue
                     << " (Priority " << r.priority << ")\n";
            } else {
                cout << "No pending requests\n";
            }
            break;

        case 3:
            cout << "Pending Requests: " << pq.size() << endl;
            break;

        }

    } while (choice != 4);

    return 0;
}