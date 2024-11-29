#include "functions.h"

int main() {
    vector<patient> patients;

    readDataFile("patient.csv", "output.txt", patients);
    cout << endl;
    int count = 1;
    for (int i = 0; i < patients.size(); i++) {
        cout << count << ": " << patients[i].firstName << " " << patients[i].lastName << " needs to go to: " << patients[i].clinicName << endl;
        count += 1;
    }
}
