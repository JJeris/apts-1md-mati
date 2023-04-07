 #include <fstream>
#include <iostream>
using namespace std;

struct Frizieris {
    int numurs;
    int klients = 0;
    int darbaBeigsanasLaiks = 0;
    bool aiznemts = false;
    Frizieris* next;
};

void dzestLinkedList(Frizieris*& head) {
    if (head == NULL) {
        return;
    }
    dzestLinkedList(head->next);
    delete head;
    head = NULL;
}

void izveidotList(Frizieris** head, int numElements) {
    *head = nullptr;
    Frizieris* pointer= nullptr;

    for (int i = 1; i <= numElements; i++) {
        Frizieris* jaunsFrizieris = new Frizieris();
        jaunsFrizieris->numurs = i;
        jaunsFrizieris->next = nullptr;

        if (*head == nullptr) {
            *head = jaunsFrizieris;
            pointer= *head;
        } else {
            pointer->next = jaunsFrizieris;
            pointer= jaunsFrizieris;
        }
    }
}

bool vaiDerigsFrizieris(int ierasanasLaiks, int frizieris, int ilgums) {
    // int hundrethPlace = (ierasanasLaiks / 100) % 10;
    // int hundrethPart = ierasanasLaiks % 1000;
    if ((ierasanasLaiks / 100) % 10 == frizieris){
        return false;
    }
    else {
        int endTime = ierasanasLaiks % 1000 + ilgums - 1;
        if (ierasanasLaiks % 1000 < frizieris*100 && endTime >= frizieris*100) {
            return false;
        }
        else if(ierasanasLaiks % 1000 > (frizieris*100) + 99 && endTime >= frizieris*100+1000) {
            return false;
        }
        return true;
    }
}

