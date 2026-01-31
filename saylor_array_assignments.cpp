#include <iostream>

using namespace std;

void selectionSort(int arr[], int n);

int main() { 

    int profit[6] = {150, 300, 500};

    cout << profit[3] << endl;
    cout << profit[0] << endl;
    cout << profit[6] << endl;

    /** 
    int list[10] = {0};
    int k;
    for (k = 0; k < 5; k++)
    list[2 * k + 1] = k + 2;
    for (k = 0; k < 10; k++)
    printf ("%4d\n", list[k]);
    */

    int array[8] = {7, 8, 26, 44, 13, 23, 98, 57};

    char teams[ ] = {'L','a','k','e','r','s','\0','N','e','t','s','\0'};

    printf(" %s",teams);

    printf("%s",teams+7);
    printf("%s",(teams+3));
    //printf("%s",teams[0]);   Segmentation fault
    //printf("%c",(teams+0)[0]);
    printf("%c",(teams+5));
    printf("%c",(teams-200)[202]);



    return 0;
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        swap(arr[min_idx], arr[i]);
    }
}