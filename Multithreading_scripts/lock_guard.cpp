#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex m;
int number = 0;

void IncrementCount(const char thread_number, int j) {
    lock_guard<mutex> lock(m); // Automatically locks the mutex
    for (int i = 0; i < j; ++i) {
        ++number;
        // Mutex is automatically released when lock goes out of scope
        cout << "Thread t" << thread_number << " has count incremented to: " << number << endl;
    }
}

int main() {
    thread t1(IncrementCount, '1', 5);
    thread t2(IncrementCount, '2', 5);  

    t1.join();
    t2.join();

    return 0;
}