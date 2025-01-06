#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <string>
#include "Student.h"
#include "Enterprise.h"
#include "Meeting.h"

using namespace std;

class DataManager {
private:
    vector<Student> students;
    vector<Enterprise> enterprises;
    vector<Meeting> meetings;

public:
    // Student Management
    bool addStudent(const Student &student);
    void displayAllStudents() const;
    bool studentExists(int studentID) const;
    Student* getStudentByID(int studentID);

    // Enterprise Management
    bool addEnterprise(const Enterprise &enterprise);
    void displayAllEnterprises() const;
    bool enterpriseExists(int enterpriseID) const;
    Enterprise* getEnterpriseByID(int enterpriseID);
    Enterprise* getEnterpriseByName(const string &name);

    // Meeting Management
    bool addMeeting(const Meeting &meeting);
    void displayAllMeetings() const;
    bool hasSchedulingConflict(const Meeting &meeting) const;

    // Display sorted meetings
    void listMeetingsForStudent(int studentID) const;
    void listMeetingsForAllEnterprises() const;

    // CV Display
    void displayStudentCV(int studentID) const;

    // File Operations
    void loadStudents(const string &filename);
    void saveStudents(const string &filename) const;
    void loadEnterprises(const string &filename);
    void saveEnterprises(const string &filename) const;
    void loadMeetings(const string &filename);
    void saveMeetings(const string &filename) const;
};

#endif
