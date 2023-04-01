#include <fstream>
using namespace std;
// Author: Johans Justs Eris, je21033

// Definition of a Barber struct with an integer value 
// and a pointer to the next Node. Used to construct the barber linked list.
struct Barber {
    int numB;
    int lastWorkTime = 0;
    int client = 0;
    bool busy = false;
    Barber* next;
};

// Delete the nodes in the barber linked list.
void deleteList(Barber** headRef) {
    Barber* current = *headRef;
    while (current != nullptr) {
        Barber* temp = current;
        current = current->next;
        delete temp;
    }
    *headRef = nullptr;
}

// Create the barber linked list.
void createList(Barber** headRef, int n) {
    *headRef = nullptr;

    // Create the linked list.
    for (int i = 1; i <= n; i++) {
        Barber* newBarber = new Barber;
        newBarber->numB = i;
        newBarber->next = nullptr;

        if (*headRef == nullptr) {
            *headRef = newBarber;
        }
        else {
            Barber* current = *headRef;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newBarber;
        }
    }
}

// This function sorts a linked list of Barber nodes in ascending order 
// based on their lastWorkTime and numB values. It uses a selection 
// sort algorithm to find the minimum element from the current node to the 
// end of the list, and swaps it with the current node if necessary.
void sortList(Barber** headRef) {
    Barber* current = *headRef;
    Barber* min;

    while (current != nullptr) {
        // Find the minimum element from current to the end of the list.
        min = current;
        Barber* innerCurrent = current->next;
        while (innerCurrent != nullptr) {
            if (!innerCurrent->busy && min->busy ||
                (innerCurrent->busy == min->busy && innerCurrent->lastWorkTime < min->lastWorkTime) ||
                (innerCurrent->busy == min->busy && innerCurrent->lastWorkTime == min->lastWorkTime && innerCurrent->numB < min->numB)) {
                min = innerCurrent;
            }
            innerCurrent = innerCurrent->next;
        }
        // Swap the minimum element with the current element.
        if (min != current) {
            int temp = current->numB;
            current->numB = min->numB;
            min->numB = temp;

            temp = current->lastWorkTime;
            current->lastWorkTime = min->lastWorkTime;
            min->lastWorkTime = temp;

            bool tempBool = current->busy;
            current->busy = min->busy;
            min->busy = tempBool;

            temp = current->client;
            current->client = min->client;
            min->client = temp;
        }
        current = current->next;
    }
}

