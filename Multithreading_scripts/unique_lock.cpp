#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex m;

int buffer = 0;

void task(const char thread_id, int iterations) {
    //unique_lock<mutex> lock(m); // Lock the mutex
    unique_lock<mutex> lock(m, defer_lock); // Create unique_lock without locking
    lock.lock(); // Manually lock the mutex
    for (int i = 0; i < iterations; ++i) {
        ++buffer;
        cout << "Thread " << thread_id << " : " << buffer << endl;
    }

    // Mutex is automatically released when 'lock' goes out of scope
}


int main() {

    thread t1(task, 'A', 5);
    thread t2(task, 'B', 5);

    t1.join();
    t2.join();
    return 0;
}