#include <iostream>
using namespace std;
bool valid(int barberNum, int time, int duration){
   int hundrethPlace = (time / 100) % 10;
//    int hundrethPart = time % 1000;
    if (hundrethPlace == barberNum){
        return false;
    }
    else {
        int endTime = time + duration - 1;
        if (time < barberNum*100 && endTime >= barberNum*100) {
            return false;
        }
        else if(time > (barberNum*100) + 99 && endTime >= barberNum*100+1000) {
            return false;
        }
        return true;
    }
}

int main() {
    cout << valid(11710) << endl;

}