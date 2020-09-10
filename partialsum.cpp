/*
@Creator: Jay Doerga

06-09-2020

*/
#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    int x;
    int num = 1;
    int count = 1;

    cout << "Summing up 1 to n, please enter n: ";
    cin >> n;
    vector<int> partialSums(n);
    cout << "Which partial sum (1+...+x) would you like to know? Please enter x<=n : ";
    cin >> x;

    for(int i = 0; i< partialSums.size(); ++i){
        partialSums.at(i) = num;
        count++;
        num+=count;
    }


    for(int i = 1; i<=x; ++i){

        if(i != x){
            cout << i << "+";
        }else {
            cout << i;
        }

    }

    cout << " = " << partialSums.at(x-1) << endl; 
    cout << "The entire sequence of partial sums up to " << n << " is: ";

    for(int i = 0; i< partialSums.size(); ++i){
       cout << partialSums.at(i) << " ";

    }
    
    return 0;
}