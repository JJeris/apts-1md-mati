//Autors: Agnese Griķe, ag21201

#include <fstream>

using namespace std;

struct Marsietis //marsieša parametri
{
    int parent = -1; //lai sekotu koka struktūrai, saglabā mezgla vecāku, kreiso un labo bērnu
    int left = -1;
    int right = -1;
    int prev = -1; //prev un next ir nepieciešami, lai sekotu līdzi inorder secībai
    int next = -1;
};

int main()
{
    ifstream input("aliens.i1");
    ofstream output;

    char buffer[1536]; //izveido buferi
    output.rdbuf()->pubsetbuf(buffer, 1536);
    output.open("aliens.out");

    int vecaks = 0;

    char rinda[15];
    int kursors = 0;

    Marsietis marsiesi[10001]; //izveido masīvu ar marsiešiem - šeit tiks glabāti visi marsieši indeksā, kas atbilst viņu numuram

    input.getline(rinda, 15); //ielasa pirmo rindu
    while(rinda[kursors] != '\0')
    {
        vecaks = vecaks*10 + rinda[kursors] - '0'; //un no tās iegūst pirmo mezglu
        kursors++;
    }
    kursors = 2; //tālākajos vaicājumos mums nav jāapskata pirmie divi simboli - jo pirmo mēs varam tāpat apskatīt un otrais ir atstarpe

    marsiesi[vecaks].parent = 0; //pirmā marsieša vecāku iestata kā 0 - viņam nav vecāka, bet pats mezgls eksistē

    vecaks = 0;
    int berns = 0; //atkal iestata mainīgos par 0, lai tos varētu iegūt tālāk
    int temp = -1; //būs nepieciešams inorder secības mainīšanai

    input.getline(rinda, 15); //visiem nākamajiem marsiešiem
    while (rinda[0] != 'F') //F apzīmē faila beigas
    {
        if (rinda[0] == 'L') //ja jāievieto kreiso bērnu
        {
            while(rinda[kursors] != ' ') //iegūst abus mainīgos
            {
                vecaks = vecaks*10 + rinda[kursors] - '0';
                kursors++;
            }
            kursors++;

            while(rinda[kursors] != '\0')
            {
                berns = berns*10 + rinda[kursors] - '0';
                kursors++;
            }
            kursors = 2; //atkal ignorējam pirmos divus simbolus

            if (vecaks == berns) //ja abi mezgli ir vienādi
            {
                output << "error1" << '\n';
            }

            else if (marsiesi[vecaks].parent == -1) //ja neeksistē norādītais vecāks
            {
                output << "error2" << '\n';
            }

            else if (marsiesi[berns].parent != -1) // ja ievietojamais bērns jau eksistē
            {
                output << "error3" << '\n';
            }

            else
            {
                if (marsiesi[vecaks].left != -1) //ja kreisais bērns vecākam jau eksistē
                {
                    output << "error4" << '\n';
                }
                else
                {
                    marsiesi[berns].parent = vecaks; //iestata bērna vecāku
                    marsiesi[vecaks].left = berns; //iestata vecāka kreiso bērnu

                    /** tālāk pārkabina inorder saites. **/
                    marsiesi[berns].prev = marsiesi[vecaks].prev; //ievietotā bērna iepriekšējais kļūst par vecāka iepriekšējo,
                                                                    //jo kreiso bērnu apskata pirms vecāka
                    marsiesi[berns].next = vecaks; //bērna nākamais ir vecāks (secība left-root-right)
                    temp = marsiesi[vecaks].prev; //saglabājam, jo vecāka iepriekšējais tiks mainīts
                    marsiesi[vecaks].prev = berns; //vecāka iepriekšējais ir bērns - kreiso bērnu apskata pirms vecāka
                    if (temp != -1)
                    {
                        marsiesi[temp].next = berns; //vecāka iepriekšējam nākamais ir ievietotais bērns, jo kreiso bērnu apskata pirms vecāka
                    }
                }
            }

        }
        else if (rinda[0] == 'R') //ja jāievieto labais bērns
        {
            while(rinda[kursors] != ' ') //iegūst mainīgos
            {
                vecaks = vecaks*10 + rinda[kursors] - '0';
                kursors++;
            }
            kursors++;

            while(rinda[kursors] != '\0')
            {
                berns = berns*10 + rinda[kursors] - '0';
                kursors++;
            }
            kursors = 2; //atkal ignorējam pirmos divus simbolus

            if (vecaks == berns) //ja abi mezgli ir vienādi
            {
                output << "error1" << '\n';
            }

            else if (marsiesi[vecaks].parent == -1) //ja neeksistē norādītais vecāks
            {
                output << "error2" << '\n';
            }

            else if (marsiesi[berns].parent != -1) // ja ievietojamais bērns jau eksistē
            {
                output << "error3" << '\n';
            }

            else
            {
                if (marsiesi[vecaks].right != -1) //ja labais bērns vecākam jau eksistē
                {
                    output << "error5" << '\n';
                }
                else
                {
                    marsiesi[berns].parent = vecaks; //iestata bērna vecāku
                    marsiesi[vecaks].right = berns; //iestata vecāka labo bērnu

                    /** tālāk pārkabina inorder saites. **/
                    marsiesi[berns].prev = vecaks; //ievietotā bērna iepriekšējais ir vecāks - labo bērnu apskata pēc vecāka (left-right-root)
                    marsiesi[berns].next = marsiesi[vecaks].next; //bērna nākamais ir vecāka nākamais - labo bērnu apskata pēc vecāka,
                                                                  //tāpēc nākamais būs tas, kas iepriekš bija vecāka nākamais
                    temp = marsiesi[vecaks].next; //saglabājam, jo vecāka nākamais tiks mainīts
                    marsiesi[vecaks].next = berns; //vecāka nākamais ir ievietotais bērns, jo secība left-root-right
                    if (temp != -1)
                    {
                        marsiesi[temp].prev = berns; //vecāka nākamā iepriekšējais tagad ir bērns, jo vecāku apskata pirms labā bērna
                    }                                //un pēc tam apskata to, kas būtu bijis vecāka nākamais
                }
            }
        }
        else if (rinda[0] == '?')
        {
            while(rinda[kursors] != '\0') //iegūst mainīgo
            {
                vecaks = vecaks*10 + rinda[kursors] - '0';
                kursors++;
            }

            if (marsiesi[vecaks].parent == -1) //ja apskatāmais mezgls neeksistē
            {
                output << "error0" << '\n';
            }

            else
            {
                if (marsiesi[vecaks].prev == -1 && marsiesi[vecaks].next == -1) output << "0 0\n"; //ja gan iepriekšējais, gan nākamais neeksistē
                else if (marsiesi[vecaks].prev == -1) output << "0 " << marsiesi[vecaks].next << '\n'; //ja tikai iepriekšējais neeksistē
                else if (marsiesi[vecaks].next == -1) output << marsiesi[vecaks].prev << " 0\n"; //ja tikai iepriekšējais neeksistē
                else output << marsiesi[vecaks].prev << ' ' << marsiesi[vecaks].next << '\n'; //citādi izvada apskatāmā iepriekšējo un nākamo
             }
        }
        vecaks = 0; //atiestatam mainīgos, lai tos aprēķinātu no jauna
        berns = 0;
        kursors = 2; //atkal ignorējam pirmos divus simbolus
        input.getline(rinda, 15); //ielasa nākamo rindu
    }
}
