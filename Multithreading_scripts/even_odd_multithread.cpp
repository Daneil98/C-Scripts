#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

typedef unsigned long  long ull;

ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end) {
    for (ull i = start; i < end; i++) {
        if (i % 2 == 0){
            EvenSum += i;
        }
    }
}

void findOdd(ull start, ull end){
    for (ull i = start; i < end; i++) {
        if (i%2!=0){
            OddSum += i;
        }
    }
}



int main() {

    ull start = 0, end = 1000000000;
    
    auto startTime = high_resolution_clock::now();


    thread t1(findEven, start, end);
    thread t2(findOdd, start, end);

    t1.join();
    t2.join();

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "Sum of Even Numbers: " << EvenSum << endl;
    cout << "Sum of Odd Numbers: " << OddSum << endl;
    cout << "Duration(s): " << duration.count()/1000000 << endl;

    return 0;
}