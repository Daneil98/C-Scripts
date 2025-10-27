#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int amount = 0;
timed_mutex m;




void increment(int i) {
    //if(m.try_lock_for(chrono::seconds(2))) {
    auto now = chrono::steady_clock::now();
    if (m.try_lock_until(now + chrono::seconds(2))) {   
        amount++;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Thread " << i << " acquired the lock." << endl;
        cout << "Incremented by " << i << ", total amount: " << amount << endl;
        m.unlock();
    }
    else {
        cout <<"Thread "<< i << " failed to acquire lock." << endl;
    }
}


int main() {
    thread t1(increment, 1);
    thread t2(increment, 2);

    t1.join();
    t2.join();


    cout << "Final amount: " << amount << endl;
    return 0;
}