#include <iostream>
using namespace std;
int checkBreakTime(int currentTime){
    int hundrethPlace = (currentTime / 100) % 10;
    return hundrethPlace;

    
}

int main() {
    int temp = 0;
    // if (temp>=100){
    cout<<checkBreakTime(temp);
    // }
    
}