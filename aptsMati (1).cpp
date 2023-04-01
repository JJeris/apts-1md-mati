#include <iostream>
#include <fstream>
using namespace std;

struct Frizieris
{
    int num;
    int pedejaisDarbaLaiks = 0;
    int klients;
    Frizieris* next;
};

void izveidotSarakstu(Frizieris** head, int n)
{
    *head = nullptr;

    // izveido sarakstu
    for (int i = 1; i <= n; i++)
    {
        Frizieris* frizieris = new Frizieris;
        frizieris->num = i;
        frizieris->next = nullptr;

        //ja saraksts ir tukšs
        if (*head == nullptr)
        {
            *head = frizieris;
        }

        //ja saraksts nav tukšs
        else
        {
            //iet cauri sarakstam
            Frizieris* current = *head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            //un beigās pieliek jauno frizieri
            current->next = frizieris;
        }
    }
}

void izdzestSarakstu(Frizieris** head)
{
    Frizieris* current = *head;
    while (current != nullptr)
    {
        Frizieris* temp = current;
        current = current->next;
        delete temp;
    }
    *head = nullptr;
}

void pievienotElementu(Frizieris** head, int num, int pedejaisDarbaLaiks, int klients)
{
    Frizieris* frizieris = new Frizieris;
    frizieris->num = num;
    frizieris->pedejaisDarbaLaiks = pedejaisDarbaLaiks;
    frizieris->klients = klients;
    frizieris->next = nullptr;

    //ja saraksts ir tukšs
    if (*head == nullptr)
    {
        *head = frizieris;
    }

    //ja saraksts nav tukšs
    else
    {
        //iet cauri sarakstam
        Frizieris* current = *head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        //un beigās pieliek jauno frizieri
        current->next = frizieris;
    }
}

void izdzestElementu(Frizieris** head)
{
    //ja ir tukšs saraksts, tad nav, ko dzēst
    if (*head == nullptr)
    {
        return;
    }

    //izdzēš pirmo elementu un norāda saraksta 2.elementu kā jauno 1.elementu
    Frizieris* temp = *head;
    *head = (*head)->next;
    delete temp;
}

void kartosana(Frizieris** head)
{
    // saraksts ir tukšs vai sarakstā ir tikai viens elements
    if (*head == nullptr || (*head)->next == nullptr)
    {
        return;
    }

    Frizieris* previous = nullptr;
    Frizieris* current = *head;
    Frizieris* next = nullptr;
    bool swapped;

    //dara kamēr elementi ir jāmaina vietām
    do
    {
        swapped = false;
        current = *head;

        //kamēr nav sasniegtas saraksta beigas
        while (current->next != nullptr)
        {
            next = current->next;

            //ja ir atrasti divi elementi, kuri ir jāmaina vietām
            if (current->pedejaisDarbaLaiks > next->pedejaisDarbaLaiks ||
                    (current->pedejaisDarbaLaiks == next->pedejaisDarbaLaiks && current->num > next->num))
            {
                swapped = true;

                //ja nav pirmais elements
                if (previous != nullptr)
                {
                    previous->next = next;
                }
                //ja ir pirmais elements
                else
                {
                    *head = next;
                }

                //apmaina elementus vietām
                current->next = next->next;
                next->next = current;

                previous = next;
                next = current->next;
            }

            //apskata nākamo elementu
            else
            {
                previous = current;
                current = next;
                next = next->next;
            }
        }
    }
    while (swapped);
}

bool derigs(int frizieraNum, int laiks, int pateretaisLaiks)
{
    int simti = laiks % 1000;

    if ((simti/100) == frizieraNum)
    {
        return false;
    }

    else
    {
        int beiguLaiks = simti + pateretaisLaiks - 1;
        int partraukums = frizieraNum*100;

        if(simti < partraukums && beiguLaiks >= partraukums)
        {
            return false;
        }

        else if(simti >= (partraukums+100) && beiguLaiks >= (partraukums+1000))
        {
            return false;
        }

        return true;
    }
}

