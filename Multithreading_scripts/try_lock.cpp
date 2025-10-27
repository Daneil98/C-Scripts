#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int x=0, y=0;
mutex m1, m2;






void doSomeWorkForSeconds(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void incrementXY(int& xory, mutex& m, const char* description) {
    for (int i=0; i <5; i++) {
        m.lock();
        ++xory;
        cout << description << ": " << xory << endl;
        m.unlock();

        doSomeWorkForSeconds(1); 
    }
}

void consumeXY() {
    int useCount = 5;
    int XplusY = 0;
    while(1) {
        int lockResult = try_lock(m1, m2);
        if (lockResult == -1) {
            if (x > 0 && y > 0) {
                --useCount;
                XplusY += x + y;
                x = 0;
                y = 0;
                cout << "X + Y = " << XplusY << ", useCount = " << useCount << endl; 
            }
            m1.unlock();
            m2.unlock();
            if (useCount == 0) { break; }
        }

    }
}

int main() {

    thread t1(incrementXY, ref(x), ref(m1), "X");
    thread t2(incrementXY, ref(y), ref(m2), "Y");
    thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
