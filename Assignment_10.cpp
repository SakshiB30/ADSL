//A library system maintains a collection of books. The file contains book ID, title, author, genre, and availability status. The system allows users to add, delete, and update book information. Users can search for a specific book by its ID. If the book record does not exist, an appropriate message is displayed. If the book is found, the system will show the details of the book. Use a sequential file to store and manage the data.

#include <iostream>
#include <fstream>
using namespace std;

// ---------- ADD BOOK ----------
void addBook() {
    ofstream file("books.txt", ios::app);

    int id;
    string title, author, genre, status;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, title);

    cout << "Enter Author: ";
    getline(cin, author);

    cout << "Enter Genre: ";
    getline(cin, genre);

    cout << "Enter Status (Available/Issued): ";
    getline(cin, status);

    file << id << "|" << title << "|" << author << "|"
         << genre << "|" << status << endl;

    file.close();
    cout << "Book added successfully!\n";
}

// ---------- DISPLAY ----------
void displayBooks() {
    ifstream file("books.txt");
    string line;

    cout << "\nAll Books:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// ---------- SEARCH ----------
void searchBook() {
    ifstream file("books.txt");

    int searchId;
    string line;
    bool found = false;

    cout << "Enter Book ID to search: ";
    cin >> searchId;

    while (getline(file, line)) {
        int id = stoi(line.substr(0, line.find('|')));

        if (id == searchId) {
            cout << "Book Found:\n" << line << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Book not found!\n";

    file.close();
}

// ---------- DELETE ----------
void deleteBook() {
    ifstream file("books.txt");
    ofstream temp("temp.txt");

    int delId;
    string line;
    bool found = false;

    cout << "Enter Book ID to delete: ";
    cin >> delId;

    while (getline(file, line)) {
        int id = stoi(line.substr(0, line.find('|')));

        if (id != delId) {
            temp << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book deleted successfully!\n";
    else
        cout << "Book not found!\n";
}

// ---------- UPDATE ----------
void updateBook() {
    ifstream file("books.txt");
    ofstream temp("temp.txt");

    int updId;
    string line;
    bool found = false;

    cout << "Enter Book ID to update: ";
    cin >> updId;
    cin.ignore();

    while (getline(file, line)) {
        int id = stoi(line.substr(0, line.find('|')));

        if (id == updId) {
            found = true;

            string title, author, genre, status;

            cout << "Enter new Title: ";
            getline(cin, title);
            cout << "Enter new Author: ";
            getline(cin, author);
            cout << "Enter new Genre: ";
            getline(cin, genre);
            cout << "Enter new Status: ";
            getline(cin, status);

            temp << updId << "|" << title << "|" << author
                 << "|" << genre << "|" << status << endl;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book updated successfully!\n";
    else
        cout << "Book not found!\n";
}

// ---------- MAIN ----------
int main() {
    int choice;

    do {
        cout << "\n--- LIBRARY MENU ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Update Book\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: updateBook(); break;
        }

    } while (choice != 6);

    return 0;
}

