#include <iostream>

using namespace std;

//USER DEFINED VECTOR TYPE  

struct Vector {
    int sz;
    double* elem;           //By itself this pointer points to nothing
};

void vector_init(Vector& v, int s)  //pass v by a non-constant reference for the vector being passed can be modified
{
    v.elem = new double[s];
    v.sz = s;
}

double read_and_sum(Vector& v, int s) {
 //   Vector v;
//    vector_init(v, s);

/**    for (int i = 0; i<s; i++){
        cin >> v.elem[i]; 
    }
 */
    double sum = 0;
    for (int i = 0; i<s; i++) {
        sum += v.elem[i];
    }
    return sum;
}

//This function accesses struct members through a name, reference and uses −> to access through a pointer.
void f(Vector v, Vector& rv, Vector* pv) {
    int i1 = v.sz;
    int i2 = rv.sz;
    int i3 = pv->sz;
}

int main() {
    Vector v;
    vector_init(v, 4);

    for (int i =0; i < v.sz; i++){
        v.elem[i] = i * 1.1;
    }
    
    for (int i =0; i < v.sz; i++){
        cout << v.elem[i] << endl;
    }

    cout << "Sum of all vector elements is: " << read_and_sum(v, 4) << endl;

    return 0;
}