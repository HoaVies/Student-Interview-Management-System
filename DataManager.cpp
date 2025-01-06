#include "DataManager.h"
#include <iostream>
#include <fstream> // for file stream operations
#include <sstream> // for string stream
#include <algorithm> // for sort

using namespace std;

// ----------------- Student Management -----------------

// Add a new student
bool DataManager::addStudent(const Student &student) {
    // Check if studentID already exists
    if (studentExists(student.getStudentID())) {
        cout << "Error: Student with ID " << student.getStudentID() << " already exists." << endl;
        return false;
    }
    // If not, add the student
    students.push_back(student);
    return true;
}

// Display information about all students
void DataManager::displayAllStudents() const {
    // If there are no students, print the message
    if (students.empty()) {
        cout << "No students available." << endl;
        return;
    }
    // Otherwise, iterate through each student and display their information
    for (const auto &student : students) {
        student.displayInfo();
    }
}

// Check if a student already exists 
bool DataManager::studentExists(int studentID) const {
    // Iterate through each student in the vector
    for (const auto &student : students) {
        if (student.getStudentID() == studentID)
            return true;
    }
    return false;
}

// Get a pointer to a Student object by studentID
Student* DataManager::getStudentByID(int studentID) {
    // Iterate through each student in the vector, if found return the address of the student
    for (auto &student : students) {
        if (student.getStudentID() == studentID)
            return &student;
    }
    //return a null pointer if the student is not found
    return nullptr;
}

// ----------------- Enterprise Management -----------------

// Add a new enterprise if the enterprise doesn't already exist
bool DataManager::addEnterprise(const Enterprise &enterprise) {
    // Check if enterpriseID already exists
    if (enterpriseExists(enterprise.getEnterpriseID())) {
        cout << "Error: Enterprise with ID " << enterprise.getEnterpriseID() << " already exists." << endl;
        return false;
    }
    // If not, add the enterprise
    enterprises.push_back(enterprise);
    return true;
}

// Display information about all enterprises
void DataManager::displayAllEnterprises() const {
    // If there are no enterprises, print the message
    if (enterprises.empty()) {
        cout << "No enterprises available." << endl;
        return;
    }
    // Otherwise, iterate through each enterprise and display their information
    for (const auto &enterprise : enterprises) {
        enterprise.displayEnterprise();
    }
}

// Check if an enterprise already exists
bool DataManager::enterpriseExists(int enterpriseID) const {
    for (const auto &enterprise : enterprises) {
        if (enterprise.getEnterpriseID() == enterpriseID)
            return true;
    }
    return false;
}

// Get a pointer to an Enterprise object by enterpriseID
Enterprise* DataManager::getEnterpriseByID(int enterpriseID) {
    // Iterate through each enterprise in the vector, if found return the address of the enterprise
    for (auto &enterprise : enterprises) {
        if (enterprise.getEnterpriseID() == enterpriseID)
            return &enterprise;
    }
    //return a null pointer if the enterprise is not found
    return nullptr;
}

// Get a pointer to an Enterprise object by name
Enterprise* DataManager::getEnterpriseByName(const string &name) {
    for (auto &enterprise : enterprises) {
        if (enterprise.getName() == name)
            return &enterprise;
    }
    return nullptr;
}

// ----------------- Meeting Management -----------------

// Add a new meeting if the meeting doesn't already exist
bool DataManager::addMeeting(const Meeting &meeting) {
    // Check if meetingID already exists
    for (const auto &m : meetings) {
        if (m.getMeetingID() == meeting.getMeetingID()) {
            cout << "Error: Meeting with ID " << meeting.getMeetingID() << " already exists." << endl;
            return false;
        }
    }

    // Check if the referenced student and enterprise exist
    if (!studentExists(meeting.getStudentID())) {
        cout << "Error: Student with ID " << meeting.getStudentID() << " does not exist." << endl;
        return false;
    }
    if (!enterpriseExists(meeting.getEnterpriseID())) {
        cout << "Error: Enterprise with ID " << meeting.getEnterpriseID() << " does not exist." << endl;
        return false;
    }

    // Check for scheduling conflicts
    if (hasSchedulingConflict(meeting)) {
        cout << "Error: Scheduling conflict detected for the student or enterprise." << endl;
        return false;
    }

    // If there are no errors, add the meeting to the vector
    meetings.push_back(meeting);
    return true;
}

