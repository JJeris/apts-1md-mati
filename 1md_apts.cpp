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

// This function sorts a linked list of Barber nodes in ascending order based on their lastWorkTime and numB attributes. It uses a selection sort algorithm to find the minimum element from the current node to the end of the list, and swaps it with the current node if necessary. The function takes a pointer to the head of the linked list as input and modifies the list in place.
void sortList(Barber** headRef) {
    Barber* current = *headRef;
    Barber* min;

    while (current != nullptr) {
        // Find the minimum element from current to the end of the list
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
// Nosaka, vai barberis ir derīgs, skatoties uz dažādiem vairantiem, kad klients varētu atnākt un vai viņa pauze viņam kko sapisīs. Skaties image.png.
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
    ofstream output;


    // Initialization
    const unsigned int length = 1536;
    char buffer[length];
    output.rdbuf()->pubsetbuf(buffer, length);
    output.open("hair.out");

    // Create a linked list of barbers
    int n = 0;
    int time = 0; 
    int clientNum = 0; 
    int duration = 0;
    int cursor = 0;
    char line[25];
    input.getline(line, 25);
    while(line[cursor] != '\0'){
        n = n*10 + line[cursor] - '0';
        cursor++;
    }
    cursor = 0;
    Barber* head = nullptr;
    createList(&head, n);

    
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

    //! ŠIS VISS IR PIRMAJAM ELEMENTAM Atrod derīgo barberi.
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

    // <...>
    // if (!='0'){
    //     while
    // }
    // else {

    // }
    // ! ŠIS VISS IR NĀKAMAJIEM ELEMENTIEM
    while (input >> time >> clientNum >> duration) { //true
    // while(time != 0)
        if (time == 0) break; // Tātad fails beidzās
        current = head;
        if (time < currentTime){ // Ātrākais brīdis, kad klientu barberis var apkalpot ķip
            time = currentTime;
            currentTime = time;
        }
        // Atbrīvot busy: salīdzini time ar vinu lastWorkTime
        while(current != nullptr && current->lastWorkTime < time){
            if (current->busy == true) {
                current->busy = false;
                output << current->lastWorkTime << " " << current->numB << " " << current->client << "\n";
            }
            current = current->next;
        }
        current = head;
        bool busyExists = false;
        while(true) {
           
            if(current == nullptr){
                // tikai brivie frizieri
                // tikai aiznemtie frizieri
                // abi kopā sarakstā.
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
                        // Both busy and not busy
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
                    // Ja ir currentam ir beidzies tas iepriekšējais klienta apkalpošana
                    if (current->busy == true) {
                        // Ja next ir nullptr, tad lists ie beidzies.
                        if (current->next == nullptr) {
                            // Un tas nozīmē, ka neeksistē vairs neviens busy barber, so nomainam busyExists uz false, jo no busy exist.
                            busyExists = false;
                        }
                        // Ja tas nav vēl beidzies, tad vnk nomainam viņa busy uz false uz sūtam pabeigtā klienta datus prom.
                        current->busy = false;
                        output << current->lastWorkTime << " " << current->numB << " " << current->client << "\n";
                    }
                    current = current->next;
                }
                current = head;
            }
            if (current->busy == true){ // Kad sarakstā vairs nav neviena brīva friziera, un sastapam pirmo busy frizieru, tad nav jēgas vairs checkot
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
    // <...>
    }
    current = head;
    // Kas viss beidzies, vnk iztukšo arī tos, kas vēl bija busy.
    while(current != nullptr){
            if (current->busy == true) {
                output << current->lastWorkTime << " " << current->numB << " " << current->client << "\n";
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