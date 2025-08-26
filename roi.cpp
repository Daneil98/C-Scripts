#include <iostream>
#include <string>
//#include <iomanip>

using namespace std;

int main(){

    string stock;
    double current_price, ATH, roi;
  
    cout << "What is the name of the stock? ";
    getline(cin, stock);

    cout << "What is the current price and ATH? ";
    cin >> current_price >> ATH;

    roi = ((ATH - current_price)/current_price) * 100;
    cout << stock << "'s potential ROI is " << roi << "%";

    return 0;
}

//TSLA 54.7716%