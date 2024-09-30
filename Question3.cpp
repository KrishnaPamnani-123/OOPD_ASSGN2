#include <iostream>
#include <cstring>
using namespace std;

const int MAX_NAME_LENGTH = 50;
const int MAX_EMAIL_LENGTH = 50;
const int MAX_PHONE_LENGTH = 20;
const int MAX_ROOM_LENGTH = 50;
const int MAX_POSITION_LENGTH = 100;
const int MAX_DEPARTMENT_LENGTH = 50;
const int MAX_DOMAIN_LENGTH = 50;
const int MAX_DESCRIPTION_LENGTH = 200;
const int MAX_PEOPLE = 20;
const int MAX_COMPLAINTS = 50;

enum class Role { AdminOfficer, HeadOfDepartment, Registrar, Dean, Director };

class Person {
protected:
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char room[MAX_ROOM_LENGTH];
    char domain[MAX_DOMAIN_LENGTH];
    Role role;

public:
    Person() : role(Role::AdminOfficer) {
        name[0] = email[0] = phone[0] = room[0] = domain[0] = '\0';
    }

    Person(const char* n, const char* e, const char* p, const char* r, const char* d, Role rl)
        : role(rl) {
        strncpy(name, n, MAX_NAME_LENGTH - 1);
        strncpy(email, e, MAX_EMAIL_LENGTH - 1);
        strncpy(phone, p, MAX_PHONE_LENGTH - 1);
        strncpy(room, r, MAX_ROOM_LENGTH - 1);
        strncpy(domain, d, MAX_DOMAIN_LENGTH - 1);
        name[MAX_NAME_LENGTH - 1] = email[MAX_EMAIL_LENGTH - 1] = phone[MAX_PHONE_LENGTH - 1] = room[MAX_ROOM_LENGTH - 1] = domain[MAX_DOMAIN_LENGTH - 1] = '\0';
    }

    virtual void displayInfo() const {
        cout << "Name: " << name << " (";
        switch (role) {
            case Role::AdminOfficer: cout << "Administrative Officer"; break;
            case Role::HeadOfDepartment: cout << "Head of Department"; break;
            case Role::Registrar: cout << "Registrar"; break;
            case Role::Dean: cout << "Dean"; break;
            case Role::Director: cout << "Director"; break;
        }
        cout << ")\n";
        cout << "Email: " << email << "\n";
        cout << "Phone: " << phone << "\n";
        cout << "Room: " << room << "\n";
        cout << "Domain: " << domain << "\n";
    }

    const char* getName() const { return name; }
    const char* getDomain() const { return domain; }
    Role getRole() const { return role; }
};

class AdministrativeOfficer : public Person {
protected:
    char position[MAX_POSITION_LENGTH];

public:
    AdministrativeOfficer(const char* n, const char* e, const char* p, const char* r, const char* d, const char* pos)
        : Person(n, e, p, r, d, Role::AdminOfficer) {
        strncpy(position, pos, MAX_POSITION_LENGTH - 1);
        position[MAX_POSITION_LENGTH - 1] = '\0';
    }

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Position: " << position << "\n";
    }
};

class HeadOfDepartment : public Person {
public:
    HeadOfDepartment(const char* n, const char* e, const char* p, const char* r, const char* d)
        : Person(n, e, p, r, d, Role::HeadOfDepartment) {}
};

class Registrar : public Person {
public:
    Registrar(const char* n, const char* e, const char* p, const char* r, const char* d)
        : Person(n, e, p, r, d, Role::Registrar) {}
};

class Dean : public Person {
public:
    Dean(const char* n, const char* e, const char* p, const char* r, const char* d)
        : Person(n, e, p, r, d, Role::Dean) {}
};

class Director : public Person {
public:
    Director(const char* n, const char* e, const char* p, const char* r)
        : Person(n, e, p, r, "All", Role::Director) {}
};

