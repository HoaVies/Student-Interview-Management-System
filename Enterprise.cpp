#include "Enterprise.h"
#include <iostream>
#include <sstream>

using namespace std;

// Initialize enterprise ID, name, address, contact name and phone
Enterprise::Enterprise(int id, string n, string addr, string contact, string phone)
    : enterpriseID(id), name(n), address(addr), contactName(contact), contactPhone(phone) {}

// Display the enterprise
void Enterprise::displayEnterprise() const {
    cout << "-----------------------------------" << endl;
    cout << "Enterprise ID: " << enterpriseID << endl;
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Contact Name: " << contactName << endl;
    cout << "Contact Phone: " << contactPhone << endl;
    cout << "-----------------------------------" << endl;
}

// Serialize enterprise data
string Enterprise::serialize() const {
    stringstream ss;
    //Each field is separated by '|'
    ss << enterpriseID << "|" << name << "|" << address << "|" << contactName << "|" << contactPhone;
    return ss.str();
}

// Deserialize enterprise data
void Enterprise::deserialize(const string &data) {
    // Use a stringstream to parse the input data
    stringstream ss(data);
    string token;
    
    // Read the first token as the enterprise ID and convert to integer
    try {
        getline(ss, token, '|');
        enterpriseID = stoi(token);
    }
    catch (const invalid_argument &e) {
        cerr << "Error: Invalid enterpriseID '" << token << "'" << endl;
        throw;
    }

    // Read the remaining tokens as the enterprise name, address, contact name and phone
    getline(ss, name, '|');
    getline(ss, address, '|');
    getline(ss, contactName, '|');
    getline(ss, contactPhone, '|');
}
