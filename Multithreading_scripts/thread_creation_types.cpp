#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

//1. Function Pointer
void fun(int x) {
    while (x-->0) {
        cout << x << endl;
    }
}


//2. lambda Expression
auto fun_lambda = [](int x) {
    while (x-->0) {
        cout << x << endl;
    }
};


//3. Functor
class Functor {
    public:
        void operator() (int x) {
            while (x-->0) {
                cout << x << endl;
            }
        }
};

//4. Non static Member Function
class Base {
    public:
        void run (int x) {
            while (x-->0) {
                cout << x << endl;
            }
        }
};


//5. static Member Function
class Base_static {
    public:
        static void run (int x) {
            while (x-->0) {
                cout << x << endl;
            }
        }
};


int main() {

    Base_static b;     
    std::thread t1(&Base_static::run, 5);
    

    //std::thread t1(&Base::run, &b, 5);      // Non static Member Function insertion
    //std::thread t1(Functor (), 5);    functor insertion  
    //std::thread t2(fun_lambda, 10);   lambda expression insertion
    t1.join();
    //t2.join();
    
    return 0;
}