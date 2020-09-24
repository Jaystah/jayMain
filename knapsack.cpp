#include <iostream>
#include <vector>
#include <fstream>

int maxInt(int a, int b){
    return a>b ? a : b;
}

int valueOfKnapsack(int capacity, int pos, std::vector<std::vector<int> > knapsack, std::vector<bool> &isInSack){
    if(capacity == 0 || pos>knapsack.size()-1){
        return 0;
    }
    
    if(knapsack.at(pos).at(0) > capacity){
        isInSack.at(pos) = false;
        return valueOfKnapsack(capacity, pos+1, knapsack, isInSack);

    }

    std::cout << "Option No in Position: " << pos << ": "  << valueOfKnapsack(capacity, pos+1, knapsack, isInSack) <<  std::endl;
    std::cout << "Option Yes in Position: " << pos << ": "  << knapsack.at(pos).at(1) +  valueOfKnapsack(capacity - knapsack.at(pos).at(0), pos+1, knapsack, isInSack ) << "\n"  << std::endl;
    isInSack.at(pos) = true;

    return maxInt(valueOfKnapsack(capacity, pos+1, knapsack, isInSack), knapsack.at(pos).at(1) +  valueOfKnapsack(capacity - knapsack.at(pos).at(0), pos+1, knapsack, isInSack ));

}

int main(int argc, char* argv[]){
    int capacity;
    std::vector<bool> inSack;
    std::vector<std::vector<int> > values;
    std::vector<int> weights;
    unsigned int i = 0;

    if(argc <= 1){
         std::cout << "No input filename given" << std::endl;
    }

    std::ifstream inputFile;

    inputFile.open(argv[1]);

    if(!inputFile.is_open()){
        std::cout << "Could not open file " << argv[1];
    }

    inputFile >> capacity;

    while(!inputFile.eof()){
        
        int weight;
        inputFile >> weight;
        int value;
        inputFile >> value;
        std::vector<int> a(2);
        a.at(0) = weight;
        a.at(1) = value;
        values.push_back(a);
    }

    values.pop_back();

    for(int i = 0; i<values.size(); i++){
        std::cout << "Weight: " << values.at(i).at(0) << " | Value: " << values.at(i).at(1) << std::endl;
    }

    inSack.resize(values.size());
    int answer = valueOfKnapsack(capacity, 0, values, inSack);
    int remainingWeight = 0;

    for(int i = 0; i<inSack.size();i++){
        if(inSack.at(i)){
            remainingWeight+=values.at(i).at(0);
        }
    }

    std::cout << "With a capacity of " << capacity << " kg, the total value is "<< answer << " Eur, leading to a total weight of " << remainingWeight << " kg" << std::endl;
    std::cout << "The following items are included: ";

    for(int i = 0; i<inSack.size();i++){
        if(inSack.at(i)){
            std::cout << "[" << values.at(i).at(0) << "," << values.at(i).at(1) << "] ";
        }
    }
   
   std::cout << std::endl;
   for(int i = 0; i<inSack.size(); i++){
       std::cout << i << ": " << inSack.at(i) << std::endl;
   }

}