#include <iostream>

using namespace std;

class Vector {
    private:
        double* elem;
        int sz;
    public:
        Vector(int s);                      //constructor
        ~Vector() { delete[] elem;}         //destructor
        Vector(const Vector & a);           //copy constructor
        Vector& operator= (const Vector& a); //copy assignment operator
};



Vector::Vector(const Vector& a): elem{new double[a.sz]}
    {for (int i=0; i!=sz; ++i) {
        elem[i] = a.elem[i];
    }}



