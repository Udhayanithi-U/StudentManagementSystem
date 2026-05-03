#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class student {
public:
    int id;
    char name[30];
    int age;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age << endl;
    }
};

// ADD
void add() {
    student s;
    ofstream file("student.dat", ios::binary | ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    s.input();
    file.write((char*)&s, sizeof(s));

    cout << "Student added successfully!\n";
    file.close();
}

// DISPLAY
void displayAll() {
    student s;
    ifstream file("student.dat", ios::binary);

    if (!file) {
        cout << "No records found!\n";
        return;
    }

    cout << "\n--- Student Records ---\n";

    while (file.read((char*)&s, sizeof(s))) {
        cout << "------------------";
        s.display();
    }

    file.close();
}

// UPDATE
void update() {
    student s;
    fstream file("student.dat", ios::binary | ios::in | ios::out);

    int id, found = 0;
    cout << "Enter ID to update: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "\nOld Data:";
            s.display();

            cout << "\nEnter New Data:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Updated successfully!\n";
            found = 1;
            break;
        }
    }

    if (found == 0)
        cout << "Record not found!\n";

    file.close();
}

// DELETE
void deleteRecord() {
    student s;
    ifstream file("student.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    int id, found = 0;
    cout << "Enter ID to delete: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }

    file.close();
    temp.close();

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (found)
        cout << "Deleted successfully!\n";
    else
        cout << "Record not found!\n";
}

// MAIN
int main() {
    int choice;

    do {
        cout << "\n\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: displayAll(); break;
            case 3: update(); break;
            case 4: deleteRecord(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
