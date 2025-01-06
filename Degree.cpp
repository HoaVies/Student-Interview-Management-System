#include "Degree.h"
#include <iostream>
#include <sstream>

using namespace std;

// Initialize degree code, name, year of completion and place of completion
Degree::Degree(string code, string name, int year, string place)
    : degreeCode(code), degreeName(name), completionYear(year), completionPlace(place) {}

// Display the degree
void Degree::displayDegree() const {
    cout << "  - Degree Code: " << degreeCode << ", Name: " << degreeName
         << ", Year: " << completionYear << ", Place: " << completionPlace << endl;
}

// Serialize the degree data
string Degree::serialize() const {
    stringstream ss;
    // Each field is separated by a comma
    ss << degreeCode << "," << degreeName << "," << completionYear << "," << completionPlace;
    return ss.str();
}

// Deserialize the degree data
void Degree::deserialize(const string &data) {
    stringstream ss(data);
    getline(ss, degreeCode, ','); // Read degree code up to first comma
    getline(ss, degreeName, ','); // Read degree name up to next comma
    // Read completion year up to next comma and convert to integer
    string token;
    getline(ss, token, ',');
    completionYear = stoi(token);
    // Read the final token as the place
    getline(ss, completionPlace, ',');
}