void insertInOrder(Frizieris** headRef, int newnumurs, int newdarbaBeigsanasLaiks, bool newaiznemts, int newklients) {
    Frizieris* newNode = new Frizieris;
    newNode->numurs = newnumurs;
    newNode->darbaBeigsanasLaiks = newdarbaBeigsanasLaiks;
    newNode->aiznemts = newaiznemts;
    newNode->klients = newklients;

    if (*headRef == nullptr || (!newNode->aiznemts && (*headRef)->aiznemts) ||
        (newNode->aiznemts == (*headRef)->aiznemts && newNode->darbaBeigsanasLaiks < (*headRef)->darbaBeigsanasLaiks) ||
        (newNode->aiznemts == (*headRef)->aiznemts && newNode->darbaBeigsanasLaiks == (*headRef)->darbaBeigsanasLaiks && newNode->numurs < (*headRef)->numurs)) {
        newNode->next = *headRef;
        *headRef = newNode;
    }
    else {
        Frizieris* p = *headRef;
        while (p->next != nullptr &&
               (p->next->aiznemts || (newNode->aiznemts == p->next->aiznemts && newNode->darbaBeigsanasLaiks > p->next->darbaBeigsanasLaiks) ||
                (newNode->aiznemts == p->next->aiznemts && newNode->darbaBeigsanasLaiks == p->next->darbaBeigsanasLaiks && newNode->numurs > p->next->numurs))) {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
}

void printList(Frizieris* head) {
    Frizieris* p = head;
    while (p != nullptr) {
        cout << "Numurs: " << p->numurs << endl;
        cout << "Klients: " << p->klients << endl;
        cout << "Darba beigsanas laiks: " << p->darbaBeigsanasLaiks << endl;
        cout << "Aiznemts: " << p->aiznemts << endl;
        cout << endl;
        p = p->next;
    }
}

#include <cstdlib> // for rand() function
#include <ctime> // for time() function

void assignRandomValues(Frizieris* head) {
    srand(time(0)); // seed the random numurser generator with the p time

    Frizieris* p = head;
    while (p != nullptr) {
        p->klients = rand() % 10 + 1; // random numurser between 1 and 10 (inclusive)
        p->darbaBeigsanasLaiks = rand() % 120 + 1; // random numurser between 1 and 120 (inclusive)
        p->aiznemts = rand() % 2; // random boolean value (0 or 1)
        p = p->next;
    }
}

int main() {

    long int globalaisLaiks = 0;    

    ifstream in("hairin.txt");

    const unsigned int len = 1536;
    char buffers[len];
    ofstream out;
    out.rdbuf()->pubsetbuf(buffers, len);
    out.open("hairout.txt");

    int n = 0;
    int ierasanasLaiks = 0; 
    int klientaNumurs = 0; 
    int ilgums = 0;
    int cursor = 0;
    char line[25];


    in.getline(line, 25);
    while(line[cursor] != '\0'){
        n = n*10 + line[cursor] - '0';
        cursor++;
    }
    cursor = 0;


    Frizieris* head = nullptr;
    izveidotList(&head, n);

    in.getline(line, 25);
    while(line[cursor] != ' '){
        ierasanasLaiks = ierasanasLaiks*10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;
    while(line[cursor] != ' '){
        klientaNumurs = klientaNumurs*10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;
    while(line[cursor] != '\0'){
        ilgums = ilgums*10 + line[cursor] - '0';
        cursor++;
    }
    cursor = 0;

    Frizieris* p = head;


    while(true) {
        if(p == nullptr){
            // If the list has ended, update the time, to mitigate the 
            // barbers break time.
            ierasanasLaiks = (((ierasanasLaiks/100)*100)+100); // Update the time by 100.
            globalaisLaiks = ierasanasLaiks;
            p = head;
        }

        else if (vaiDerigsFrizieris(ierasanasLaiks, p->numurs, ilgums)){
            // If the barber can service the client - add the values to 
            // the barbers node.
            // p->darbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
            // p->klients = klientaNumurs;
            // p->aiznemts = true;

            // int tempNumurs = p->numurs;
            // int tempDarbaBeigsanasLaiks = p->darbaBeigsanasLaiks;
            // int tempKlients = p->klients;
            // bool tempAiznemts = p->aiznemts;
            // delete p;
            // insertInOrder(&head, tempNumurs, tempDarbaBeigsanasLaiks, tempAiznemts, tempKlients);
            // break;
            if (p == head) { // p is the head node
                head = p->next;
                int tempNumurs = p->numurs;
                int tempDarbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
                int tempKlients = klientaNumurs;
                bool tempAiznemts = true;
                delete p;
                insertInOrder(&head, tempNumurs, tempDarbaBeigsanasLaiks, tempAiznemts, tempKlients);
                break;
            } else { // p is not the head node
                p->darbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
                p->klients = klientaNumurs;
                p->aiznemts = true;
                int tempNumurs = p->numurs;
                int tempDarbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
                int tempKlients = klientaNumurs;
                bool tempAiznemts = true;
                delete p;
                insertInOrder(&head, tempNumurs, tempDarbaBeigsanasLaiks, tempAiznemts, tempKlients);
                break;
            }
        } 
        else {
            // If the p barber wasn't valid, go to the next one.
            p = p->next;
            continue;
        }        
    }

   // <Turpinājums, kas būs līdzīgs manam kodam.>


    ierasanasLaiks = 0; 
    klientaNumurs = 0; 
    ilgums = 0;
    cursor = 0;

    // Read the next client.
    in.getline(line, 25);
    if (line[cursor]!='0'){ // Checks, weather the file has ended.
        while(line[cursor] != ' '){
            ierasanasLaiks = ierasanasLaiks*10 + line[cursor] - '0';
            cursor++;
        }
        cursor++;
        while(line[cursor] != ' '){
            klientaNumurs = klientaNumurs*10 + line[cursor] - '0';
            cursor++;
        }
        cursor++;
        while(line[cursor] != '\0'){
            ilgums = ilgums*10 + line[cursor] - '0';
            cursor++;
        }
        cursor = 0;

        // Continue to process the remaining clients inside hair.in.
        while (true) {
            Frizieris* p = head;
            if (ierasanasLaiks < globalaisLaiks){ // The next soonest moment, that a client can be serviced.
                ierasanasLaiks = globalaisLaiks;
                globalaisLaiks = ierasanasLaiks;
            }
            // Free up the busy barbers and output their content.
            while(p != nullptr && p->darbaBeigsanasLaiks < ierasanasLaiks){
                if (p->aiznemts == true) {
                    p->aiznemts = false;
                    out << p->darbaBeigsanasLaiks << " " << p->numurs << " " << p->klients << "\n";
                }
                p = p->next;
            }
            p = head;
            // All barbers are no longer busy.
            bool busyExists = false;
            while(true) {
                // Updates the globalaisLaiks, considering if all barbers are free, 
                // all barbers are busy or its a mix of both.
                if(p == nullptr){
                    if (busyExists == false){
                        // All barbers are free.
                        ierasanasLaiks = (((ierasanasLaiks/100)*100)+100);
                        globalaisLaiks = ierasanasLaiks;
                        p = head;
                    }
                    else if (busyExists == true){
                        p = head;
                        if (p->aiznemts == true){
                            // All barbers are busy
                            globalaisLaiks = p->darbaBeigsanasLaiks+1;
                            ierasanasLaiks = globalaisLaiks;
                        }
                        else {
                            while (p->aiznemts != true) {
                                p = p->next;
                            }
                            // The barber list has Both busy and free barbers.
                            if (ierasanasLaiks/100*100+100<p->darbaBeigsanasLaiks+1) {
                                globalaisLaiks = ierasanasLaiks/100*100+100;
                                ierasanasLaiks = globalaisLaiks;    
                            }
                            else {
                                globalaisLaiks = p->darbaBeigsanasLaiks+1;
                                ierasanasLaiks = globalaisLaiks;
                            }
                        }
                    }

                    p = head;
                    while(p != nullptr && p->darbaBeigsanasLaiks < ierasanasLaiks){
                        // While the p barber has finished servicing his client.
                        if (p->aiznemts == true) {
                            // If the next barber is empty - the list has ended.
                            if (p->next == nullptr) {
                                // Which means that there are no more busy barbers in the list.
                                busyExists = false;
                            }
                            // If the list hasn't ended yet, then only set the p->busy to false, 
                            // and output the contents of the element.
                            p->aiznemts = false;
                            out << p->darbaBeigsanasLaiks << " " << p->numurs << " " << p->klients << "\n";
                        }
                        p = p->next;
                    }
                    p = head;
                }
                if (p->aiznemts == true){ 
                    // When the list no longer has any free barbers, set busyExist to true, 
                    // and skip to the end of the list.
                    busyExists = true;
                    p = nullptr;
                    continue;
                }
                if (p->aiznemts == false && vaiDerigsFrizieris(ierasanasLaiks, p->numurs, ilgums)){
                    // // When the barber can service the client, pass him the clients information.

                    // p->darbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
                    // p->klients = klientaNumurs;
                    // p->aiznemts = true;

                    // int tempNumurs = p->numurs;
                    // int tempDarbaBeigsanasLaiks = p->darbaBeigsanasLaiks;
                    // int tempKlients = p->klients;
                    // bool tempAiznemts = p->aiznemts;
                    // delete p;
                    // insertInOrder(&head, tempNumurs, tempDarbaBeigsanasLaiks, tempAiznemts, tempKlients);   
                    // break;
                    if (p == head) { // p is the head node
                        head = p->next;
                        int tempNumurs = p->numurs;
                        int tempDarbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
                        int tempKlients = klientaNumurs;
                        bool tempAiznemts = true;
                        delete p;
                        insertInOrder(&head, tempNumurs, tempDarbaBeigsanasLaiks, tempAiznemts, tempKlients);
                        break;
                    } else { // p is not the head node
                        p->darbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
                        p->klients = klientaNumurs;
                        p->aiznemts = true;
                        int tempNumurs = p->numurs;
                        int tempDarbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
                        int tempKlients = klientaNumurs;
                        bool tempAiznemts = true;
                        delete p;
                        insertInOrder(&head, tempNumurs, tempDarbaBeigsanasLaiks, tempAiznemts, tempKlients);
                        break;
                    }
                
                } 
                else {
                    // If the barber is not valid.
                    p = p->next;
                    continue;
                }        
            }    
        
        ierasanasLaiks = 0; 
        klientaNumurs = 0; 
        ilgums = 0;
        cursor = 0;
        // Read in the next client.
        in.getline(line, 25);
        if (line[cursor]!='0'){
            while(line[cursor] != ' '){
                ierasanasLaiks = ierasanasLaiks*10 + line[cursor] - '0';
                cursor++;
            }
            cursor++;
            while(line[cursor] != ' '){
                klientaNumurs = klientaNumurs*10 + line[cursor] - '0';
                cursor++;
            }
            cursor++;
            while(line[cursor] != '\0'){
                ilgums = ilgums*10 + line[cursor] - '0';
                cursor++;
            }
            cursor = 0;
        }
        else {
            break;
        }

        }
    }
    p = head;
    // When the input file has ended, output all of the busy barbers, if there were any.
    while(p != nullptr){
            if (p->aiznemts == true) {
                out << p->darbaBeigsanasLaiks << " " << p->numurs << " " << p->klients << "\n";
            }
            p = p->next;
        }



    // Close the files.
    in.close();
    out.close();

    // Free up memory by deleting the list.
    dzestLinkedList(head);
    return 0;
}