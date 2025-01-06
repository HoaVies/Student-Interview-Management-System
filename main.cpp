#include <iostream>
#include <limits> // For numeric_limits
#include "DataManager.h"

using namespace std;

// Function Prototypes
void displayMenu();
void addStudent(DataManager &dm);
void addEnterprise(DataManager &dm);
void scheduleMeeting(DataManager &dm);
void loadData(DataManager &dm);
void saveData(DataManager &dm);
void listMeetingsForStudent(DataManager &dm);
void listMeetingsForAllEnterprises(DataManager &dm);
void displayStudentCV(DataManager &dm);

int main() {
    DataManager dataManager; // Manage student, enterprise, and meeting data
    int choice; // Store user's choice

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addStudent(dataManager);
                break;
            case 2:
                addEnterprise(dataManager);
                break;
            case 3:
                scheduleMeeting(dataManager);
                break;
            case 4:
                dataManager.displayAllStudents();
                break;
            case 5:
                dataManager.displayAllEnterprises();
                break;
            case 6:
                dataManager.displayAllMeetings();
                break;
            case 7:
                loadData(dataManager);
                break;
            case 8:
                saveData(dataManager);
                break;
            case 9:
                listMeetingsForStudent(dataManager);
                break;
            case 10:
                listMeetingsForAllEnterprises(dataManager);
                break;
            case 11:
                displayStudentCV(dataManager);
                break;
            case 12:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            // For invalid choices
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}

// Print the list of options 
void displayMenu() {
    cout << "========== Student-Enterprise Meeting System ==========" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add Enterprise" << endl;
    cout << "3. Schedule Meeting" << endl;
    cout << "4. Display All Students" << endl;
    cout << "5. Display All Enterprises" << endl;
    cout << "6. Display All Meetings" << endl;
    cout << "7. Load Data from Files" << endl;
    cout << "8. Save Data to Files" << endl;
    cout << "9. List Meetings for a Student" << endl;
    cout << "10. List Meetings for All Enterprises" << endl;
    cout << "11. Display Student CV" << endl;
    cout << "12. Exit" << endl;
    cout << "=======================================================" << endl;
}

// Add a new student to the system
void addStudent(DataManager &dm) {
    int id;
    string firstName, lastName, address, phone, cycle;
    string fieldOfStudy, bacSeries, bacPlace;
    int bacYear;

    // Ask user to enter student details
    cout << "Enter Student ID (integer): ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Check if student ID already exists
    if (dm.studentExists(id)) {
        cout << "Error: Student with ID " << id << " already exists." << endl;
        return;
    }

    cout << "Enter First Name: ";
    getline(cin, firstName);

    cout << "Enter Last Name: ";
    getline(cin, lastName);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Phone Number: ";
    getline(cin, phone);

    cout << "Enter Cycle (First-cycle/Second-cycle): ";
    getline(cin, cycle);

    // If student is the First-cycle, ask for baccaulaureate details
    if (cycle == "First-cycle") {
        cout << "Enter Baccalaureate Series: ";
        getline(cin, bacSeries);

        cout << "Enter Baccalaureate Year (integer): ";
        cin >> bacYear;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Baccalaureate Place: ";
        getline(cin, bacPlace);
    }
    // If student is the Second-cycle, ask for field of study
    if (cycle == "Second-cycle") {
        cout << "Enter Field of Study: ";
        getline(cin, fieldOfStudy);
    }
    // Construct student object
    Student student(id, firstName, lastName, address, phone, cycle, fieldOfStudy, bacSeries, bacYear, bacPlace);

    // Add Degrees
    int numDegrees;
    cout << "Enter number of degrees obtained: ";
    cin >> numDegrees;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // For each degree, ask for details and add to the student
    for (int i = 0; i < numDegrees; ++i) {
        string code, name, place;
        int year;
        cout << "Enter details for Degree " << i + 1 << ":" << endl;
        cout << "  Degree Code: ";
        getline(cin, code);
        cout << "  Degree Name: ";
        getline(cin, name);
        cout << "  Completion Year (integer): ";
        cin >> year;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Completion Place: ";
        getline(cin, place);
        Degree degree(code, name, year, place);
        student.addDegree(degree);
    }

    // Add Professional Experiences
    int numExperiences;
    cout << "Enter number of professional experiences: ";
    cin >> numExperiences;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // For each experience, ask for details and add to the student
    for (int i = 0; i < numExperiences; ++i) {
        string expID, company, position, start, end;
        cout << "Enter details for Professional Experience " << i + 1 << ":" << endl;
        cout << "  Experience ID (unique string): ";
        getline(cin, expID);
        cout << "  Company Name: ";
        getline(cin, company);
        cout << "  Position: ";
        getline(cin, position);
        cout << "  Start Date (YYYY-MM-DD): ";
        getline(cin, start);
        cout << "  End Date (YYYY-MM-DD): ";
        getline(cin, end);
        ProfessionalExperience exp(expID, company, position, start, end);
        student.addExperience(exp);
    }
    // Add the student with all details to the system
    if (dm.addStudent(student)) {
        cout << "Student added successfully." << endl;
    }
}

