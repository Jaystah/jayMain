/*

@Creator: Jay Doerga
13-09-2020

*/

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
using namespace std;
int main(){
int n = 0;
int x = 0;
// e = (1/(1+n))^n
double e;

while(1){
e = pow(1+(1/static_cast<double>(n)),static_cast<double>(n));
   cout << "\r" << e << flush;
   

n+=3;

this_thread::sleep_for(chrono::milliseconds(10));

x++;




}
 return 0;
}