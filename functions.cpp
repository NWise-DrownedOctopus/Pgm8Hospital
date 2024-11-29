//
// Created by nicho on 11/18/2024.
//

#include "functions.h"

#include <vector>

bool isDigits(string str1) {
    return (str1.find_first_not_of("1234567890") == string::npos);
}

void readDataFile(const string &patientFile, const string &errFile, vector<patient> &patients) {
    ifstream inputFile(patientFile);
    ofstream outputFile(errFile);
    string line;

    if (!inputFile.is_open() || !outputFile.is_open()) {
        outputFile << "Error opening file" << endl;
        return;
    }

    patient tempPatient;
    while (getline(inputFile, line)) {
        istringstream  iss(line);
        string token;
        char comma = ',';
        vector<string> tokens;
        while (getline(iss, token, comma)) {
            tokens.push_back(token);
        }
        if (tokens[0] == "PC" || tokens[0] == "PSC" || tokens[0] == "HC") {
            tempPatient.clinicName = tokens[0];
        }
        else {
            outputFile << "Error: Clinic Name is not valid for patient: " << tokens[1] << " " << tokens[2] << endl;
            continue;
        }
        tempPatient.firstName = tokens[1];
        tempPatient.lastName = tokens[2];
        if (isDigits(tokens[3])) {
            tempPatient.SSN = stoi(tokens[3]);
        }
        else {
            outputFile << "Error: Non digit in SSN input file for patient: " << tokens[1] << " " << tokens[2] << endl;
            continue;
        }
        patients.push_back(tempPatient);
    }
    inputFile.close();
    outputFile.close();
}
