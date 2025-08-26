#include <iostream>

using namespace std;

int main() {
	double f_temp;

	cout << "Enter the temperature in fahrenheit: ";
	cin >> f_temp;

	double c_temp = 5.0/9.0 * (f_temp - 32);
	cout << "The temperature in Celcius is: " << c_temp;

	return 0;
}