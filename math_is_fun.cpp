#include <iostream>

using namespace std;


int main() {

    int high = 0; 
    int low = 0;
    int average, temp;

    cout << "Enter how many grades you would like to input: ";
    int numberOfGrades;
    cin >> numberOfGrades;

    int* grades = new int[numberOfGrades];

    for (int i = 0; i < numberOfGrades; ++i) {
        cout << "Enter grade " << (i + 1) << ": ";
        cin >> grades[i];
        if (grades[i] > high) high = grades[i];
        if (grades[i] < low || low == 0) low = grades[i];
        temp += grades[i];   
    }
    average = temp / numberOfGrades;

    cout << "Highest grade: " << high << endl;
    cout << "Lowest grade: " << low << endl;
    cout << "Average grade: " << average << endl;

    return 0;
}


