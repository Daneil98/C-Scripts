#include <iostream>

using namespace std;


int grades [] = {};
void sortArray(int* arr, int size);

int main() {

    int temp;
    int high = 0;
    int low = 0;

    cout << "Enter how many grades you would like to input: ";
    int numberOfGrades;
    cin >> numberOfGrades;

    int* grades = new int[numberOfGrades];

    for (int i = 0; i < numberOfGrades; ++i) {
        cout << "Enter grade " << (i + 1) << ": ";
        cin >> grades[i];
    }

    sortArray(grades, numberOfGrades);

    return 0;
}

void sortArray(int* arr, int size) {
    for (int i =0; i < size -1; i++) {
        for (int j=0; j < size - i -1; j++) {
            if (arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    cout << "Sorted grades: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
}