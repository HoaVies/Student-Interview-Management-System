#include "ProfessionalExperience.h"
#include <iostream>
#include <sstream>

using namespace std;

// Initialize experiences with specified attributes
ProfessionalExperience::ProfessionalExperience(string id, string company, string pos, string start, string end)
    : experienceID(id), companyName(company), position(pos), startDate(start), endDate(end) {}

// Display experience
void ProfessionalExperience::displayExperience() const {
    cout << "    * Experience ID: " << experienceID << ", Company: " << companyName
         << ", Position: " << position << ", Start: " << startDate << ", End: " << endDate << endl;
}

// Serialize experience data
string ProfessionalExperience::serialize() const {
    stringstream ss;
    // Separate each field with a comma
    ss << experienceID << "," << companyName << "," << position << "," << startDate << "," << endDate;
    return ss.str();
}

// Deserialize experience data
void ProfessionalExperience::deserialize(const string &data) {
    stringstream ss(data);
    getline(ss, experienceID, ',');
    getline(ss, companyName, ',');
    getline(ss, position, ',');
    getline(ss, startDate, ',');
    getline(ss, endDate, ',');
}
