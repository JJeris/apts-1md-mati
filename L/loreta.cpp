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
        Frizieris* current = *headRef;
        while (current->next != nullptr &&
               (current->next->aiznemts || (newNode->aiznemts == current->next->aiznemts && newNode->darbaBeigsanasLaiks > current->next->darbaBeigsanasLaiks) ||
                (newNode->aiznemts == current->next->aiznemts && newNode->darbaBeigsanasLaiks == current->next->darbaBeigsanasLaiks && newNode->numurs > current->next->numurs))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void printList(Frizieris* head) {
    Frizieris* current = head;
    while (current != nullptr) {
        cout << "Numurs: " << current->numurs << endl;
        cout << "Klients: " << current->klients << endl;
        cout << "Darba beigsanas laiks: " << current->darbaBeigsanasLaiks << endl;
        cout << "Aiznemts: " << current->aiznemts << endl;
        cout << endl;
        current = current->next;
    }
}

#include <cstdlib> // for rand() function
#include <ctime> // for time() function

void assignRandomValues(Frizieris* head) {
    srand(time(0)); // seed the random numurser generator with the current time

    Frizieris* current = head;
    while (current != nullptr) {
        current->klients = rand() % 10 + 1; // random numurser between 1 and 10 (inclusive)
        current->darbaBeigsanasLaiks = rand() % 120 + 1; // random numurser between 1 and 120 (inclusive)
        current->aiznemts = rand() % 2; // random boolean value (0 or 1)
        current = current->next;
    }
}

int main() {

    long int globalaisLaiks = 0;    

    ifstream in("hair.in");

    const unsigned int len = 1536;
    char buffers[len];
    ofstream out;
    out.rdbuf()->pubsetbuf(buffers, len);
    out.open("hair.out");

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

        else if (vaiDerigsFrizieris(p->numurs, ierasanasLaiks, ilgums)){
            // If the barber can service the client - add the values to 
            // the barbers node.
            p->darbaBeigsanasLaiks = ierasanasLaiks+ilgums-1;
            p->klients = klientaNumurs;
            p->aiznemts = true;

            int tempNumurs = p->numurs;
            int tempDarbaBeigsanasLaiks = p->darbaBeigsanasLaiks;
            int tempKlients = p->klients;
            bool tempAiznemts = p->aiznemts;
            delete p;
            insertInOrder(&head, tempNumurs, tempDarbaBeigsanasLaiks, tempAiznemts, tempKlients);
            break;
        } 
        else {
            // If the current barber wasn't valid, go to the next one.
            p = p->next;
            continue;
        }        
    }



    // <Turpinājums, kas būs līdzīgs manam kodam.>




    // Close the files.
    in.close();
    out.close();

    // Free up memory by deleting the list.
    dzestLinkedList(head);
    return 0;
}