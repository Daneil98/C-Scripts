#include <iostream>
#include <vector>

//typedef std::string text_t;
//typedef int number_t;

using  text_t = std::string;
using number_t = int;

int main() {

    text_t firstName = "David";
    number_t age = 23;

    std::cout << "The name is: " << firstName << '\n'; 
    std::cout << "Age is: " << age <<'\n';

    return 0;
}