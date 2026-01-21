#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;


string doors [2] = {"Goat", "Car"};

int doors[3] = {0, 0, 0};

int chooseDoor();
int switchDoor(int initialChoice, int revealedDoor);
int revealDoor(int initialChoice, int carDoor);

int main() {



    return 0;
}

int chooseDoor() {
    srand(static_cast<unsigned int>(time(0)));
    int choice = rand() % 3;
    return choice;
}   

int carPostion() {
    srand(static_cast<unsigned int>(time(0)));
    int position = rand() % 3;
    return position;
}

int switchDoor(int initialChoice, int revealedDoor) {
    for (int i = 0; i < 3; i++) {
        if (i != initialChoice && i != revealedDoor) {
            return i;
        }
    }
    return -1; // Should never reach here
}

int revealDoor(int initialChoice, int carDoor) {
    for (int i = 0; i < 3; i++) {
        if (i != initialChoice && i != carDoor) {
            return i;
        }
    }
    return -1; // Should never reach here
}