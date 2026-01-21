#include <iostream>

using namespace std;

string daysOfWeek[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
int zellersCongruence(int day, int month, int year);


int main() {

    int day, month, year;
    int dayOfWeek = zellersCongruence(day, month, year);
    cout << "The day of the week you were born is: " << daysOfWeek[dayOfWeek] << endl;

    return 0;
}

// Zeller's Congruence algorithm to find the day of the week for any date

int zellersCongruence(int day, int month, int year) {
    cout << "Enter day: ";
    cin >> day;

    cout << "Enter month (1-12): ";
    cin >> month;

    cout << "Enter year: ";
    cin >> year;


    // Adjust month and year for January and February
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    int K = year % 100;      // The year within the century
    int J = year / 100;      // The zero-based century

    int h = (day + ((13 * (month + 1)) / 5) + K + (K / 4) + (J / 4) - (2 * J)) % 7;

    return h;
}