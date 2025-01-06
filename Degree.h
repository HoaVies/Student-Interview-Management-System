#ifndef DEGREE_H
#define DEGREE_H

#include <string>

using namespace std;

class Degree {
private:
    string degreeCode; // Unique code for the degree
    string degreeName;
    int completionYear;
    string completionPlace;

public:
    // Constructors
    Degree() : completionYear(0) {}
    Degree(string code, string name, int year, string place);

    void displayDegree() const;

    // Serialization and deserialization
    string serialize() const;
    void deserialize(const string &data);

    // Getters
    string getDegreeCode() const { return degreeCode; }
};

#endif
