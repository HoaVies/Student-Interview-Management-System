#ifndef MEETING_H
#define MEETING_H

#include <string>

using namespace std;

class Meeting {
private:
    int meetingID; // Unique ID for the meeting
    int studentID;
    int enterpriseID;
    string date;
    string startTime;
    string endTime;

public:
    // Constructors
    Meeting() : meetingID(0), studentID(0), enterpriseID(0) {}
    Meeting(int id, int sID, int eID, string d, string start, string end);

    void displayMeeting() const;

    // Serialization and deserialization
    string serialize() const;
    void deserialize(const string &data);

    // Getters
    int getMeetingID() const { return meetingID; }
    int getStudentID() const { return studentID; }
    int getEnterpriseID() const { return enterpriseID; }
    string getDate() const { return date; }
    string getStartTime() const { return startTime; }
    string getEndTime() const { return endTime; }
};

#endif
