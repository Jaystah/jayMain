/*
@Creator: Jay Doerga
15-9-2020
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

void outputData(std::vector<int>& nums, std::vector<char>& c){
    
    std::cout << "The compressed data is: ";
    if(nums.size() == c.size()){
        for(int i = 0; i<nums.size(); ++i){
              std::cout << nums.at(i) << c.at(i);
         }
        std::cout << std::endl;
    }

}

int askForInput(std::string& str){

    std::cout << "Enter the data to be compressed: ";
    getline(std::cin,str);

    try{
         for(int i = 0; i<str.size(); ++i){
             if(str.at(i) < 97 || str.at(i) > 122){
                 throw std::runtime_error("error: invalid input");
             }
         }
    }
    catch(std::runtime_error excpt){
        std::cout << excpt.what() << std::endl;
        return 1;
    }

    return 0;
    
}

void getCompressedData(std::string& data){
    
    char current;
    std::vector<int> amounts;
    std::vector<char> chars;
    int count = 1;
    
    for(int i = 0; i<data.size(); ++i){
        current = data.at(i);

        if(i != data.size() - 1){
            if(data.at(i + 1) == current){
                 count++;
            }else{
                amounts.push_back(count);
                chars.push_back(data.at(i));
                count = 1;
            }
        }else{
            if(data.size()==1){
                amounts.push_back(count);
                chars.push_back(data.at(i));
            }
            else if(current == data.at(i - 1)){
                amounts.push_back(count);
                chars.push_back(data.at(i));
            }else{
                count = 1;
                amounts.push_back(count);
                chars.push_back(data.at(i));
            }
        }
    }

    outputData(amounts,chars);
   
}


int main(){

    std::string input;

    if(askForInput(input) != 1){
        getCompressedData(input);
    }

    return 0;

}