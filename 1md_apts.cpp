/**
Nr 1-9
Laiks 2 000 000 000
Atpūšas, kad simtnieku pozīcijas cipas sakrīt ar nr: 5 un 500-590, 1500-1599 utt
out - k beigu moments, f nr., k nr.
secīgi laikam pieaugot. Ja vienā laika momentā beidz apkalpot vairākus klientus, tad rezultāti jādrukā frizieru numuru secībā.
**/

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

struct Node2 {
    int spentTime;
    int barberNum;
    int clientNum;
    Node2* next;
};

void traverseList(Node2* head) {
    Node2* current = head;
    while (current != nullptr) {
        std::cout << "Spent Time: " << current->spentTime << ", ";
        std::cout << "Barber Num: " << current->barberNum << ", ";
        std::cout << "Client Num: " << current->clientNum << std::endl;
        current = current->next;
    }
}

void addElement(Node2** headRef, int spentTime, int barberNum, int clientNum) {
    Node2* newNode = new Node2;
    newNode->spentTime = spentTime;
    newNode->barberNum = barberNum;
    newNode->clientNum = clientNum;
    newNode->next = nullptr;

    if (*headRef == nullptr) {
        *headRef = newNode;
    }
    else {
        Node2* current = *headRef;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteList(Node2** headRef) {
    Node2* current = *headRef;
    while (current != nullptr) {
        Node2* temp = current;
        current = current->next;
        delete temp;
    }
    *headRef = nullptr;
}

int main() {
    // Global variables
    long int MAX_TIME = 2000000000;
    cout << "Max time: " << MAX_TIME << endl;

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
        cout << "Failed to open output file." << endl;
        return 1;
    }

    int n;
    input >> n;
    if (n < 1 || n>9){
        cout << "Number of barbers has be between 1-9." << endl;
        return 1;  
    } 
    // Output the first line to the console
    cout << "The number of barbers: " << n << endl;
    // output << n << endl;

    // Create a linked list of barbers
    Node* head = nullptr;
    createList(&head, n);
    traverseList(head);
    cout << endl;
    
    // Create a linked list of clients
    Node1* head1 = nullptr; 
    int time; 
    int num; 
    int duration;
    while (input >> time >> num >> duration) {
        if (time == 0) break;
        if (num >= 1 && num <= 200000 && duration >= 1 && duration <= 900) {
            appendToList(&head1, time, num, duration);
        } else {
            cout << "Error: Invalid input value for num or duration." << endl;
            return 1;
        }
    }
    traverseList(head1);
    // Close the input file
    input.close();



    Node2* head2 = nullptr;
    while (true)
    {
        /* code */
        break;
    }
    addElement(&head2, 20, 1, 1);
    addElement(&head2, 50, 1, 3);
    addElement(&head2, 70, 2, 2);

    // Traverse the list and write values to file
    Node2* current = head2;
    while (current != nullptr) {
        output << current->spentTime << " ";
        output << current->barberNum << " ";
        output << current->clientNum << std::endl;
        current = current->next;
    }

    // Close the output file
    output.close();

    // Free memory
    deleteList(&head);
    deleteList(&head1);
    deleteList(&head2);
    return 0;
}






    // int num;
    // while (input >> num)
    // {
    //     cout << "Number: " << num << endl;
    //     output << num << endl;
    // }
    // input.close();

// // DEMO
// void seperateLists(){
//     // Create the first linked-list
//     Node* head1 = nullptr;
//     createList(&head1, 5);

//     // Create the second linked-list
//     Node* head2 = nullptr;
//     addElement(&head2, 10);
//     addElement(&head2, 20);
//     addElement(&head2, 30);

//     // Add an element from list1 to list2
//     Node* current = head1;
//     while (current != nullptr && current->value != 3) {
//         current = current->next;
//     }

//     if (current != nullptr) {
//         addElement(&head2, current->value);
//     }
// }

// // DEMO
// void demoClientList(){
//     Node1* head = nullptr;
//     appendToList(&head, 10, 1, 100);
//     appendToList(&head, 20, 2, 200);
//     appendToList(&head, 30, 3, 300);
//     traverseList(head);
//     deleteList(&head);

// }