// Display information about all meetings
void DataManager::displayAllMeetings() const {
    // If no meetings are scheduled, print the message
    if (meetings.empty()) {
        cout << "No meetings scheduled." << endl;
        return;
    }

    // Otherwise, iterate through each meeting and display their information
    for (const auto &meeting : meetings) {
        meeting.displayMeeting();
    }
}

// Check if a new meeting overlaps with an existing meeting
bool DataManager::hasSchedulingConflict(const Meeting &newMeeting) const {
    // Iterate through each existing meeting
    for (const auto &meeting : meetings) {
        // Compare the dates 
        if (meeting.getDate() == newMeeting.getDate()) {
            // Check if it's the same student
            if (meeting.getStudentID() == newMeeting.getStudentID()) {
                // Check if time overlaps
                if (!(newMeeting.getEndTime() <= meeting.getStartTime() || newMeeting.getStartTime() >= meeting.getEndTime()))
                    return true;
            }
            // Check if it's the same enterprise
            if (meeting.getEnterpriseID() == newMeeting.getEnterpriseID()) {
                // Check if time overlaps
                if (!(newMeeting.getEndTime() <= meeting.getStartTime() || newMeeting.getStartTime() >= meeting.getEndTime()))
                    return true;
            }
        }
    }
    // If there's no overlap, return false
    return false;
}

// ----------------- Sorted Listings -----------------

// List meetings for a specific student sorted by date and time
void DataManager::listMeetingsForStudent(int studentID) const {
    const Student* student = nullptr;
    // Find the student with studentID
    for (const auto &s : students) {
        if (s.getStudentID() == studentID) {
            student = &s;
            break;
        }
    }

    // If no student is found, print an error message
    if (!student) {
        cout << "Error: Student with ID " << studentID << " not found." << endl;
        return;
    }

    // Create a vector of pointers to meetings for the student
    vector<const Meeting*> studentMeetings;
    for (const auto &meeting : meetings) {
        if (meeting.getStudentID() == studentID) {
            studentMeetings.push_back(&meeting);
        }
    }

    // Sort meetings by date and time
    sort(studentMeetings.begin(), studentMeetings.end(), [&](const Meeting* a, const Meeting* b) -> bool {
        string datetimeA = a->getDate() + " " + a->getStartTime();
        string datetimeB = b->getDate() + " " + b->getStartTime();
        return datetimeA < datetimeB;
    });

    cout << "Meetings for " << student->getFirstName() << " " << student->getLastName()
         << " (ID: " << studentID << "):" << endl;
    // If no meetings are found for this student, print a message
    if (studentMeetings.empty()) {
        cout << "No meetings found for this student." << endl;
        return;
    }

    // Otherwise, display each meeting for that student
    for (const auto *meeting : studentMeetings) {
        meeting->displayMeeting();
    }
}

// List all meetings sorted by enterprise name, then date and time
void DataManager::listMeetingsForAllEnterprises() const {
    // Create a copy of meetings to sort
    vector<const Meeting*> sortedMeetings;
    for (const auto &meeting : meetings) {
        sortedMeetings.push_back(&meeting);
    }

    // First sort by enterprise name, then date and time
    sort(sortedMeetings.begin(), sortedMeetings.end(), [&](const Meeting* a, const Meeting* b) -> bool {
        // Get pointers to the associated enterprises
        Enterprise* enterpriseA = const_cast<DataManager*>(this)->getEnterpriseByID(a->getEnterpriseID());
        Enterprise* enterpriseB = const_cast<DataManager*>(this)->getEnterpriseByID(b->getEnterpriseID());

        // Get the names of the enterprises for comparison; if an enterprise is missing, use an empty string
        string nameA = enterpriseA ? enterpriseA->getName() : "";
        string nameB = enterpriseB ? enterpriseB->getName() : "";

        // If the names are the same, compare the dates and times
        if (nameA == nameB) {
            string datetimeA = a->getDate() + " " + a->getStartTime();
            string datetimeB = b->getDate() + " " + b->getStartTime();
            return datetimeA < datetimeB;
        }

        // Otherwise, just compare the enterprise names
        return nameA < nameB;
    });

    cout << "All Meetings Sorted by Enterprise Name, Date, and Time:" << endl;

    // If no meetings are found, print a message
    if (sortedMeetings.empty()) {
        cout << "No meetings scheduled." << endl;
        return;
    }

    // Track the current enterprise to group related meetings
    string currentEnterprise = "";
    for (const auto *meeting : sortedMeetings) {
        Enterprise* enterprise = const_cast<DataManager*>(this)->getEnterpriseByID(meeting->getEnterpriseID());
        string enterpriseName = enterprise ? enterprise->getName() : "Unknown Enterprise";
        //Print the enterprise name when a new enterprise group starts
        if (enterpriseName != currentEnterprise) {
            currentEnterprise = enterpriseName;
            cout << "Enterprise: " << currentEnterprise << endl;
        }
        // Display the meeting information
        meeting->displayMeeting();
    }
}

