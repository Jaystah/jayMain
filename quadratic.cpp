/*
@Creator: Jay Doerga

06-09-2002

*/

#include <iostream>
#include <cmath>

using namespace std;
    double a;
    double b;
    double c;
    double D;
    double x1;
    double x2;
    double getDiscriminant(double a, double b, double c);
    int quadratic(double D);
int main(){ 

    cout << "Please enter the values of a, b, and c: ";
    cin >> a;
    cin >> b;
    cin >> c;

    D = getDiscriminant(a,b,c);

    if(quadratic(D) == 0){
        cout << "There is no solution." << endl;
    }else if(quadratic(D) == 1){
        cout << "There is 1 solution.\n" << endl;
        cout << "The solution is: " << x1;

    }else if(quadratic(D) == 2){
 cout << "There are 2 solutions.\n" << endl;
        cout << "The solutions are: " << x1 << " and " << x2;

    };

    

    return 0;
}


double getDiscriminant(double a,double b,double c){
    return (b*b) - 4 * a * c;

}

int quadratic(double D){
    if(D>0){
        x1 = (-b + sqrt(D))/(2 * a);
        x2 = (-b - sqrt(D))/(2 * a);

        return 2;

    }else if(D<0){
        return 0;
        
    }else{
        x1 = (-b + sqrt(D))/(2 * a);
        return 1;

    }

}