// Finds out if a barber is allowed (is valid) to service a client, 
// considering the time, when the client arrives, and if the barbers break 
// time would interfere with the appointment.
bool isValidBarber(int barberNum, int time, int duration){
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
    // Global time.
    long int currentTime = 0;    

    // Open the files.
    ifstream input("hair.in");
    ofstream output;

    // Create a buffer, to help with the output. Makes the program faster 
    // and in turn more effiecient.
    const unsigned int length = 1536;
    char buffer[length];
    output.rdbuf()->pubsetbuf(buffer, length);
    output.open("hair.out");

    // Initialize variables.
    int n = 0;
    int time = 0; 
    int clientNum = 0; 
    int duration = 0;
    int cursor = 0;
    char line[25];

    // Read in the number of barbers.
    input.getline(line, 25);
    while(line[cursor] != '\0'){
        n = n*10 + line[cursor] - '0';
        cursor++;
    }
    cursor = 0;

    // Create a linked list of barbers.
    Barber* head = nullptr;
    createList(&head, n);

    // Read in the time, client number and duration of the appointment for the first client.
    input.getline(line, 25);
    while(line[cursor] != ' '){
        time = time*10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;
    while(line[cursor] != ' '){
        clientNum = clientNum*10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;
    while(line[cursor] != '\0'){
        duration = duration*10 + line[cursor] - '0';
        cursor++;
    }
    cursor = 0;

    Barber* current = head;

    // First loop for that processes the first client.
    while(true) {
        if(current == nullptr){
            // If the list has ended, update the time, to mitigate the 
            // barbers break time.
            time = (((time/100)*100)+100); // Update the time by 100.
            currentTime = time;
            current = head;
        }
        if (isValidBarber(current->numB, time, duration)){
            // If the barber can service the client - add the values to 
            // the barbers node.
            current->lastWorkTime = time+duration-1;
            current->client = clientNum;
            current->busy = true;
            sortList(&head); // The list gets sorted immediately for convenience.
            break;
        } 
        else {
            // If the current barber wasn't valid, go to the next one.
            current = current->next;
            continue;
        }        
    }

    time = 0; 
    clientNum = 0; 
    duration = 0;
    cursor = 0;

    // Read the next client.
    input.getline(line, 25);
    if (line[cursor]!='0'){ // Checks, weather the file has ended.
        while(line[cursor] != ' '){
            time = time*10 + line[cursor] - '0';
            cursor++;
        }
        cursor++;
        while(line[cursor] != ' '){
            clientNum = clientNum*10 + line[cursor] - '0';
            cursor++;
        }
        cursor++;
        while(line[cursor] != '\0'){
            duration = duration*10 + line[cursor] - '0';
            cursor++;
        }
        cursor = 0;

        // Continue to process the remaining clients inside hair.in.
        while (true) {
            current = head;
            if (time < currentTime){ // The next soonest moment, that a client can be serviced.
                time = currentTime;
                currentTime = time;
            }
            // Free up the busy barbers and output their content.
            while(current != nullptr && current->lastWorkTime < time){
                if (current->busy == true) {
                    current->busy = false;
                    output << current->lastWorkTime << " " << current->numB << " " << current->client << "\n";
                }
                current = current->next;
            }
            current = head;
            // All barbers are no longer busy.
            bool busyExists = false;
            while(true) {
                // Updates the currentTime, considering if all barbers are free, 
                // all barbers are busy or its a mix of both.
                if(current == nullptr){
                    if (busyExists == false){
                        // All barbers are free.
                        time = (((time/100)*100)+100);
                        currentTime = time;
                        current = head;
                    }
                    else if (busyExists == true){
                        current = head;
                        if (current->busy == true){
                            // All barbers are busy
                            currentTime = current->lastWorkTime+1;
                            time = currentTime;
                        }
                        else {
                            while (current->busy != true) {
                                current = current->next;
                            }
                            // The barber list has Both busy and free barbers.
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
                        // While the current barber has finished servicing his client.
                        if (current->busy == true) {
                            // If the next barber is empty - the list has ended.
                            if (current->next == nullptr) {
                                // Which means that there are no more busy barbers in the list.
                                busyExists = false;
                            }
                            // If the list hasn't ended yet, then only set the current->busy to false, 
                            // and output the contents of the element.
                            current->busy = false;
                            output << current->lastWorkTime << " " << current->numB << " " << current->client << "\n";
                        }
                        current = current->next;
                    }
                    current = head;
                }
                if (current->busy == true){ 
                    // When the list no longer has any free barbers, set busyExist to true, 
                    // and skip to the end of the list.
                    busyExists = true;
                    current = nullptr;
                    continue;
                }
                if (current->busy == false && isValidBarber(current->numB, time, duration)){
                    // When the barber can service the client, pass him the clients information.
                    current->lastWorkTime = time+duration-1;
                    current->client = clientNum;
                    current->busy = true;
                    sortList(&head); // Again sort the list.
                    break;
                } 
                else {
                    // If the barber is not valid.
                    current = current->next;
                    continue;
                }        
            }    
        
        time = 0; 
        clientNum = 0; 
        duration = 0;
        cursor = 0;
        // Read in the next client.
        input.getline(line, 25);
        if (line[cursor]!='0'){
            while(line[cursor] != ' '){
                time = time*10 + line[cursor] - '0';
                cursor++;
            }
            cursor++;
            while(line[cursor] != ' '){
                clientNum = clientNum*10 + line[cursor] - '0';
                cursor++;
            }
            cursor++;
            while(line[cursor] != '\0'){
                duration = duration*10 + line[cursor] - '0';
                cursor++;
            }
            cursor = 0;
        }
        else {
            break;
        }

        }
    }
    current = head;
    // When the input file has ended, output all of the busy barbers, if there were any.
    while(current != nullptr){
            if (current->busy == true) {
                output << current->lastWorkTime << " " << current->numB << " " << current->client << "\n";
            }
            current = current->next;
        }

    // Close the files.
    input.close();
    output.close();

    // Free up memory by deleting the list.
    deleteList(&head);
    return 0;
}