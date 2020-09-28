#include <iostream>
#include <cmath>
#include <set>


int pdi_example(int number, int base = 10){
    int total = 0;
    while (number>0){
        total = total + pow(number % base, 2);
        number = number / base;
    }
    return total;
}
bool is_happy(int number){
std::set<int> seen_numbers;
while(number > 1 && !seen_numbers.count(number)){
    seen_numbers.insert(number);
    number = pdi_example(number);
}
return number == 1;
}

int main(){
    std::cout << "Which number do you want to test? ";
    int num;
    std::cin >> num;
if(is_happy(num)){
std::cout << num << " is happy!" << std::endl;
}else{

std::cout << num << " is unhappy!" << std::endl;
}




    return 0;
}