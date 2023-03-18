#include <iostream>
#include <fstream>
using namespace std;

// Definition of a Barber struct with an integer value and a pointer to the next Node. Used to construct a linked list.
struct Barber {
    int numB;
    bool onBreak;
    Barber* next;
};

// Traverse the linked list and print out each value
void traverseList(Barber* head) {
    Barber* current = head;
    while (current != nullptr) {
        cout << current->numB << " ";
        cout << current->onBreak << " " << endl;
        current = current->next;
    }
}

// Delete the nodes in the linked list
void deleteList(Barber** headRef) {
    Barber* current = *headRef;
    while (current != nullptr) {
        Barber* temp = current;
        current = current->next;
        delete temp;
    }
    *headRef = nullptr;
}

// Creates a linked-list
void createList(Barber** headRef, int n) {
    *headRef = nullptr;

    // Create the linked list
    for (int i = 1; i <= n; i++) {
        Barber* newNode = new Barber;
        newNode->numB = i;
        newNode->onBreak = false;
        newNode->next = nullptr;

        if (*headRef == nullptr) {
            *headRef = newNode;
        }
        else {
            Barber* current = *headRef;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}

// Function to append a new node to the end of a linked-list.
void addElement(Barber** headRef, int numB) {
    Barber* newNode = new Barber;
    newNode->numB = numB;
    newNode->onBreak = false;
    newNode->next = nullptr;

    if (*headRef == nullptr) {
        *headRef = newNode;
    }
    else {
        Barber* current = *headRef;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Definition of a Client struct with three integer values and a pointer to the next Client.
struct Client {
    int time;
    int numC;
    int duration;
    Client* next;
};

// Traverse the linked list and print out each value
void traverseList(Client* head) {
    Client* current = head;
    while (current != nullptr) {
        cout << "Time: " << current->time << ", ";
        cout << "NumC: " << current->numC << ", ";
        cout << "Duration: " << current->duration << endl;
        current = current->next;
    }
}

// Delete the nodes in the linked list
void deleteList(Client** headRef) {
    Client* current = *headRef;
    while (current != nullptr) {
        Client* temp = current;
        current = current->next;
        delete temp;
    }
    *headRef = nullptr;
}

void appendToList(Client** headRef, int time, int numC, int duration) {
    Client* newNode = new Client;
    newNode->time = time;
    newNode->numC = numC;
    newNode->duration = duration;
    newNode->next = nullptr;

    if (*headRef == nullptr) {
        *headRef = newNode;
    }
    else {
        Client* current = *headRef;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// checks whether the linked list is empty
bool checkIfListIsEmpty(Client* head) {
    if (head == nullptr) {
        cout << "Linked list is empty" << endl;
        return true;
    }
    else {
        cout << "Linked list is not empty" << endl;
        return false;
    }
}

// Definition of a OutputList struct with an integer value and a pointer to the next Node. Used to construct a linked list.
struct OutputList {
    int spentTime;
    int barberNum;
    int clientNum;
    OutputList* next;
};

void traverseList(OutputList* head) {
    OutputList* current = head;
    while (current != nullptr) {
        cout << "Spent Time: " << current->spentTime << ", ";
        cout << "Barber Num: " << current->barberNum << ", ";
        cout << "Client Num: " << current->clientNum << endl;
        current = current->next;
    }
}

void addElement(OutputList** headRef, int spentTime, int barberNum, int clientNum) {
    OutputList* newNode = new OutputList;
    newNode->spentTime = spentTime;
    newNode->barberNum = barberNum;
    newNode->clientNum = clientNum;
    newNode->next = nullptr;

    if (*headRef == nullptr) {
        *headRef = newNode;
    }
    else {
        OutputList* current = *headRef;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteList(OutputList** headRef) {
    OutputList* current = *headRef;
    while (current != nullptr) {
        OutputList* temp = current;
        current = current->next;
        delete temp;
    }
    *headRef = nullptr;
}


void checkBreakTime(Barber* head, int currentTime){
    Barber* current = head;
    int hundrethPlace = (currentTime / 100) % 10;
    while (current != nullptr) {
        if (current->numB == hundrethPlace) {
            /* Barber is on break 
                // - A new list
                - A bool onBreak change
            */
            current->onBreak = true;
            break;
        }
        current = current->next;
    }
}


int main() {
    // CONSTANTS
    long int currentTime = 0;    
    long int maxTime = 2000000000;
    cout << "Max time: " << currentTime << endl;

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

    // Create a linked list of barbers
    Barber* head = nullptr;
    createList(&head, n);
    traverseList(head);
    cout << endl;
    
    // Create a linked list of clients
    Client* head1 = nullptr; 
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

    OutputList* head2 = nullptr;
    while (currentTime<=maxTime)
    {
        // Checks, if there are anymore clients, that need to be serviced
        if (checkIfListIsEmpty(head1) == true){
            cout << "The client list is empty - there are no more clients to service." << endl;
            break;
        } 
        else {
            /*
            List of conditions already met outside while loop:
            All input values are checked, before they are entered into the their respective linked lists. 
            */
            /*
            List of conditions in this while loop: 
            */
            /*
                DONE:
                    1. Time cant exceed 2 000 000 000. DONE, the while loop takes care of this.
                    2. A barber is resting and not taking on clients, if the hundredths place position in of the time variable corresponds to the the barbers own number, i.e. the barber with the number 5 will rest when the time variable is [500-599], [1500-1599], [2500.. 2599], etc. 
                        - Needs a function, that loops through barber list, and changes a bool value or puts the barber in another list, if any of them need to be resting. DONE, function checkBreakTime does this, changes a bool value.


                    

                    6. Knowing the arrival time, the number (customers number) and service time (duration of the service) of the customer, output the end of service moments time, the barbers number (who sercived the customer) and the customers number (the number of the customer, who was serviced). Outputting should be done sequentially, as in, according to the times growing order. If several clients service ends at the exact same time moment, then the result of these services are outputted according to the growing order of the barbers (that serviced these customers) numbers.
                        - The output lists does this, by each line being an element in the linked list. DONE, this functionality is outside this loop.
            */
            // Start of the else
            checkBreakTime(head, currentTime);
            traverseList(head);
            break;
            /*
                NOT DONE:
                    3. Klients ir jāapkalpo nekavējoties, ja eksistē brīvs frizieris un tam nav nekādu ierobežojumu veikt šo darbu.
                        - If a barber has finished servicing his client, he is immediately lower precedence than every other barber in the barbershop. This means, that, when he is freed up, he is pushed to the end of the list (not considering every other aspect of how barbers are chosen).
                    
                    Customers are waiting in an honest and "tight" (meaning punctual) line. Only one client can come in at a certain time momemt. The receptionist (in the case of C++ and the context of this exercise, an algorithm) shall immediately determine the customers number (which corresponds to the customer order of arrival) thats between 1 and 200000 and the needed service time for the customers, that's between 1-900.

                    If there is an unserviced customer and several free barbers at the same time, then: preference is for a barber who has been without a customer for the longest amount of time (measured from the end of last serviced customer). Also, if two or more barbers have been waiting the same amount of time, then the barber who has the smaller number services the customer.
                        - The barbers might need another variable, that tracks the moment they finished servicing their last customer. This means, that we cant rely on the barber at the start of the list being the barber, that hasnt worked the longest.

                    4. Frizierim, beidzot darbu pie kārtējā klienta, ar nākošo laika momentu jāmēģina apkalpot kādu klientu.
                        - An if condition, that checks, if clients needed service time is less than the remaining time between the first barbers in the barbers list remaining time, till the next hundreth starts.
                        If remaining time+service needed time doesn't overslap break time
                            - incramentally dividing the service time, if its big enough, and checking it in a loop, if the task cannot be completed. This will be inside the currentTime>=100 condition. 

                    5. More accurate specification: customer C1 arrives at time T1 and needs service time S1 (service time means that it will take S1 amount of time, for the customer to be serviced). There's a free barber B1. Accordingly, the service takes place at the time interval of [T1...T1+(S1-1)]. The service is finished at the time: T1 + S1-1. If client C2 has already arrived before or at exactly at the time moment T1 + S1, then the barber B1 can start servicing client C2 at the time T1 + S1.

            */
            /* algorithm code 
            Take barber, get client, when everything done, write result into output list, delete client, repeat. Break time is checked on each repeat.
                - Need to sort out barber sequence and the order, that they take their respective clients.
            
            */
            return 1;
        }

    }

    
    // Traverse the list and write values to file. Dont know if this can be a function.
    OutputList* current = head2;
    while (current != nullptr) {
        output << current->spentTime << " ";
        output << current->barberNum << " ";
        output << current->clientNum << endl;
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


// int main() {
//     // CONSTANTS
//     long int MAX_TIME = 2000000000;
//     cout << "Max time: " << MAX_TIME << endl;

//     // Open the files
//     ifstream input("hair.in");
//     ofstream output("hair.out");

//     // Check if the file was opened successfully
//     if (!input.is_open())
//     {
//         cout << "Failed to open input file." << endl;
//         return 1;
//     }
//     if (!output.is_open())
//     {
//         cout << "Failed to open output file." << endl;
//         return 1;
//     }

//     int n;
//     input >> n;
//     if (n < 1 || n>9){
//         cout << "Number of barbers has be between 1-9." << endl;
//         return 1;  
//     } 
//     // Output the first line to the console
//     cout << "The number of barbers: " << n << endl;

//     // Create a linked list of barbers
//     Barber* head = nullptr;
//     createList(&head, n);
//     traverseList(head);
//     cout << endl;
    
//     // Create a linked list of clients
//     Client* head1 = nullptr; 
//     int time; 
//     int num; 
//     int duration;
//     while (input >> time >> num >> duration) {
//         if (time == 0) break;
//         if (num >= 1 && num <= 200000 && duration >= 1 && duration <= 900) {
//             appendToList(&head1, time, num, duration);
//         } else {
//             cout << "Error: Invalid input value for num or duration." << endl;
//             return 1;
//         }
//     }
//     traverseList(head1);

//     // Close the input file
//     input.close();

//     OutputList* head2 = nullptr;
//     while (true)
//     {
//         /* code */
//         break;
//     }

//     // Traverse the list and write values to file
//     OutputList* current = head2;
//     while (current != nullptr) {
//         output << current->spentTime << " ";
//         output << current->barberNum << " ";
//         output << current->clientNum << endl;
//         current = current->next;
//     }

//     // Close the output file
//     output.close();

//     // Free memory
//     deleteList(&head);
//     deleteList(&head1);
//     deleteList(&head2);
//     return 0;
// }

    // addElement(&head2, 20, 1, 1);
    // addElement(&head2, 50, 1, 3);
    // addElement(&head2, 70, 2, 2);




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