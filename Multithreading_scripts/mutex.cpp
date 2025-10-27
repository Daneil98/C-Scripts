#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int my_counter = 0;
mutex my_mutex;

void increment_counter(int iterations = 100000) {
    for (int i = 0; i < iterations; ++i) {
        // Lock the mutex before modifying the shared resource
        if (my_mutex.try_lock()) {
            ++my_counter;
            // Unlock the mutex after modification
            my_mutex.unlock();
        }
        else {
            // If the lock is not acquired, we can choose to wait or skip
            // Here we simply skip this iteration
            this_thread::yield(); // Yield to allow other threads to proceed
        }
    }
}


int main() {
    thread t1(increment_counter, 100000);
    thread t2(increment_counter, 100000);

    t1.join();
    t2.join();

    cout << "Final counter value: " << my_counter << endl;

    return 0;
}