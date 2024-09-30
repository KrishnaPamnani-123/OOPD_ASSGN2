#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Person {
protected:
    char name[50];
    char position[50];
    char room[10];
    char phone[15];
    char email[50];
    char department[50];

public:
    Person() {
        name[0] = position[0] = room[0] = phone[0] = email[0] = department[0] = '\0';
    }

    void setDetails(const char* n, const char* pos, const char* r, const char* ph, const char* e, const char* dept) {
        strncpy(name, n, 49);
        strncpy(position, pos, 49);
        strncpy(room, r, 9);
        strncpy(phone, ph, 14);
        strncpy(email, e, 49);
        strncpy(department, dept, 49);
        name[49] = position[49] = room[9] = phone[14] = email[49] = department[49] = '\0';
    }

    void display() const {
        cout << "Name: " << name << "\nPosition: " << position
                  << "\nDepartment: " << department << "\nRoom: " << room 
                  << "\nPhone: " << phone << "\nEmail: " << email << endl;
    }

    const char* getName() const { return name; }
};

class Administration {
private:
    Person people[100];
    int peopleCount;

public:
    Administration() : peopleCount(0) {}

    void addPerson(const Person& p) {
        if (peopleCount < 100) {
            people[peopleCount++] = p;
        }
    }

    Person* findPerson(const char* name) {
        for (int i = 0; i < peopleCount; ++i) {
            if (strcmp(people[i].getName(), name) == 0) {
                return &people[i];
            }
        }
        return nullptr;
    }

    void loadFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file: " << filename << endl;
            return;
        }

        char line[256];
        file.getline(line, 256);

        while (file.getline(line, 256)) {
            char department[50], position[50], name[50], room[10], phone[15], email[50];
            char* token = strtok(line, ",");
            if (token) strncpy(department, token, 49);
            token = strtok(nullptr, ",");
            if (token) strncpy(position, token, 49);
            token = strtok(nullptr, ",");
            if (token) strncpy(name, token, 49);
            token = strtok(nullptr, ",");
            if (token) strncpy(room, token, 9);
            token = strtok(nullptr, ",");
            if (token) strncpy(phone, token, 14);
            token = strtok(nullptr, ",");
            if (token) strncpy(email, token, 49);

            Person p;
            p.setDetails(name, position, room, phone, email, department);
            addPerson(p);
        }

        file.close();
    }
};

int main() {
    Administration iiitd;
    iiitd.loadFromCSV("F:\\IIITD\\Mtech Sem 1\\OOPD\\MT24048_Assignment-2(A)\\MT24048_Ass2\\data.csv");

    while (true) {
        char name[50];
        cout << "\nEnter a name to search (or 'quit' to exit): ";
        cin.getline(name, 50);

        if (strcmp(name, "quit") == 0) {
            break;
        }

        Person* found = iiitd.findPerson(name);
        if (found) {
            cout << "\nPerson found:\n";
            found->display();
        } else {
            cout << "\nPerson not found: " << name << endl;
        }
    }

    return 0;
}