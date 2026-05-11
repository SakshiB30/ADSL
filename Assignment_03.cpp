// Starting with an empty organizational hierarchy, construct the structure by adding employees in the given order. After building the hierarchy: i. Add a new employee to the team, ensuring they are placed in the correct position based on their role. ii. Determine the number of employees in the longest reporting chain starting from the CEO. iii. Identify the employee with the least seniority in the organization. iv. Search for an employee within the hierarchy to check if they are part of the organization. Find the time requirements of your method.

#include <iostream>
#include <vector>
using namespace std;

struct Employee {
    string name;
    string role;
    vector<Employee*> subordinates;

    Employee(string n, string r) {
        name = n;
        role = r;
    }
};

Employee* findEmployee(Employee* root, string name) {
    if (!root) return NULL;
    if (root->name == name) return root;

    for (auto sub : root->subordinates) {
        Employee* res = findEmployee(sub, name);
        if (res) return res;
    }
    return NULL;
}

void addEmployee(Employee* root) {
    string managerName, empName, role;

    cout << "Enter Manager Name: ";
    cin >> managerName;

    Employee* manager = findEmployee(root, managerName);

    if (!manager) {
        cout << "Manager not found!\n";
        return;
    }

    cout << "Enter Employee Name: ";
    cin >> empName;
    cout << "Enter Role: ";
    cin >> role;

    Employee* emp = new Employee(empName, role);
    manager->subordinates.push_back(emp);

    cout << "Employee added successfully!\n";
}

void display(Employee* root, int level = 0) {
    if (!root) return;

    for (int i = 0; i < level; i++)
        cout << "  ";

    cout << root->name << " (" << root->role << ")" << endl;

    for (auto sub : root->subordinates)
        display(sub, level + 1);
}

int longestChain(Employee* root) {
    if (!root) return 0;

    int maxDepth = 0;
    for (auto sub : root->subordinates) {
        maxDepth = max(maxDepth, longestChain(sub));
    }
    return 1 + maxDepth;
}

Employee* leastSenior(Employee* root) {
    if (!root) return NULL;

    if (root->subordinates.empty())
        return root;

    for (auto sub : root->subordinates) {
        Employee* res = leastSenior(sub);
        if (res) return res;
    }
    return NULL;
}

int main() {
    string ceoName;
    cout << "Enter CEO Name: ";
    cin >> ceoName;

    Employee* CEO = new Employee(ceoName, "CEO");

    int choice;
    string name;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Hierarchy\n";
        cout << "3. Add New Employee (Task i)\n";
        cout << "4. Longest Reporting Chain (Task ii)\n";
        cout << "5. Least Senior Employee (Task iii)\n";
        cout << "6. Search Employee (Task iv)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addEmployee(CEO);
            break;

        case 2:
            display(CEO);
            break;

        case 3:
            addEmployee(CEO);
            break;

        case 4:
            cout << "Longest chain length: "
                 << longestChain(CEO) << endl;
            break;

        case 5: {
            Employee* emp = leastSenior(CEO);
            if (emp)
                cout << "Least senior employee: "
                     << emp->name << endl;
            break;
        }

        case 6:
            cout << "Enter name to search: ";
            cin >> name;
            if (findEmployee(CEO, name))
                cout << "Employee exists\n";
            else
                cout << "Employee not found\n";
            break;
        }

    } while (choice != 7);

    return 0;
}


