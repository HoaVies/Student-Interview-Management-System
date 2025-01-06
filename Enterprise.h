#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include <string>

using namespace std;

class Enterprise {
private:
    int enterpriseID; // Unique ID for the enterprise
    string name;
    string address;
    string contactName;
    string contactPhone;

public:
    // Constructors
    Enterprise() : enterpriseID(0) {}
    Enterprise(int id, string n, string addr, string contact, string phone);

    void displayEnterprise() const;

    // Serialization and deserialization
    string serialize() const;
    void deserialize(const string &data);

    // Getters
    int getEnterpriseID() const { return enterpriseID; }
    string getName() const { return name; }
};

#endif
