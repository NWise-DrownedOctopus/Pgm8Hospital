#include "functions.h"

using namespace std;

int main() {
    vector<patient> patients;
    Logger logger("output.txt");

    readDataFile("patient.csv", "output.txt", patients);

    Clinic heartClinic("Heart Clinic");
    Clinic pulmonaryClinic("Pulmonary Clinic");
    Clinic plasticSurgeryClinic("Plastic Surgery Clinic");

    for (int i = 0; i < patients.size(); i++) {
        if (patients[i].clinicName == "HC") {
            ClinicPatient TCP(patients[i]);
            heartClinic.addPatient(TCP);
        }
        else if (patients[i].clinicName == "PC") {
            ClinicPatient tempCPatient(patients[i]);
            pulmonaryClinic.addPatient(tempCPatient);
        }
        else if (patients[i].clinicName == "PSC") {
            ClinicPatient tempCPatient(patients[i]);
            plasticSurgeryClinic.addPatient(tempCPatient);
        }
    }

    while (true) {
        printMenu1();
        string userInput;
        cin >> userInput;
        cout << endl;

        if (!isDigits(userInput)) {
            cout << "ERROR: Non digit Entry" << endl;
            continue;
        }

        Clinic* clinicChoice;
        if (userInput == "1") { clinicChoice = &heartClinic;}
        else if (userInput == "2") { clinicChoice = &pulmonaryClinic;}
        else if (userInput == "3") { clinicChoice = &plasticSurgeryClinic;}
        else if (userInput == "4") { break; }
        else {
            cout << "ERROR: Invalid Input" << endl;
            continue;
        }

        while (true) {
            printMenu2(clinicChoice->clinicName);
            string userInput2;
            cin >> userInput2;
            cout << endl;
            if (!isDigits(userInput2)) {
                cout << "ERROR: Non digit Entry" << endl;
                continue;
            }

            if (userInput2 == "1") {
                checkInPatient(clinicChoice);
            }
            else if (userInput2 == "2") {
                checkInCriticalPatient(clinicChoice);
            }
            else if (userInput2 == "3") {
                clinicChoice->removePatient();
            }
            else if (userInput2 == "4") {
                cout << "Enter Patient SSN: ";
                int userInput3;
                cin >> userInput3;
                clinicChoice->removePatient(userInput3);
            }
            else if (userInput2 == "5") {
                printClinicPatients(clinicChoice);
            }
            else if (userInput2 == "6") { break; }
            else {
                cout << "ERROR: Invalid Input" << endl;
            }
        }
    }

    cout << "Now Exiting Program. Thank You." << endl;
    ofstream patientLog;
    patientLog.open("patientLog.csv");
    if (!patientLog.is_open()) {
        logger.logMessage("Error opening patient log\n");
        return 0;
    }

    patientLog << "Patient List " << endl;
    logClinicPatients(&heartClinic, patientLog);
    logClinicPatients(&pulmonaryClinic, patientLog);
    logClinicPatients(&plasticSurgeryClinic, patientLog);

    patientLog.close();

    return 0;
}
