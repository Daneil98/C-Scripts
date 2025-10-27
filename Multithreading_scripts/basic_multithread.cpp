#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void threadFunction(){
    for (int i =0; i<5; i++) {
        cout << "Thread Executing" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void threadwithParams(int id, const string& message) {
    cout << "thread "<< id << ": " << message << endl; 
}


int main () {
    //create a thread object that executes the threadFunction
    //thread t(threadFunction);


    auto lambda1 = []() {
        for (int i = 0; i<3; i++) {
            cout << "Lambda thread 1: " << i << endl;
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    };
    
    thread t1(lambda1);
    thread t2([]() {
        cout << "Lambda thread 2 executing" <<endl;
    });
    
    //thread t1(threadwithParams, 1, "Hello from thread 1");
    //thread t2(threadwithParams, 2, "Hello from thread 2");

    //wait for the thread to finish 
    t1.join();
    t2.join();

    return 0;
}