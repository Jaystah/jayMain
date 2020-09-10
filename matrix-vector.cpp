/*
@Creator: Jay Doerga

06-09-2020
*/

#include <iostream>
#include <vector>

using namespace std;
/*
{
    {1,2,3}             {2 x 1, 1x2, 3x3}
    {4,5,6}  x {2,1,3}  {2 x 4, 1x5, 3x6} = 13
    {7,8,9}             {2 x 7, 1x8, 3x9}   31
}                                           49
*/
int main(){

    vector<vector<double> > mainMatrix(3);
    vector<double> ans(3);
    vector<double> final(3);
    int num = 1;
    int id = 0;

    mainMatrix.at(0) = {static_cast<double>(num ), static_cast<double>(num + 1), static_cast<double>(num + 2)};
    for(int i = 0; i< mainMatrix.size(); i++){
        if(i!= mainMatrix.size() - 1){
        mainMatrix.at(i+1) = {static_cast<double>(num +3 + id), static_cast<double>(num + 4 + id) , static_cast<double>(num + 5 + id)};
        num++;
        id = 2;
    }}

    cout << "Please enter the three vector coefficients\n" << endl;
    cin >> ans.at(0);
    cin >> ans.at(1);
    cin >> ans.at(2);
    cout << endl;

    for(int i = 0; i < mainMatrix.size(); i++){
        for(int j = 0; j < mainMatrix[0].size(); j++){
            
            if(j==0){
                mainMatrix.at(i).at(j)*=ans.at(0);
            }else if(j==1){
                mainMatrix.at(i).at(j)*= ans.at(1);
            }else if(j==2){
                mainMatrix.at(i).at(j)*= ans.at(2);
            }

            if(i==0){
                final.at(0)+=mainMatrix.at(i).at(j);
            }else if(i==1){
                final.at(1)+=mainMatrix.at(i).at(j);
            }else if(i==2){
                final.at(2)+=mainMatrix.at(i).at(j);
            }

        }
    }
    
   cout << "The result vector is [";
   for(int i = 0; i< final.size();i++){
       if(i!=final.size()-1){
       cout << final.at(i) << ", ";
       }else{
           cout << final.at(i) << "]" << endl;
       }

   }


    return 0;
}