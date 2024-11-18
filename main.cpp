#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    ifstream inputFile("patient.csv");

    string line;

    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    }

    while (getline(inputFile, line)) {
        cout << line << endl;
    }
}
