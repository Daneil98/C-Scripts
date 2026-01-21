#include <iostream>

void some_function(){ // function that doesn't return a value
    
    double d = 2.2; // initialize floating-point number
    int i = 7; // initialize integer
    d = d+i; // assign sum to d
    i = d*i; // assign product to i; beware: truncating the double d*i to an int
    i = ++i;
    std::cout << i << " " << d << std::endl;
}

int main(){
    some_function();

    std::cout << 9*7;
}

