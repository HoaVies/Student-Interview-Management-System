#include "Student.h"
#include <iostream>
#include <sstream>

using namespace std;

// Construct a new student Object
Student::Student(int id, string first, string last, string addr, string phone, string cyc,
               string field, string bacSeries, int bacYear, string bacPlace)
    : studentID(id), firstName(first), lastName(last), address(addr), phoneNumber(phone),
      cycle(cyc), fieldOfStudy(field), baccalaureateSeries(bacSeries),
      baccalaureateYear(bacYear), baccalaureatePlace(bacPlace) {}

// Add degree to the student
void Student::addDegree(const Degree &degree) {
    degrees.push_back(degree);
}

// Add professional experience to the student
void Student::addExperience(const ProfessionalExperience &experience) {
    experiences.push_back(experience);
}

// Display student information
void Student::displayInfo() const {
    cout << "-----------------------------------" << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Cycle: " << cycle << endl;

    // Display additional information based on which cycle the student is in
    if (cycle == "First-cycle") {
        cout << "Baccalaureate Series: " << baccalaureateSeries << endl;
        cout << "Year: " << baccalaureateYear << endl;
        cout << "Place: " << baccalaureatePlace << endl;
    } else if (cycle == "Second-cycle") {
        cout << "Field of Study: " << fieldOfStudy << endl;
    }
    // Display degrees and professional experiences
    cout << "Degrees:" << endl;
    if(degrees.empty()) {
        cout << "  No degrees listed." << endl;
    }
    for (const auto &degree : degrees) {
        degree.displayDegree();
    }
    cout << "Professional Experiences:" << endl;
    if(experiences.empty()) {
        cout << "  No professional experiences listed." << endl;
    }
    for (const auto &experience : experiences) {
        experience.displayExperience();
    }
    cout << "-----------------------------------" << endl;
}

// Display CV of the student
void Student::displayCV() const {
    cout << "========== CV of " << firstName << " " << lastName << " ==========" << endl;
    displayInfo();
    cout << "=========================================================" << endl;
}

// Serialize student data to a string
string Student::serialize() const {
    stringstream ss;
    // Serialize basic student information
    ss << studentID << "|" << firstName << "|" << lastName << "|" << address << "|"
       << phoneNumber << "|" << cycle << "|" << fieldOfStudy << "|" 
       << baccalaureateSeries << "|" << baccalaureateYear << "|" << baccalaureatePlace;
    
    // Serialize degrees with a start marker and an end marker
    ss << "|DEGREES_START";
    for (const auto &degree : degrees) {
        ss << "|" << degree.serialize();
    }
    ss << "|DEGREES_END";
    
    // Serialize professional experiences with a start marker and an end marker
    ss << "|EXPERIENCES_START";
    for (const auto &exp : experiences) {
        ss << "|" << exp.serialize();
    }
    ss << "|EXPERIENCES_END";
    
    return ss.str();
}

// Deserialize student data from a string
void Student::deserialize(const string &data) {
    stringstream ss(data);
    string token;

    try {
        // Read the studentID token and convert it to an integer
        getline(ss, token, '|');
        studentID = stoi(token);
    }
    catch (const invalid_argument &e) {
        cerr << "Error: Invalid studentID '" << token << "'" << endl;
        throw;
    }
    // Read the remaining tokens
    getline(ss, firstName, '|');
    getline(ss, lastName, '|');
    getline(ss, address, '|');
    getline(ss, phoneNumber, '|');
    getline(ss, cycle, '|');
    getline(ss, fieldOfStudy, '|');
    getline(ss, baccalaureateSeries, '|');

    // Convert baccalaureateYear to an integer
    try {
        getline(ss, token, '|');
        if(token.empty()) {
            baccalaureateYear = 0;
        }
        else {
            baccalaureateYear = stoi(token);
        }
    }
    catch (const invalid_argument &e) {
        cerr << "Error: Invalid baccalaureateYear '" << token << "'" << endl;
        throw;
    }

    // Read the baccalaureatePlace token
    getline(ss, baccalaureatePlace, '|');

    // Clear existing degree and experience lists (if any)
    degrees.clear();
    experiences.clear();

    // Parse the remaining tokens to find the markers for degrees and experiences
    while (getline(ss, token, '|')) {
        // Check if we have reached the start of the degrees section
        if (token == "DEGREES_START") {
            // Read until we reach the end of the degrees section
            while (getline(ss, token, '|') && token != "DEGREES_END") {
                if(token.empty()) continue;
                Degree degree;
                try {
                    // Deserialize the degree token into the degree object and add it to the degree list
                    degree.deserialize(token);
                    degrees.push_back(degree);
                }
                catch(...) {
                    cerr << "Error deserializing degree: " << token << endl;
                }
            }
        }
        // Check if we have reached the start of the experiences section
        else if (token == "EXPERIENCES_START") {
            // Read until we reach the end of the experiences section
            while (getline(ss, token, '|') && token != "EXPERIENCES_END") {
                if(token.empty()) continue;
                ProfessionalExperience exp;
                try {
                    // Deserialize the experience token into the experience object and add it to the experience list
                    exp.deserialize(token);
                    experiences.push_back(exp);
                }
                catch(...) {
                    cerr << "Error deserializing experience: " << token << endl;
                }
            }
        }
    }
}
