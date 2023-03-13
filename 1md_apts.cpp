/**
*Nr 1-9
Laiks 2 000 000 000
Atpūšas, kad simtnieku pozīcijas cipas sakrīt ar nr: 5 un 500-590, 1500-1599 utt


out - k beigu moments, f nr., k nr.
secīgi laikam pieaugot. Ja vienā laika momentā beidz apkalpot vairākus klientus, tad rezultāti jādrukā frizieru numuru secībā.
 **/

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // Open the file
    ifstream file("hair.in");
    // Check if the file was opened successfully
    if (!file.is_open())
    {
        cout << "Failed to open file." << endl;
        return 1;
    }
    

    // Read each line of the file
    // string line;
    // for (int i = 1; getline(file, line); ++i)
    // {
    //     // Output the line to the console
    //     cout << "Line " << i << ": " << line << endl;
    // }
    // int foo;
    // getline(file, foo);

    // Read the first line of the file into an integer variable named "foo"
    int foo;
    file >> foo;

    // Output the first line to the console
    cout << "The first line of the file is: " << foo << endl;

    // Read and output each integer of the file
    int num;
    while (file >> num)
    {
        cout << "Number: " << num << endl;
    }

    
    // string word;
    // while (file >> word)
    // {
    //     // Output the word to the console
    //     cout << "Word: " << word << endl;
    // }


    // Read the first line into a char array
    // const int MAX_LINE_LENGTH = 256; // Maximum line length to read
    // char line[MAX_LINE_LENGTH];
    // file.getline(line, MAX_LINE_LENGTH);
    
    // Output the first line to the console
    // cout << "The first line of the file is: " << line << endl;
    
    // Close the file
    file.close();
    
    return 0;
}





