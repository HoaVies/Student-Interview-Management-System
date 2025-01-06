#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Degree.h"
#include "ProfessionalExperience.h"

using namespace std;

class Student {
private:
    int studentID;
    string firstName;
    string lastName;
    string address;
    string phoneNumber;
    string cycle; // "First-cycle" or "Second-cycle"
    string fieldOfStudy; // Second-cycle students
    string baccalaureateSeries; // First-cycle students
    int baccalaureateYear;
    string baccalaureatePlace;
    vector<Degree> degrees; // List of degrees obtained
    vector<ProfessionalExperience> experiences; // Professional experiences

public:
    // Constructors
    Student() : studentID(0), baccalaureateYear(0) {}
    Student(int id, string first, string last, string addr, string phone, string cyc,
            string field = "", string bacSeries = "", int bacYear = 0, string bacPlace = "");

    void addDegree(const Degree &degree);
    void addExperience(const ProfessionalExperience &experience);
    void displayInfo() const;
    void displayCV() const;

    // Serialization and deserialization
    string serialize() const;
    void deserialize(const string &data);
    
    // Getters
    int getStudentID() const { return studentID; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
};

#endif
