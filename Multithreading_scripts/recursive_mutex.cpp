#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
recursive_mutex m;

int buffer = 0;

void recursion(char c, int count) {
    if (count <0){
        return;
    }

    m.lock();
    ++buffer;
    cout << "Thread " << c << " : " << buffer << endl;
    recursion(c, count - 1);
    m.unlock();
    cout << "Thread " << c << " unlocked mutex." << endl;
}



int main() {

    thread t1(recursion, 'A', 5);
    thread t2(recursion, 'B', 5);

    t1.join();
    t2.join();

    return 0;
}