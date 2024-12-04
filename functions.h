//
// Created by nicho on 11/18/2024.
//
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H



struct patient {
    string clinicName;
    string firstName;
    string lastName;
    char type;
    int SSN;
};

void readDataFile(const string &patientFile, const string &errFile, vector<patient> &patients);
bool isDigits(string s);

class Logger {
    ofstream outputFile;
public:
    explicit Logger(const string& oF) {
        outputFile.open(oF, ios::app);
        if (!outputFile.is_open()) {
            outputFile << "Error opening file" << endl;
            return;
        }
    }
    ~Logger() {
        if (outputFile.is_open()) {
            outputFile.close();
        }
    }
    void logMessage(const string& message);
};

class ClinicPatient {

public:
    patient cPatient;
    ClinicPatient* next;

    explicit ClinicPatient(const patient &cP) {
        cPatient = cP;
        next = nullptr;
    }
    ~ClinicPatient() {
        next = nullptr;
    }

};

class Clinic {
private:
    ClinicPatient* head;
    Logger logger; // Logger as a member

public:
    int capacity;
    ClinicPatient* tail;
    string clinicName;
    int currentPatients;
    // Constructor declaration
    Clinic() : logger("output.txt") {
        head = nullptr;
        tail = nullptr;
        clinicName = "";
        currentPatients = 0;
        capacity = 10;
    }

    explicit Clinic(const string& name): logger("output.txt") {
        head = nullptr;
        tail = nullptr;
        clinicName = name;
        currentPatients = 0;
        capacity = 10;
    }

    void setHead(ClinicPatient* cP);
    ClinicPatient* getHead();

    // Method declarations
    int addPatient(ClinicPatient& patientToAdd);
    int addCriticalPatient(ClinicPatient& patientToAdd);
    void removePatient();
    void removePatient(int ssn);
};

void printMenu1();
void printMenu2(const string& clinicName);

void checkInPatient(Clinic* clinic);
void checkInCriticalPatient(Clinic* clinic);
void printClinicPatients(Clinic* clinic);
void logClinicPatients(Clinic *clinic, ofstream& oFile);


#endif //FUNCTIONS_H
