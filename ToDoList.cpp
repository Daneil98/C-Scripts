#include <iostream>
#include <list>
#include <ctime>
#include <string>


class TodoItem {
    private:
        int id;
        std::string description;
        bool completed;

    public:
        TodoItem(): id(0), description(""), completed(false) {}   //class initializer
        ~TodoItem() = default;

        bool create(std::string new_description) {
            id = rand() % 100 + 1; // Generate a random int between 1 and 100
            description = new_description;
            return true;
        }

        int getId(){ return id; }
        std::string getDescription() { return description; }
        bool isCompleted() { return completed; }
        void setCompleted(bool val) { completed = val; } //this function sets the task as completetd

};

int main(){

    char input_option;
    std::string input_description;
    int input_id;
    std::string version = "v0.1.0";
    std::list<TodoItem> todoItems;    //creates todoitems list
    std::list<TodoItem>::iterator it;

    srand(time(NULL));
    todoItems.clear();      // start the list as a fresh list

    //TodoItem test;
    //test.create("This is a test");
    //todoItems.push_back(test);

    while (1){              //create infinite while loop for TodoList console app
        system("cls");
        std::cout << "Todo List Maker - " << version << std::endl;
        std::cout << std::endl << std::endl;

        
        for (it = todoItems.begin(); it != todoItems.end(); it++) {

            std::string completed = it->isCompleted() ? "done" : "not done";

            std::cout << it->getId() << " | " << it->getDescription() << " | "
                << completed << std::endl;

        } 

        if (todoItems.empty()) {
            std::cout << "Add your first Todo Item!" << std::endl;
        }

        std::cout << std::endl << std::endl;

        std::cout << "[a]dd a new Todo Item" << std::endl;
        std::cout << "[c]omplete a Todo Item" << std::endl;
        std::cout << "[q]uit" << std::endl;

        std::cout << "choice: ";

        std::cin >> input_option;

        if (input_option == 'q') {
            std::cout << "Have a great day!" << std::endl;
            break;
        }

        else if (input_option == 'a') {
            std::cout << "Add a new description: ";
            std::cin.clear();
            std::cin.ignore();
            std::getline(std::cin, input_description);

            TodoItem newItem;
            newItem.create(input_description);
            todoItems.push_back(newItem);
        }

        else if (input_option == 'c') {
            std::cout << "Enter id to mark completed: ";
            std::cin >> input_id;

            for (it = todoItems.begin(); it != todoItems.end(); it++) {
                if (input_id == it->getId()) {
                    it->setCompleted(true);
                    break;
                }
            }
        }
        
    }


    return 0;
}