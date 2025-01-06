#ifndef PROFESSIONALEXPERIENCE_H
#define PROFESSIONALEXPERIENCE_H

#include <string>

using namespace std;

class ProfessionalExperience {
private:
    string experienceID; // Unique ID for the experience
    string companyName;
    string position;
    string startDate;
    string endDate;

public:
    // Constructors
    ProfessionalExperience() {}
    ProfessionalExperience(string id, string company, string pos, string start, string end);

    void displayExperience() const;

    // Serialization and deserialization
    string serialize() const;
    void deserialize(const string &data);

    // Getters
    string getExperienceID() const { return experienceID; }
};

#endif
