#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

using namespace std; 
typedef long int ull;

//Producer
void findOdd(promise<ull>&& OddSumPromise, ull start, ull end) {
    ull OddSum = 0;
    for (ull i = start; i <= end; ++i) {
        if (i & 1) {
            OddSum += i;
        }
    }
    OddSumPromise.set_value(OddSum);
}

void findEven(){

}


int main() {
    ull start = 0, end = 1900000000;

    promise <ull>  OddSum;
    future <ull> OddFuture = OddSum.get_future();

    cout << "Thread Created! " << endl;
    thread t1(findOdd, move(OddSum), start, end);

    cout << "Waiting for Result" << endl;

    cout << "Oddsum: " << OddFuture.get() << endl;      //Consumer

    cout << "Completed!" << endl;

    t1.join();

    return 0;
}