int main()
{
    //laiks vajadzīgs, lai pārbaudītu brīvos frizierus
    int reallaiks = 0;

    //atver failus
    ifstream input("hair.i3");
    ofstream output("hair.out");

    int n;
    input >> n;
    Frizieris* headBrivie = nullptr;
    izveidotSarakstu(&headBrivie, n);

    Frizieris* headAiznemtie = nullptr;

    int laiks;
    int klientaNum;
    int pateretaisLaiks;

    input >> laiks >> klientaNum >> pateretaisLaiks;

    Frizieris* currentBrivie = headBrivie;
    Frizieris* currentAiznemtie = headAiznemtie;

    while(true)
    {
        //ja nav neviena brīva friziera
        if(currentBrivie == nullptr)
        {
            laiks = (((laiks/100)*100)+100);
            reallaiks = laiks;
            currentBrivie = headBrivie;
        }

        if(derigs(currentBrivie->num, laiks, pateretaisLaiks))
        {
            int darbaLaiks = laiks + pateretaisLaiks - 1;
            pievienotElementu(&headAiznemtie, currentBrivie->num, darbaLaiks, klientaNum);
            izdzestElementu(&headBrivie);
            break;
        }

        else //dotais frizieris ies pārtraukumā, tātad neder
        {
            currentBrivie = currentBrivie->next;
            continue;
        }
    }

    while (input >> laiks >> klientaNum >> pateretaisLaiks)
    {
        if (laiks == 0) break; //faila beigas

        currentBrivie = headBrivie;
        currentAiznemtie = headAiznemtie;

        if(laiks < reallaiks+1)
        {
            laiks = reallaiks+1;
            reallaiks = laiks;
        }

        while(currentAiznemtie != nullptr && currentAiznemtie->pedejaisDarbaLaiks < laiks)
        {
            output << currentAiznemtie->pedejaisDarbaLaiks << " " << currentAiznemtie->num << " " << currentAiznemtie->klients << '\n';
            pievienotElementu(&headBrivie, currentAiznemtie->num, currentAiznemtie->pedejaisDarbaLaiks, currentAiznemtie->klients);
            izdzestElementu(&headAiznemtie);
            kartosana(&headBrivie);
            currentAiznemtie = currentAiznemtie->next;
        }

        currentAiznemtie = headAiznemtie;

        while(true)
        {
            if (currentBrivie == nullptr)
            {
                if(headAiznemtie == nullptr)
                {
                    laiks = (((laiks/100)*100)+100);
                    reallaiks = laiks;
                    currentBrivie = headBrivie;
                }
                else
                {
                    currentBrivie = headBrivie;
                    currentAiznemtie = headAiznemtie;
                    if (currentBrivie == nullptr)
                    {
                        reallaiks = currentAiznemtie->pedejaisDarbaLaiks+1;
                        laiks = reallaiks;
                    }
                    else
                    {
                        if((((laiks/100)*100)+100) < currentAiznemtie->pedejaisDarbaLaiks+1)
                        {
                            reallaiks = (((laiks/100)*100)+100);
                            laiks = reallaiks;
                        }
                        else
                        {
                            //...
                            reallaiks = headAiznemtie->pedejaisDarbaLaiks+1;
                            laiks = reallaiks;
                        }
                    }
                }

                currentAiznemtie = headAiznemtie;

                while(currentAiznemtie != nullptr && currentAiznemtie->pedejaisDarbaLaiks < laiks)
                {
                    output << currentAiznemtie->pedejaisDarbaLaiks << " " << currentAiznemtie->num << " " << currentAiznemtie->klients << '\n';
                    pievienotElementu(&headBrivie, currentAiznemtie->num, currentAiznemtie->pedejaisDarbaLaiks, currentAiznemtie->klients);
                    izdzestElementu(&headAiznemtie);
                    kartosana(&headBrivie);
                    currentAiznemtie = currentAiznemtie->next;
                }

                currentBrivie = headBrivie;
            }

            if(currentBrivie == nullptr)
            {
                continue;
            }

            if(derigs(currentBrivie->num, laiks, pateretaisLaiks))
            {
                int darbaLaiks = laiks + pateretaisLaiks - 1;
                pievienotElementu(&headAiznemtie, currentBrivie->num, darbaLaiks, klientaNum);
                izdzestElementu(&headBrivie);
                kartosana(&headAiznemtie);
                break;
            }

            else
            {
                currentBrivie = currentBrivie->next;
                continue;
            }
        }
    }

    currentAiznemtie = headAiznemtie;

    while(currentAiznemtie != nullptr)
    {
        output << currentAiznemtie->pedejaisDarbaLaiks << " " << currentAiznemtie->num << " " << currentAiznemtie->klients << '\n';
        currentAiznemtie = currentAiznemtie->next;
    }

    input.close();
    output.close();

    izdzestSarakstu(&headBrivie);
    izdzestSarakstu(&headAiznemtie);

    return 0;
}
