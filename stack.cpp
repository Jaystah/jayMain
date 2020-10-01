#include <iostream>
#include <limits>
#include <vector>

class Stack {
    public:
        Stack();
        bool isEmpty() const;
        int top() const;
        int pop();
        void push(int i);
        std::string toString() const;
    private:
        std::vector<int> elements;
};
Stack::Stack(){

}
 bool Stack::isEmpty() const{
     if(elements.size() == 0){
         return true;
     }
     return false;
}

int Stack::top() const{
    if(elements.size() == 0 ){
        throw std::runtime_error("stack is empty");
    }
        return elements.at(0);

}

int Stack::pop(){
        if(elements.size() == 0 ){
        throw std::runtime_error("stack is empty");
    }
        int temp = elements.at(0);
        elements.erase(elements.begin());
        return temp;
}

void Stack::push(int i){
    if(elements.size() == 0){
        elements.push_back(i);
    }else{
    elements.push_back(elements.at(elements.size() - 1));
    for(int a = elements.size() - 2; a >= 0; a--){
        if(a==0){
            elements.at(a) = i;
        }else{
          elements.at(a) = elements.at(a - 1);
        }

    }
    }
}

std::string Stack::toString() const{
    if(elements.size() == 0){
        return "[]";
    }
    std::string ans = "[";
    int a = 3;
    for(int i = 0; i<elements.size(); i++){
        if(i != elements.size()-1){
              ans+=std::to_string(elements.at(i));
              ans+=',';
        }
        else{
              ans+=std::to_string(elements.at(i));
              ans+=']';
        }
    }
    return ans;
}

int main() {
    Stack stack;
    
    while (true) {
        try {
            std::cout << "stack> ";
            
            std::string command;
            std::cin >> command;
            
            if ( (command.compare("end") == 0) || std::cin.eof() ){
                break;
            } else if (command.compare("top") == 0) {
                std::cout << stack.top() << std::endl;
            } else if (command.compare("pop") == 0) {
                std::cout << stack.pop() << std::endl;
            } else if (command == "push") {
                if ( std::cin.eof() ) break;
                int i;
                std::cin >> i;
                bool failed = std::cin.fail();
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if ( failed ){
                  throw std::runtime_error("not a number");
                }
                stack.push(i);
            } else if ( command.compare("list") == 0){
                std::cout << stack.toString() << std::endl;;
            } else {
                throw std::runtime_error("invalid command");
            }
        } catch (std::runtime_error& e) {
            std::cout << "error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}