// Add a new enterprise to the system
void addEnterprise(DataManager &dm) {
    int id;
    string name, address, contactName, contactPhone;

    cout << "Enter Enterprise ID (integer): ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Check if enterprise ID already exists
    if (dm.enterpriseExists(id)) {
        cout << "Error: Enterprise with ID " << id << " already exists." << endl;
        return;
    }
    // Ask user to enter enterprise details
    cout << "Enter Enterprise Name: ";
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Contact Name: ";
    getline(cin, contactName);

    cout << "Enter Contact Phone: ";
    getline(cin, contactPhone);
    // Construct enterprise object
    Enterprise enterprise(id, name, address, contactName, contactPhone);
    // Add the enterprise with all details to the system
    if (dm.addEnterprise(enterprise)) {
        cout << "Enterprise added successfully." << endl;
    }
}

// Schedule a meeting between a student and an enterprise
void scheduleMeeting(DataManager &dm) {
    int meetingID, studentID, enterpriseID;
    string date, startTime, endTime;
    // Ask user to enter meeting details
    cout << "Enter Meeting ID (integer): ";
    cin >> meetingID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Check if meeting ID already exists
    if (dm.hasSchedulingConflict(Meeting(meetingID, 0, 0, "", "", ""))) { // Preliminary check
        cout << "Error: Meeting with ID " << meetingID << " already exists." << endl;
        return;
    }

    // Ask user to enter studentID and validate it
    cout << "Enter Student ID (integer): ";
    cin >> studentID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!dm.studentExists(studentID)) {
        cout << "Error: Student with ID " << studentID << " does not exist." << endl;
        return;
    }

    // Ask user to enter enterpriseID and validate it
    cout << "Enter Enterprise ID (integer): ";
    cin >> enterpriseID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!dm.enterpriseExists(enterpriseID)) {
        cout << "Error: Enterprise with ID " << enterpriseID << " does not exist." << endl;
        return;
    }

    // Ask user to enter date, start time, and end time
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter Start Time (HH:MM): ";
    getline(cin, startTime);

    cout << "Enter End Time (HH:MM): ";
    getline(cin, endTime);
    // Construct meeting object
    Meeting meeting(meetingID, studentID, enterpriseID, date, startTime, endTime);
    // Add the meeting with all details to the system
    if (dm.addMeeting(meeting)) {
        cout << "Meeting scheduled successfully." << endl;
    }
}

// Load data from predefined files
void loadData(DataManager &dm) {
    string studentFile = "students.txt";
    string enterpriseFile = "enterprises.txt";
    string meetingFile = "meetings.txt";

    // Load each type of data via DataManager
    dm.loadStudents(studentFile);
    dm.loadEnterprises(enterpriseFile);
    dm.loadMeetings(meetingFile);
}

// Save data to predefined files
void saveData(DataManager &dm) {
    string studentFile = "students.txt";
    string enterpriseFile = "enterprises.txt";
    string meetingFile = "meetings.txt";

    // Save each type of data to its respective file
    dm.saveStudents(studentFile);
    dm.saveEnterprises(enterpriseFile);
    dm.saveMeetings(meetingFile);
}

// List meetings for a specific student
void listMeetingsForStudent(DataManager &dm) {
    int studentID;
    // Ask user to enter studentID and validate it
    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!dm.studentExists(studentID)) {
        cout << "Error: Student with ID " << studentID << " does not exist." << endl;
        return;
    }
    // Display a sorted list of meetings for that student
    dm.listMeetingsForStudent(studentID);
}

// List meetings for all enterprises using DataManager
void listMeetingsForAllEnterprises(DataManager &dm) {
    dm.listMeetingsForAllEnterprises();
}

// Display CV of a student 
void displayStudentCV(DataManager &dm) {
    int studentID;

    cout << "Enter Student ID to display CV: ";
    cin >> studentID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    dm.displayStudentCV(studentID);
}
