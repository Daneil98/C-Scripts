#include <iostream>

using namespace std;   

class Vector {
    public:
        Vector(int s);
        double& operator[](int i);
        int size();
    private:
        double* elem; // elem points to an array of sz doubles
        int sz;
};

Vector::Vector(int s) :elem{new double[s]}, sz{s} {} // initialize members

double& Vector::operator[](int i){
    return elem[i];
}

int Vector::size() {
    return sz;
}

void test();


int main() {

    test();

    return 0;
}


void test() {
    try {
        Vector v(-27);
    }
    
    catch (std::length_error&) { // do something and rethrow
        cerr << "test failed: length error\n";
        throw; // rethrow
    }
    
    catch (std::bad_alloc&) { // Ouch! this program is not designed to handle memory exhaustion
        std::terminate(); // terminate the program
    }
}