//
// Created by nicho on 11/18/2024.
//

#include "functions.h"

#include <vector>

bool isDigits(string str1) {
    return (str1.find_first_not_of("1234567890") == string::npos);
}

void Logger::logMessage(const string& message) {
    if (outputFile.is_open()) {
        outputFile << message << endl;
    }
}

void readDataFile(const string &patientFile, const string &errFile, vector<patient> &patients) {
    ifstream inputFile(patientFile);
    ofstream outputFile(errFile);
    string line;
    Logger logger("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        logger.logMessage("Error opening file\n");
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
            logger.logMessage("ERROR: Clinic Name is not valid for patient: " + tokens[1] + " " + tokens[2] + "\n");
            continue;
        }
        tempPatient.firstName = tokens[1];
        tempPatient.lastName = tokens[2];
        tempPatient.type = 'R';
        if (isDigits(tokens[3])) {
            tempPatient.SSN = stoi(tokens[3]);
        }
        else {
            logger.logMessage("ERROR: Non digit in SSN input file for patient: " + tokens[1] + " " + tokens[2] + "\n");
            continue;
        }
        patients.push_back(tempPatient);
    }
    inputFile.close();
    outputFile.close();
}

void Clinic::setHead(ClinicPatient* cP) {
    if (head == nullptr) {
        head = cP;
    }
}

ClinicPatient* Clinic::getHead() {
    return this->head;
}

int Clinic::addPatient(ClinicPatient& patientToAdd) {
    // Case: Adding the first patient
    if (head == nullptr) {
        head = new ClinicPatient(patientToAdd); // Allocate on the heap
        tail = head; // Set tail to the same node as head
        currentPatients++;
        logger.logMessage("Successfully added patient: " + patientToAdd.cPatient.firstName + " " + patientToAdd.cPatient.lastName + " to: " + clinicName);
        return 0;
    }

    // Case: Clinic at capacity
    if (currentPatients >= capacity) {
        logger.logMessage("ERROR: Too many patients in: " + clinicName + " ::: " + patientToAdd.cPatient.firstName + " " + patientToAdd.cPatient.lastName + " was not added");
        return -1;
    }

    // Case: Adding to the existing list
    // Create a new node and link it to the tail
    tail->next = new ClinicPatient(patientToAdd);
    tail = tail->next; // Update the tail to point to the new node

    currentPatients++;
    logger.logMessage("Successfully added patient: " + patientToAdd.cPatient.firstName + " " + patientToAdd.cPatient.lastName + " to: " + clinicName);
    return 0;
}

void printMenu1() {
    cout << "\tKC RESEARCH HOSPITAL\n";
    cout << "1: Heart Clinic\n";
    cout << "2: Pulmonary Clinic\n";
    cout << "3: Plastic Surgery\n";
    cout << "4: Quit\n";

    cout << "Please enter the clinic of interest: ";
}

void printMenu2(const string& clinicName) {
    cout << "Welcome to the " << clinicName << " \n";
    cout << "1: - Add Patient\n";
    cout << "2: - Add Critical Patient\n";
    cout << "3: - Take out Patient for Operation\n";
    cout << "4: - Cancel Patient\n";
    cout << "5: - List Patients in Queue\n";
    cout << "6: - Change Department or exit\n";

    cout << "Please enter your choice: ";
}

void checkInPatient(Clinic* clinic) {
    Logger logger("output.txt");
    string fName, lName;
    int ssNum;
    try {
        cout << "Enter Patient's First Name: " << endl;
        cin >> fName;
        cout << "Enter Patient's Last Name: " << endl;
        cin >> lName;
        cout << "Enter Patient's SSN: " << endl;
        cin >> ssNum;

        if (fName.empty() || lName.empty()) {
            throw exception();
        }
    }
    catch(...) {
        logger.logMessage("Error: Invalid Entry. Patient: " + fName + " " + lName + " was not added");
    }

    patient tempPatient;
    tempPatient.firstName = fName;
    tempPatient.lastName = lName;
    tempPatient.SSN = ssNum;
    tempPatient.type = 'R';
    ClinicPatient tempCPatient(tempPatient);
    int status;
    status = clinic->addPatient(tempCPatient);

    if (status == 0) {
        cout << clinic->clinicName << " Patient (Regular): " << fName << " " << lName << " was added to the waiting room" << endl;
    }
    else {
        cout << "Error: " << clinic->clinicName << " Patient (Regular): " << fName << " " << lName << " was not added to the waiting room" << endl;
    }
}

void printClinicPatients(Clinic *clinic) {
    const ClinicPatient* tempCPatient = clinic->getHead();
    if (clinic->getHead() != nullptr) {
        cout << "Our Head's name is: " << clinic->getHead()->cPatient.firstName << " " << clinic->getHead()->cPatient.lastName << endl;
    }
    while (tempCPatient != nullptr) {
        cout << tempCPatient->cPatient.firstName << " " << tempCPatient->cPatient.lastName << " " << tempCPatient->cPatient.SSN << " " << tempCPatient->cPatient.type << endl;
        tempCPatient = tempCPatient->next;
    }
    cout << endl;
}
