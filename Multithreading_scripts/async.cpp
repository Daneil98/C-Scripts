#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

using namespace std;
typedef long int ull;

//Producer
ull findOdd(ull start, ull end) {
    ull OddSum = 0;
    cout << "ThreadID of findOdd: " << this_thread::get_id() << endl;
    for (ull i = start; i <= end; ++i) {
        if (i & 1) {
            OddSum += i;
        }
    }
    return OddSum;
}

void findEven(){

}


int main() {
    ull start = 0, end = 1900000000;

    cout << "ThreadID: " << this_thread::get_id() << endl;
    cout << "Thread Created if policy is std::launch::async! " << endl;
    future <ull> OddSum = async(launch::async, findOdd, start, end);


    cout << "Waiting for Result" << endl;

    cout << "Oddsum: " << OddSum.get() << endl;      //Consumer

    cout << "Completed!" << endl;

    return 0;
}

