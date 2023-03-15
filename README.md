# apts-1md-mati
University homework.

TODO:
Plan:
- Open and read file DONE, need to actually read hair.in correctly and
    - Make a linked list with the number of barbers as the first line of the file
    - Needs to make a new linked list with the customers, storing: time, when they arrived, their number and the amount of time, that it would take, for them to have their haircut.
- Make a linked list of the barbers DONE, need to be able to make another linked list, where we store the busy barbers, where
    - We store the number of the barber, the customer the barber is currently working with, all the time variables and so on. NOTE: The free barbers will be stored in the original linked-list, with only their number as the value, for now - might need to add how many customers he has worked, time worked, last customer and so on. 
- Make a linked list of the customers TODO
- Global variable for the time TODO
- Run the program (misc functions) TODO update




Need a function that removes a single element from a linked list
Need to write down every condition and edge case that can happen, then ask gpt to make a solution for each one.
                                                                                                                                                                                
I have this code:
#include <iostream>
#include <fstream>
using namespace std;

// Definition of a Node struct with an integer value and a pointer to the next Node. Used to construct a linked list.
struct Node {
    int value;
    Node* next;
};

// Traverse the linked list and print out each value
void traverseList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
}

// Delete the nodes in the linked list
void deleteList(Node** headRef) {
    Node* current = *headRef;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    *headRef = nullptr;
}

// Creates a linked-list
void createList(Node** headRef, int n) {
    *headRef = nullptr;

    // Create the linked list
    for (int i = 1; i <= n; i++) {
        Node* newNode = new Node;
        newNode->value = i;
        newNode->next = nullptr;

        if (*headRef == nullptr) {
            *headRef = newNode;
        }
        else {
            Node* current = *headRef;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}

// Function to append a new node to the end of a linked-list.
void addElement(Node** headRef, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (*headRef == nullptr) {
        *headRef = newNode;
    }
    else {
        Node* current = *headRef;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Definition of a Node struct with three integer values and a pointer to the next Node.
struct Node1 {
    int time;
    int num;
    int duration;
    Node1* next;
};

// Traverse the linked list and print out each value
void traverseList(Node1* head) {
    Node1* current = head;
    while (current != nullptr) {
        std::cout << "Time: " << current->time << ", ";
        std::cout << "Num: " << current->num << ", ";
        std::cout << "Duration: " << current->duration << std::endl;
        current = current->next;
    }
}

// Delete the nodes in the linked list
void deleteList(Node1** headRef) {
    Node1* current = *headRef;
    while (current != nullptr) {
        Node1* temp = current;
        current = current->next;
        delete temp;
    }
    *headRef = nullptr;
}

void appendToList(Node1** headRef, int time, int num, int duration) {
    Node1* newNode = new Node1;
    newNode->time = time;
    newNode->num = num;
    newNode->duration = duration;
    newNode->next = nullptr;

    if (*headRef == nullptr) {
        *headRef = newNode;
    }
    else {
        Node1* current = *headRef;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int main() {
    // Global variables
    long int time = 2000000000;
    cout << "Max time: " << time << endl;

    // Open the files
    ifstream input("hair.in");
    ofstream output("hair.out");

    // Check if the file was opened successfully
    if (!input.is_open())
    {
        cout << "Failed to open input file." << endl;
        return 1;
    }
    if (!output.is_open())
    {
        cout << "Failed to open output file." << std::endl;
        return 1;
    }

    int n;
    input >> n;
    // Output the first line to the console
    cout << "The number of barbers: " << n << endl;
    output << n << endl;
    // Create a linked list of barbers
    Node* head = nullptr;
    createList(&head, n);
    traverseList(head);
    cout << endl;
    deleteList(&head);

    int num;
    while (input >> num)
    {
        cout << "Number: " << num << endl;
        output << num << endl;
    }
    input.close();
    
    return 0;
}
Concerning the while(input >> num) loop: 
Imagine if the input hair.in file is written as follows:
2
11 1 10
21 2 50
31 3 20
0

The first line is the number of barbers or the number of elements inside a linked list (Node).
The second, third and fourth lines are for the client linked list (Node1), as in, the first number is the "time", the second is the clients number "num", and the third number is the "duration".
The fifth and final line is "0", which indicates that the file has ended.

I need you to modify the while loop, so that the values are read into a Node1 linked list. Each element would have the "time", "num" and "duration" values. Can you try to write an example?