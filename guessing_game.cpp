#include <iostream>



int main(){
    
    int num, guess;
    int tries=0;
    
    srand(time(NULL));
    num = rand() % 10 + 1;

    std::cout << "**** NUMBER GUESSING GAME *****\n";

    do{
        std::cout << "Guess a number between 1 - 10: ";
        std::cin >> guess;
        tries++;

        if(guess > num){
            std::cout << "Your guess is too high!\n";
        }

        else if(guess < num){
            std::cout << "Your guess is too low!\n";
        }

        else{
            std::cout << "You guessed the number " << num << " correctly\n";
            std::cout << "It took you " << tries << " tries";
        }
    }while(guess != num);

}