class Complaint {
private:
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    char domain[MAX_DOMAIN_LENGTH];
    int daysOpen;
    bool resolved;
    Person* assignedTo;
    int daysAtCurrentLevel;

public:
    Complaint() : id(0), daysOpen(0), resolved(false), assignedTo(nullptr), daysAtCurrentLevel(0) {
        description[0] = domain[0] = '\0';
    }

    Complaint(int i, const char* desc, const char* d) 
        : id(i), daysOpen(0), resolved(false), assignedTo(nullptr), daysAtCurrentLevel(0) {
        strncpy(description, desc, MAX_DESCRIPTION_LENGTH - 1);
        strncpy(domain, d, MAX_DOMAIN_LENGTH - 1);
        description[MAX_DESCRIPTION_LENGTH - 1] = domain[MAX_DOMAIN_LENGTH - 1] = '\0';
    }

    void assignTo(Person* person) { 
        assignedTo = person; 
        daysAtCurrentLevel = 0;
    }
    void incrementDays() { 
        daysOpen++; 
        daysAtCurrentLevel++;
    }
    void resolve() { resolved = true; }
    bool isResolved() const { return resolved; }
    int getDaysOpen() const { return daysOpen; }
    int getDaysAtCurrentLevel() const { return daysAtCurrentLevel; }
    Person* getAssignedPerson() const { return assignedTo; }
    int getId() const { return id; }
    const char* getDomain() const { return domain; }

    void display() const {
        cout << "Complaint ID: " << id << "\n";
        cout << "Description: " << description << "\n";
        cout << "Domain: " << domain << "\n";
        cout << "Days Open: " << daysOpen << "\n";
        cout << "Days at Current Level: " << daysAtCurrentLevel << "\n";
        cout << "Status: " << (resolved ? "Resolved" : "Open") << "\n";
        if (assignedTo) {
            cout << "Assigned To:\n";
            assignedTo->displayInfo();
        }
        cout << "------------------------\n";
    }
};

class EscalationMatrix {
private:
    Person* people[MAX_PEOPLE];
    int peopleCount;
    Complaint complaints[MAX_COMPLAINTS];
    int complaintCount;

    Person* findPersonByRoleAndDomain(Role role, const char* domain) const {
        for (int i = 0; i < peopleCount; i++) {
            if (people[i]->getRole() == role && 
                (strcmp(people[i]->getDomain(), domain) == 0 || strcmp(people[i]->getDomain(), "All") == 0)) {
                return people[i];
            }
        }
        return nullptr;
    }

public:
    EscalationMatrix() : peopleCount(0), complaintCount(0) {}

    void addPerson(Person* person) {
        if (peopleCount < MAX_PEOPLE) {
            people[peopleCount++] = person;
        }
    }

    void addComplaint(const char* description, const char* domain) {
        if (complaintCount < MAX_COMPLAINTS) {
            int id = complaintCount + 1;
            complaints[complaintCount++] = Complaint(id, description, domain);
            Person* assignee = findPersonByRoleAndDomain(Role::AdminOfficer, domain);
            if (assignee) {
                complaints[complaintCount - 1].assignTo(assignee);
            }
        }
    }

    void updateComplaints() {
        for (int i = 0; i < complaintCount; i++) {
            if (!complaints[i].isResolved()) {
                complaints[i].incrementDays();
                if (complaints[i].getDaysAtCurrentLevel() > 3) {
                    escalateComplaint(complaints[i]);
                }
            }
        }
    }

