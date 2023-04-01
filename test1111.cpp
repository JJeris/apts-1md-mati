#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream input("input.txt");
    int n, time, clientNum, duration;

    // Read the first line and store it in n
    input >> n;
    input.ignore(); // ignore the newline character

    // Read the second line using getline and extract the integer values
    string line;
    getline(input, line);
    istringstream iss(line);

    string value;
    getline(iss, value, ' ');
    time = stoi(value);

    getline(iss, value, ' ');
    clientNum = stoi(value);

    getline(iss, value);
    duration = stoi(value);

    input.close();

    // Output the values to the console to verify they were read correctly
    cout << "n = " << n << endl;
    cout << "time = " << time << endl;
    cout << "clientNum = " << clientNum << endl;
    cout << "duration = " << duration << endl;

    return 0;
}
