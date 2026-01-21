#include <iostream>

using namespace std;


string months[] = { "January", "February", "March", "April", "May", "June",
                    "July", "August", "September", "October", "November", "December" };

int days[] = {31, 28, 31, 30, 31, 30,
              31, 31, 30, 31, 30, 31};

void monthData(int month);
void userInput(int year);

int main() { 
    do {
        int year, month;
        userInput(year);
        monthData(month);
    } while (true);

    return 0;
}

void monthData(int month) {
    cout << "Enter month number: " << endl;
    cin >> month;

    if (month < 1 || month > 12) {
        cout << "Please enter a valid month number (1-12)." << endl;
        return;
    }

    cout << "Month: " << months[month - 1] << endl;
    cout << "Number of days: " << days[month - 1] << endl;

}

void userInput(int year) {
    cout << "Enter a year: ";
    cin >> year;
    
    if (year < 1) {
        cout << "Please enter a valid year." << endl;
    }

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        cout << year << " is a leap year." << endl;
    } else {
        cout << year << " is not a leap year." << endl;
    }
}