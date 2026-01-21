#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
double balance = 0;

mutex m;
condition_variable cv;

void deposit(double amount) {
    {
        lock_guard<mutex> lock(m);
        balance += amount;
        cout << "Deposited: " << amount << ", New Balance: " << balance << endl;
    }
    cv.notify_all(); // Notify waiting threads that balance has changed
}

void withdraw(double amount) {
    unique_lock<mutex> lock(m);
    cv.wait(lock, [] { return (balance>0) ? true : false; }); // Check if balance is above zero before proceeding
    if (balance >= amount) {
        balance -= amount;
        cout << "Withdrew: " << amount << ", New Balance: " << balance << endl;
    } else {
        cout << "Insufficient balance for withdrawal of: " << amount << endl;
    }   
}


int main() {
    thread t1(deposit, 100.0);
    thread t2(withdraw, 50.0);
    thread t3(withdraw, 70.0);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}   