// ----------------- CV Display -----------------
void DataManager::displayStudentCV(int studentID) const {
    // Search for the student using studentID
    const Student* student = nullptr;
    for (const auto &s : students) {
        if (s.getStudentID() == studentID) {
            student = &s;
            break;
        }
    }

    // If no student found, print an error message
    if (!student) {
        cout << "Error: Student with ID " << studentID << " not found." << endl;
        return;
    }

    // Display the student's CV (personal details, degrees, experiences...)
    student->displayCV();
}

// ----------------- File Operations -----------------

// Load Students data from a file
void DataManager::loadStudents(const string &filename) {
    ifstream file(filename);
    // Check if the file can be opened
    if (!file.is_open()) {
        cout << "Warning: Could not open " << filename << " for reading." << endl;
        return;
    }
    string line;
    // Read each line until the end of the file
    while (getline(file, line)) {
        if (line.empty()) continue; //Skip empty lines
        Student student;
        try {
            // Deserialize the line into a Student object
            student.deserialize(line);
            // Add the student to the system
            addStudent(student);
        }
        catch(...) {
            cerr << "Failed to deserialize student: " << line << endl;
        }
    }
    file.close();
    cout << "Students loaded from " << filename << endl;
}

// Save students' data to a file in serialized form
void DataManager::saveStudents(const string &filename) const {
    ofstream file(filename);
    // Check if the file can be opened
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << " for writing." << endl;
        return;
    }
    // Write each student's serialized data to the file as a separate line
    for (const auto &student : students) {
        file << student.serialize() << endl;
    }
    file.close();
    cout << "Students saved to " << filename << endl;
}

// Load Enterprises data from a file
void DataManager::loadEnterprises(const string &filename) {
    ifstream file(filename);
    // Check if the file can be opened
    if (!file.is_open()) {
        cout << "Warning: Could not open " << filename << " for reading." << endl;
        return;
    }
    string line;
    // Read each line until the end of the file
    while (getline(file, line)) {
        if (line.empty()) continue;
        Enterprise enterprise;
        try {
            enterprise.deserialize(line);
            addEnterprise(enterprise);
        }
        catch(...) {
            cerr << "Failed to deserialize enterprise: " << line << endl;
        }
    }
    file.close();
    cout << "Enterprises loaded from " << filename << endl;
}

// Save Enterprises data to a file in serialized form
void DataManager::saveEnterprises(const string &filename) const {
    ofstream file(filename);
    // Check if the file can be opened
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << " for writing." << endl;
        return;
    }
    // Write each enterprise's serialized data to the file as a separate line
    for (const auto &enterprise : enterprises) {
        file << enterprise.serialize() << endl;
    }
    file.close();
    cout << "Enterprises saved to " << filename << endl;
}

// Load Meetings data from a file
void DataManager::loadMeetings(const string &filename) {
    ifstream file(filename);
    // Check if the file can be opened
    if (!file.is_open()) {
        cout << "Warning: Could not open " << filename << " for reading." << endl;
        return;
    }
    string line;
    // Read each line until the end of the file
    while (getline(file, line)) {
        if (line.empty()) continue;
        Meeting meeting;
        try {
            meeting.deserialize(line);
            addMeeting(meeting); // This will also check for conflicts while adding the meeting
        }
        catch(...) {
            cerr << "Failed to deserialize meeting: " << line << endl;
        }
    }
    file.close();
    cout << "Meetings loaded from " << filename << endl;
}

// Save Meetings data to a file in serialized form
void DataManager::saveMeetings(const string &filename) const {
    ofstream file(filename);
    // Check if the file can be opened
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << " for writing." << endl;
        return;
    }
    // Write each meeting's serialized data to the file as a separate line
    for (const auto &meeting : meetings) {
        file << meeting.serialize() << endl;
    }
    file.close();
    cout << "Meetings saved to " << filename << endl;
}