    void escalateComplaint(Complaint& complaint) {
        Person* currentAssignee = complaint.getAssignedPerson();
        Role nextRole;

        switch (currentAssignee->getRole()) {
            case Role::AdminOfficer:
                nextRole = Role::HeadOfDepartment;
                break;
            case Role::HeadOfDepartment:
                nextRole = Role::Registrar;
                break;
            case Role::Registrar:
                nextRole = Role::Dean;
                break;
            case Role::Dean:
                nextRole = Role::Director;
                break;
            case Role::Director:
                return; // Can't escalate further
        }

        Person* nextAssignee = findPersonByRoleAndDomain(nextRole, complaint.getDomain());
        if (nextAssignee) {
            complaint.assignTo(nextAssignee);
            cout << "Complaint " << complaint.getId() << " escalated to " << nextAssignee->getName() << " (" << getRoleName(nextRole) << ")\n";
        } else if (nextRole == Role::Registrar) {
            // If Registrar for the specific domain is not found, try to find a general Registrar
            nextAssignee = findPersonByRoleAndDomain(Role::Registrar, "Administration");
            if (nextAssignee) {
                complaint.assignTo(nextAssignee);
                cout << "Complaint " << complaint.getId() << " escalated to " << nextAssignee->getName() << " (Registrar)\n";
            } else {
                // If still not found, escalate to Dean
                escalateComplaint(complaint);
            }
        } else {
            // If next level is not found, try to escalate to the next higher level
            escalateComplaint(complaint);
        }
    }

    const char* getRoleName(Role role) const {
        switch (role) {
            case Role::AdminOfficer: return "Administrative Officer";
            case Role::HeadOfDepartment: return "Head of Department";
            case Role::Registrar: return "Registrar";
            case Role::Dean: return "Dean";
            case Role::Director: return "Director";
            default: return "Unknown Role";
        }
    }

    void resolveComplaint(int id) {
        for (int i = 0; i < complaintCount; i++) {
            if (complaints[i].getId() == id) {
                complaints[i].resolve();
                cout << "Complaint " << id << " has been resolved.\n";
                return;
            }
        }
        cout << "Complaint " << id << " not found.\n";
    }

    void displayComplaints() const {
        for (int i = 0; i < complaintCount; i++) {
            complaints[i].display();
        }
    }
};

int main() {
    EscalationMatrix iiitd;

    // Director
    iiitd.addPerson(new Director("Prof. Ranjan Bose", "bose@iiitd.ac.in", "+91-11-26907400", "A-107, R & D Block"));

    // Deans
    iiitd.addPerson(new Dean("Sumit J Darak", "doaa@iiitd.ac.in", "+91-11-26907427", "A-208, R & D Block", "Academics"));
    iiitd.addPerson(new Dean("Shobha Sundar Ram", "dosa@iiitd.ac.in", "+91-11-26907460", "A-209, R & D Block", "StudentAffairs"));

    // Registrar
    iiitd.addPerson(new Registrar("Dr. Deepika Bhaskar", "deepika@iiitd.ac.in", "+91-11-26907419", "B-204 (Academic Block)", "Administration"));

    // Heads of Departments
    iiitd.addPerson(new HeadOfDepartment("Dr. Anubha Gupta", "anubha@iiitd.ac.in", "+91-11-26907333", "B-501 (R & D Block)", "Academics"));
    iiitd.addPerson(new HeadOfDepartment("Dr. Vivek Kumar", "vivek@iiitd.ac.in", "+91-11-26907444", "A-406 (R & D Block)", "Facilities"));

    // Administrative Officers
    iiitd.addPerson(new AdministrativeOfficer("Aakash Gupta", "aakash@iiitd.ac.in", "+91-11-26907135", "B-201 (Academic Block)", "Academics", "Junior Administrative Officer (Academics)"));
    iiitd.addPerson(new AdministrativeOfficer("Sanjay Roy", "sanjay@iiitd.ac.in", "+91-11-26907582", "A-201 (Academic Block)", "Facilities", "Project Engineer and Estate Officer"));

    // Add complaints
    iiitd.addComplaint("Network connectivity issues in Lab 1", "Facilities");
    iiitd.addComplaint("Projector not working in Lecture Hall 2", "Facilities");
    iiitd.addComplaint("Issues with course registration system", "Academics");

    // Simulate days passing and resolving complaints
    for (int day = 1; day <= 19; day++) {
        cout << "Day " << day << ":\n";
        iiitd.updateComplaints();
        iiitd.displayComplaints();

        if (day == 10) {
            iiitd.resolveComplaint(1);
        }
        if (day == 5){
            iiitd.resolveComplaint(2);
        }
        if (day == 18){
            iiitd.resolveComplaint(3);
        }

        cout << "\n";
    }

    return 0;
}