#include <iostream>
#include <fstream>
using namespace std;

// Definition of a Barber struct with an integer value and a pointer to the next Node. Used to construct a linked list.
struct Barber {
    int numB;
    int lastWorkTime = 0;
    int client = 0;
    bool busy = false;
    Barber* next;
};

// Traverse the linked list and print out each value
void traverseList(Barber* head) {
    Barber* current = head;
    while (current != nullptr) {
        cout << current->numB << " ";
        cout << current->lastWorkTime << " ";
        cout << current->busy << " " << endl;
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

// Function to push the first node to the back of a linked-list.
void pushFirstToBack(Barber** headRef) {
    if (*headRef == nullptr) {
        return;
    }

    Barber* first = *headRef;
    *headRef = first->next;

    Barber* current = *headRef;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = first;
    first->next = nullptr;
}

// This function sorts a linked list of Barber nodes in ascending order based on their lastWorkTime and numB attributes. It uses a selection sort algorithm to find the minimum element from the current node to the end of the list, and swaps it with the current node if necessary. The function takes a pointer to the head of the linked list as input and modifies the list in place.
void sortList(Barber** headRef) {
    Barber* current = *headRef;
    Barber* min;

    while (current != nullptr) {
        // Find the minimum element from current to the end of the list
        min = current;
        Barber* innerCurrent = current->next;
        while (innerCurrent != nullptr) {
            
            

            // if (innerCurrent->busy && !min->busy ||
            //     (innerCurrent->busy == min->busy && innerCurrent->lastWorkTime < min->lastWorkTime) ||
            //     (innerCurrent->busy == min->busy && innerCurrent->lastWorkTime == min->lastWorkTime && innerCurrent->numB < min->numB)) {
            //         min = innerCurrent;
            // }
            if (!innerCurrent->busy && min->busy ||
                (innerCurrent->busy == min->busy && innerCurrent->lastWorkTime < min->lastWorkTime) ||
                (innerCurrent->busy == min->busy && innerCurrent->lastWorkTime == min->lastWorkTime && innerCurrent->numB < min->numB)) {
                min = innerCurrent;
            }


            innerCurrent = innerCurrent->next;
        }
        // Swap the minimum element with the current element
        if (min != current) {
            swap(current->numB, min->numB);
            swap(current->lastWorkTime, min->lastWorkTime);
            swap(current->busy, min->busy);
            swap(current->client, min->client);
        }
        current = current->next;
    }
}

// This function finds the smallest element in a linked list that is not currently on break.
// Barber* findNextAvailableBarber(Barber* head) {
//     sortList(&head);
//     Barber* current = head;
//     while (current != nullptr) {
//         if (current->onBreak == false) {
//             return current;
//         }
//         current = current->next;
//     }
//     return nullptr;
// }


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
        // cout << "Linked list is empty" << endl;
        return true;
    }
    else {
        // cout << "Linked list is not empty" << endl;
        return false;
    }
}

void deleteFirstElement(Client** headRef) {
    if (checkIfListIsEmpty(*headRef) == true) {
        return;
    }
    Client* temp = *headRef;
    *headRef = (*headRef)->next;
    delete temp;
}

// Definition of a OutputList struct with an integer value and a pointer to the next Node. Used to construct a linked list.
//! We need this, so we can sort the client list by the their end of service time. IDK how else this would be done.
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

