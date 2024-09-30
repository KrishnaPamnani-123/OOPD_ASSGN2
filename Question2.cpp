#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Faculty {
protected:
    char name[50];
    char email[50];
    char phone[20];
    char room[20];
    char position[50];
    char Dept[50];

public:
    Faculty() {
        name[0] = email[0] = phone[0] = room[0] = position[0] = Dept[0] = '\0';
    }

    void setDetails(const char* n, const char* e, const char* ph, const char* r, const char* pos, const char* deptName) {
        strncpy(name, n, 49);
        strncpy(email, e, 49);
        strncpy(phone, ph, 19);
        strncpy(room, r, 19);
        strncpy(position, pos, 49);
        strncpy(Dept, deptName,49);
        name[49] = email[49] = phone[19] = room[19] = position[49]= Dept[49] = '\0';
    }

    void display() const {
        cout << "Name: " << name << "\nEmail: " << email
                  << "\nPhone: " << phone << "\nRoom: " << room
                  << "\nPosition: " << position 
                  << "\nDeaprtment: "<< Dept << endl;
        if (strncmp(position, "Head", 4) == 0) {
            cout << "Also serves as Administrative Officer" << endl;
        }
    }

    const char* getName() const { return name; }
};

class Department {
private:
    char name[50];
    Faculty faculty[5]; 
    int facultyCount;

public:
    Department() : facultyCount(0) {
        name[0] = '\0';
    }

    void setName(const char* n) {
        strncpy(name, n, 49);
        name[49] = '\0';
    }

    void addFaculty(const Faculty& f) {
        if (facultyCount < 5) {
            faculty[facultyCount++] = f;
        }
    }

    Faculty* findFaculty(const char* name) {
        for (int i = 0; i < facultyCount; ++i) {
            if (strcmp(faculty[i].getName(), name) == 0) {
                return &faculty[i];
            }
        }
        return nullptr;
    }

    void display() const {
        cout << "Department: " << name << endl;
        for (int i = 0; i < facultyCount; ++i) {
            cout << "\nFaculty #" << (i + 1) << ":\n";
            faculty[i].display();
        }
    }

    const char* getName() const { return name; }
};

class University {
private:
    Department departments[10];
    int departmentCount;

public:
    University() : departmentCount(0) {}

    void addDepartment(const Department& d) {
        if (departmentCount < 10) {
            departments[departmentCount++] = d;
        }
    }

    Faculty* findFaculty(const char* name) {
        for (int i = 0; i < departmentCount; ++i) {
            Faculty* found = departments[i].findFaculty(name);
            if (found) return found;
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
        // Skip header line
        file.getline(line, 256);

        while (file.getline(line, 256)) {
            char deptName[50], facultyName[50], email[50], phone[20], room[20], position[50];
            char* token = strtok(line, ",");
            if (token) strncpy(deptName, token, 49);
            token = strtok(nullptr, ",");
            if (token) strncpy(facultyName, token, 49);
            token = strtok(nullptr, ",");
            if (token) strncpy(email, token, 49);
            token = strtok(nullptr, ",");
            if (token) strncpy(phone, token, 19);
            token = strtok(nullptr, ",");
            if (token) strncpy(room, token, 19);
            token = strtok(nullptr, ",");
            if (token) strncpy(position, token, 49);

            Faculty f;
            f.setDetails(facultyName, email, phone, room, position, deptName);

            // Find or create department
            int deptIndex = -1;
            for (int i = 0; i < departmentCount; ++i) {
                if (strcmp(departments[i].getName(), deptName) == 0) {
                    deptIndex = i;
                    break;
                }
            }
            if (deptIndex == -1) {
                if (departmentCount < 10) {
                    departments[departmentCount].setName(deptName);
                    deptIndex = departmentCount;
                    departmentCount++;
                }
            }
            if (deptIndex != -1) {
                departments[deptIndex].addFaculty(f);
            }
        }

        file.close();
    }

    void display() const {
        for (int i = 0; i < departmentCount; ++i) {
            departments[i].display();
            cout << "\n------------------------\n";
        }
    }
};

int main() {
    University iiitd;
    iiitd.loadFromCSV("F:\\IIITD\\Mtech Sem 1\\OOPD\\MT24048_Assignment-2(A)\\MT24048_Ass2\\iiitd_faculty_with_hods.csv");

    // Display all departments and faculty
    // iiitd.display();

    while (true) {
        char name[50];
        cout << "\nEnter a faculty name to search (or 'quit' to exit): ";
        cin.getline(name, 50);

        if (strcmp(name, "quit") == 0) {
            break;
        }

        Faculty* found = iiitd.findFaculty(name);
        if (found) {
            cout << "\nFaculty found:\n";
            found->display();
        } else {
            cout << "\nFaculty not found: " << name << endl;
        }
    }

    return 0;
}