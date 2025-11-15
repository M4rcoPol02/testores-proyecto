//0.01 proyecto mates discretas

#include<iostream>
#include"local_include\Matrix.h"
#include"local_include\YYC.h"
#include"local_include\BT.h"

int main()
{
    //init random
    srand(time(0));
    
    BooleanMatrix booleanMatrix(5, 5);
    cout << "Difference Matrix: " << endl;
    PrintMatrix(booleanMatrix.differenceMatrix);


    cout << "Basic Matrix: " << endl;
    PrintMatrix(booleanMatrix.basicMatrix);
    cout << "Density: " << booleanMatrix.GetMatrixDensity() << endl;

    cout << "Starting YYC Incremental Algorithm..." << endl;
    cout << "Finding Typical Testors..." << endl;
    RunYYCIncremental(booleanMatrix.basicMatrix);

    cout << endl;

    cout <<"Starting BT Algorithm..." << endl;
    BT bt(booleanMatrix.basicMatrix.at(0).size());

    cout << "Finding Typical Testors..." << endl;
    vector<vector<int>> typicalTestors = bt.FindTypicalTestors(booleanMatrix.basicMatrix);

    cout << "Typical Testors found:" << endl;
    
    PrintMatrix(typicalTestors);
    
}