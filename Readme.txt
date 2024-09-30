# IIITD Administration System

This Assignment contains three C++ programs that simulate different aspects of the IIITD (Indraprastha Institute of Information Technology Delhi) administration system. Each program focuses on a specific area: Administration management, faculty management, and complaint management.

## Table of Contents

1. [Program 1: Administration Management](#program-1-Administration-management)
2. [Program 2: Faculty Management](#program-2-faculty-management)
3. [Program 3: Complaint Management System](#program-3-complaint-management-system)
4. [Building and Running the Programs](#building-and-running-the-programs)
5. [Input File Formats](#input-file-formats)

## Program 1: Administration Management

This program manages Administration information for IIITD Administrative Officers. It allows loading data from a CSV file, searching for individuals, and displaying their information.

### Key Features:
- Load Administration data from a CSV file
- Search for individuals by name
- Display detailed information about each person

## Program 2: Faculty Management

This program focuses on managing faculty information across different departments at IIITD. It supports loading data from a CSV file, searching for faculty members, and displaying department information.

### Key Features:
- Load faculty data from a CSV file
- Organize faculty members by department
- Search for faculty members by name
- Display information about all departments and faculty members

## Program 3: Complaint Management System

This program implements a complaint management system with an escalation matrix. It simulates the process of filing complaints, assigning them to appropriate Administration, and escalating them if not resolved within a specific timeframe.

### Key Features:
- Add complaints to the system
- Automatically assign complaints to appropriate Administration
- Escalate complaints based on predefined rules
- Resolve complaints
- Display status of all complaints

## Building and Running the Programs

To build and run these programs, I used a C++ compiler that supports C++11 or later. Here are the steps to compile and run each program:

1. Open a terminal or command prompt.
2. Navigate to the directory containing the source code.
3. Use the following commands to compile and run each program:

### For Program 1 (Administration Management):
```
g++ -c Question1.cpp
g++ -g -o debug1 Question1.o
g++ -O3 -o optimize1 Question1.o

./debug1
```

### For Program 2 (Faculty Management):
```
g++ -c Question2.cpp
g++ -g -o debug2 Question2.o
g++ -O3 -o optimize2 Question2.o

./debug2
```

### For Program 3 (Complaint Management System):
```
g++ -c Question3.cpp
g++ -g -o debug3 Question3.o
g++ -O3 -o optimize3 Question3.o

./debug3


## Input File Formats

### Program 1: Administration Management
This program expects a CSV file named `data.csv` with the following format:
```
Department,Position,Name,Room,Phone,Email
Department1,Position1,Name1,Room1,Phone1,Email1
Department2,Position2,Name2,Room2,Phone2,Email2
...
```

### Program 2: Faculty Management
This program expects a CSV file named `iiitd_faculty_with_hods.csv` with the following format:
```
Department,Name,Email,Phone,Room,Position
Department1,Name1,Email1,Phone1,Room1,Position1
Department2,Name2,Email2,Phone2,Room2,Position2
...
```

### Program 3: Complaint Management System
This program does not require an input file. It uses in code data to simulate the complaint management system. However, we can modify the `main()` function to add more Administration or complaints as needed.

---
