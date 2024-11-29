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
    int SSN;
};

void readDataFile(const string &patientFile, const string &errFile, vector<patient> &patients);



#endif //FUNCTIONS_H
