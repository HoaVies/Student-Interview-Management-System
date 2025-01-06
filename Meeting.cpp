#include "Meeting.h"
#include <iostream>
#include <sstream>

using namespace std;

// Initialize meeting with specified attributes
Meeting::Meeting(int id, int sID, int eID, string d, string start, string end)
    : meetingID(id), studentID(sID), enterpriseID(eID), date(d), startTime(start), endTime(end) {}

// Display the meeting details
void Meeting::displayMeeting() const {
    cout << "-----------------------------------" << endl;
    cout << "Meeting ID: " << meetingID << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Enterprise ID: " << enterpriseID << endl;
    cout << "Date: " << date << endl;
    cout << "Start Time: " << startTime << endl;
    cout << "End Time: " << endTime << endl;
    cout << "-----------------------------------" << endl;
}

// Serialize meeting data
string Meeting::serialize() const {
    stringstream ss;
    // Use '|' to separate each field
    ss << meetingID << "|" << studentID << "|" << enterpriseID << "|" << date << "|" << startTime << "|" << endTime;
    return ss.str();
}

// Deserialize meeting data
void Meeting::deserialize(const string &data) {
    stringstream ss(data);
    string token;
    
    // Extract meetingID from the first token and convert it to an integer
    try {
        getline(ss, token, '|');
        meetingID = stoi(token);
    }
    catch (const invalid_argument &e) {
        cerr << "Error: Invalid meetingID '" << token << "'" << endl;
        throw;
    }

    // Extract studentID from the second token and convert it to an integer
    try {
        getline(ss, token, '|');
        studentID = stoi(token);
    }
    catch (const invalid_argument &e) {
        cerr << "Error: Invalid studentID '" << token << "'" << endl;
        throw;
    }

    // Extract enterpriseID from the third token and convert it to an integer
    try {
        getline(ss, token, '|');
        enterpriseID = stoi(token);
    }
    catch (const invalid_argument &e) {
        cerr << "Error: Invalid enterpriseID '" << token << "'" << endl;
        throw;
    }

    // Extract date, startTime, and endTime from the remaining tokens
    getline(ss, date, '|');
    getline(ss, startTime, '|');
    getline(ss, endTime, '|');
}