// This function takes a reference to the head of an OutputList and sorts the list in ascending order based on the spentTime variable and barberNum. It uses a modified selection sort algorithm where the minimum element is repeatedly found and swapped with the current element.
/*
void sortList(OutputList** headRef) {
    if (*headRef == nullptr || (*headRef)->next == nullptr) {
        // List is already sorted (or empty)
        return;
    }

    OutputList* sortedList = nullptr;
    OutputList* current = *headRef;

    while (current != nullptr) {
        OutputList* next = current->next;

        if (sortedList == nullptr || current->spentTime < sortedList->spentTime) {
            // Insert at the beginning of the sorted list
            current->next = sortedList;
            sortedList = current;
        }
        else {
            // Traverse the sorted list to find the correct position to insert
            OutputList* temp = sortedList;
            while (temp->next != nullptr && current->spentTime >= temp->next->spentTime) {
                temp = temp->next;
            }
            // Insert the current node at the correct position in the sorted list
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    // Update the head of the original list to point to the sorted list
    *headRef = sortedList;
}
*/
// Sort of works
//! Still have to figure out how to track time properly and reflect that in the code
/*
For example, this doesn't work properly.
2
10 1 10
11 1 9
12 1 8
0
*/
void sortList(OutputList** headRef) {
    if (*headRef == nullptr || (*headRef)->next == nullptr) {
        // List is already sorted (or empty)
        return;
    }

    OutputList* sortedList = nullptr;
    OutputList* current = *headRef;

    while (current != nullptr) {
        OutputList* next = current->next;

        if (sortedList == nullptr || current->spentTime < sortedList->spentTime ||
            (current->spentTime == sortedList->spentTime && current->barberNum < sortedList->barberNum)) {
            // Insert at the beginning of the sorted list
            current->next = sortedList;
            sortedList = current;
        }
        else {
            // Traverse the sorted list to find the correct position to insert
            OutputList* temp = sortedList;
            while (temp->next != nullptr && (current->spentTime > temp->next->spentTime ||
                                              (current->spentTime == temp->next->spentTime && current->barberNum > temp->next->barberNum))) {
                temp = temp->next;
            }
            // Insert the current node at the correct position in the sorted list
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    // Update the head of the original list to point to the sorted list
    *headRef = sortedList;
}






bool valid(int barberNum, int time, int duration){
    int hundrethPlace = (time / 100) % 10;
    int hundrethPart = time % 1000;
    if (hundrethPlace == barberNum){
        return false;
    }
    else {
        int endTime = hundrethPart + duration - 1;
        if (hundrethPart < barberNum*100 && endTime >= barberNum*100) {
            return false;
        }
        else if(hundrethPart > (barberNum*100) + 99 && endTime >= barberNum*100+1000) {
            return false;
        }
        return true;
    }
}

int main() {
    // Gloabl variabes
    long int currentTime = 0;    

    // Open the files
    ifstream input("hair.in");
    ofstream output("hair.out");

    // Create a linked list of barbers
    int n;
    input >> n;
    Barber* head = nullptr;
    createList(&head, n);

    int time; 
    int clientNum; 
    int duration;
    input >> time >> clientNum >> duration;

    Barber* current = head;

    // Atrod derīgo barberi.
    while(true) {
        if(current == nullptr){
            // exit(1);
            time = (((time/100)*100)+100);
            currentTime = time;
            current = head;
        }
        if (valid(current->numB, time, duration)){
            // klientu, laiku, busy.
            current->lastWorkTime = time+duration-1;
            current->client = clientNum;
            current->busy = true;
            sortList(&head); // aiznemts, vai nē, pēc laika, un tad nr.
            break;
        } 
        else {
            // nederīgs
            current = current->next;
            continue;
        }        
    }

    while (input >> time >> clientNum >> duration) {
        if (time == 0) break;
        current = head;
        if (time < currentTime+1){
            time = currentTime+1;
            currentTime = time;
        }
        // Atbrīvot busy: salīdzini currentTime ar vinu lastWorkTime
        while(current != nullptr && current->lastWorkTime < time){
            if (current->busy == true) {
                current->busy = false;
                output << current->lastWorkTime << " " << current->numB << " " << current->client << endl;
            }
            current = current->next;
        }
        current = head;
        // cout << boolalpha << current->busy << endl << current->numB << endl << current->client << endl << current->lastWorkTime << endl << current->next << endl; 
        // cout << boolalpha << current->next->busy << endl << current->next->numB << endl << current->next->client << endl << current->next->lastWorkTime << endl << current->next << endl; 
        bool busyExists = false;
        while(true) {
           
            if(current == nullptr){
                // tikai brivie
                // tikai aiznemtie
                // abi  
                if (busyExists == false){
                    // All not busy
                    time = (((time/100)*100)+100);
                    currentTime = time;
                    current = head;
                }
                else if (busyExists == true){
                    current = head;
                    if (current->busy == true){
                        // All busy
                        currentTime = current->lastWorkTime+1;
                        time = currentTime;
                    }
                    else {
                        while (current->busy != true) {
                            current = current->next;
                        }
                        // Both busy
                        if (time/100*100+100<current->lastWorkTime+1) {
                            currentTime = time/100*100+100;
                            time = currentTime;    
                        }
                        else {
                            currentTime = current->lastWorkTime+1;
                            time = currentTime;
                        }
                    }
                }

                current = head;
                    while(current != nullptr && current->lastWorkTime < time){
                        if (current->busy == true) {
                            if (current->next == nullptr) {
                                busyExists = false;
                            }
                            current->busy = false;
                            output << current->lastWorkTime << " " << current->numB << " " << current->client << endl;
                        
                            
                        }
                        current = current->next;
                    }
                    current = head;
            }
            if (current->busy == true){
                busyExists = true;
                current = nullptr;
                continue;
            }
            if (current->busy == false && valid(current->numB, time, duration)){
                // klientu, laiku, busy.
                current->lastWorkTime = time+duration-1;
                current->client = clientNum;
                current->busy = true;
                sortList(&head); // aiznemts, vai nē, pēc laika, un tad nr.
                break;
            } 
            else {
                // nederīgs
                current = current->next;
                continue;
            }        
        }    
    }
    current = head;
    while(current != nullptr){
            if (current->busy == true) {
                output << current->lastWorkTime << " " << current->numB << " " << current->client << endl;
            }
            current = current->next;
        }

    // Close the file
    input.close();
    output.close();

    // Free memory
    deleteList(&head);
    return 0;
}





















    // while (currentTime<=maxTime)
    // {
    //     // Checks, if there are anymore clients, that need to be serviced
    //     if (checkIfListIsEmpty(head1) == true){
    //         cout << "The client list is empty - there are no more clients to service." << endl;
    //         break;
    //     } 
    //     else {
    //         /* Conditions
    //         List of conditions already met outside while loop:
    //         All input values are checked, before they are entered into the their respective linked lists. 
    //         List of conditions in this while loop:  
    //             DONE:
    //                 1. Time cant exceed 2 000 000 000. 
    //                     - DONE, the while loop takes care of this.
                    
    //                 2. A barber is resting and not taking on clients, if the hundredths place position in of the time variable corresponds to the the barbers own number, i.e. the barber with the number 5 will rest when the time variable is [500-599], [1500-1599], [2500.. 2599], etc. 
    //                     - Needs a function, that loops through barber list, and changes a bool value or puts the barber in another list, if any of them need to be resting. 
    //                     - DONE, function checkBreakTime does this, changes a bool value.

    //                 6. Knowing the arrival time, the number (customers number) and service time (duration of the service) of the customer, output the end of service moments time, the barbers number (who sercived the customer) and the customers number (the number of the customer, who was serviced). Outputting should be done sequentially, as in, according to the times growing order. If several clients service ends at the exact same time moment, then the result of these services are outputted according to the growing order of the barbers (that serviced these customers) numbers.
    //                     - The output lists does this, by each line being an element in the linked list. This functionality is outside this loop.
    //                     - !NOTE DONE, the sortList only looks at the time and doesnt consider the barbers numB.
    //                     - SORT OF DONE, still have to figure out how to keep track of the global time, so that this doen't mess up.
    //                     - Or, have to make sure that one barber cant finish two clients at the same time.
    //         */
    //         /* ALGO IDEA
    //             - Find barber with smallest number and smallest lastWorkTime that isnt on break.
    //                 - when work time overlap -> sort and find smallest.
    //             Pro: If this algo, then no need to change the positioning.
    //             Con: Might cause problems with sorting and choosing next barber that goes to work.

    //             Really, only need to calculate which barber is the one to go.
    //         */ 
    //         /* algorithm code 
    //         Take barber, get client, when everything done, write result into output list, delete client, repeat. Break time is checked on each repeat.
    //             - Need to sort out barber sequence and the order, that they take their respective clients.
            
    //         */
    //         //!UNRESOLVED ISSUES:
    //         /* 
    //             - Doesnt count break time and checks, if the barber can finish the job before his break starts.
    //                 - Really dunno how to do this one.
    //             - Has to take into account the current time when making the end of service time - see hair.i5 and hair.o5 for an example of this issue.
    //                 - An if condition that compares current time (which equals to the previous clients service time) and the arrival time of the current client. The bigger one takes center stage.
    //                     - DOENST WORK ATM
            
    //         */
    //         cout << "-----------------------------------------------------" << endl;    
    //         checkBreakTime(head, currentTime);

    //         Barber* nextAvailableBarber = findNextAvailableBarber(head);
    //         cout << "The next available barber numB: " << nextAvailableBarber->numB << endl;
    //         cout << "Current client " << endl << "Time: " << head1->time <<  endl << "numC: " << head1->numC << endl << "Duration: " << head1->duration << endl;

    //         //! Doesnt work atm, maent to fix the break time checking.
    //         // sortList(&head);
    //         // Barber* current = head;
    //         // while(current != nullptr) {
    //         //     /*
    //         //     1. Paņem barberi
    //         //     2. Paņem klientu
    //         //     3. Sačeko, vai laiki overlapos ar onBreak condition.
    //         //     */
    //         // }


    //         currentTime += head1->time;
    //         cout << endl << "Current time: " << currentTime << endl;

    //         //! This doesnt work for hair.i1-i4, but sort of works for i5, if currentTime+=outputTime at the end of the loop.
    //         /*
    //         if (currentTime>head1->time){
    //             outputTime = currentTime + head1->duration - 1;
    //         }
    //         else {
    //             outputTime = head1->time + head1->duration - 1;
    //         }
    //         */
    //         outputTime = head1->time + head1->duration - 1;
    //         outputBarber = nextAvailableBarber->numB;
    //         outputClient = head1->numC;
    //         head->lastWorkTime = outputTime;
    //         addElement(&head2, outputTime, outputBarber, outputClient); 
    //         deleteFirstElement(&head1);
    //         /* NOT DONE:
    //                 3. Klients ir jāapkalpo nekavējoties, ja eksistē brīvs frizieris un tam nav nekādu ierobežojumu veikt šo darbu.
    //                     - If a barber has finished servicing his client, he is immediately lower precedence than every other barber in the barbershop. This means, that, when he is freed up, he is pushed to the end of the list (not considering every other aspect of how barbers are chosen).
    //                         - BUT he will need another variable to track the last time he has worked, at least as far as this algo is concerned.
                    
    //                 Customers are waiting in an honest and "tight" (meaning punctual) line. Only one client can come in at a certain time momemt. The receptionist (in the case of C++ and the context of this exercise, an algorithm) shall immediately determine the customers number (which corresponds to the customer order of arrival) thats between 1 and 200000 and the needed service time for the customers, that's between 1-900.
    //                     - The ranges are already checked outside of this loop.

    //                 If there is an unserviced customer and several free barbers at the same time, then: preference is for a barber who has been without a customer for the longest amount of time (measured from the end of last serviced customer). Also, if two or more barbers have been waiting the same amount of time, then the barber who has the smaller number services the customer.
    //                     - The barbers might need another variable, that tracks the moment they finished servicing their last customer. This means, that we cant rely on the barber at the start of the list being the barber, that hasnt worked the longest.

    //                 4. Frizierim, beidzot darbu pie kārtējā klienta, ar nākošo laika momentu jāmēģina apkalpot kādu klientu.
    //                     - An if condition, that checks, if clients needed service time is less than the remaining time between the first barbers in the barbers list remaining time, till the next hundreth starts.
    //                     If remaining time+service needed time doesn't overslap break time
    //                         - incramentally dividing the service time, if its big enough, and checking it in a loop, if the task cannot be completed. This will be inside the currentTime>=100 condition. 

    //                 5. More accurate specification: customer C1 arrives at time T1 and needs service time S1 (service time means that it will take S1 amount of time, for the customer to be serviced). There's a free barber B1. Accordingly, the service takes place at the time interval of [T1...T1+(S1-1)]. The service is finished at the time: T1 + S1-1. If client C2 has already arrived before or at exactly at the time moment T1 + S1, then the barber B1 can start servicing client C2 at the time T1 + S1.

    //                 7. Deal with counting the break time, 
    //         */
    //     }
    // }

