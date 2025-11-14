//0.01 proyecto mates discretas

#include<iostream>
#include"local_include\Matrix.h"
#include"local_include\YYC.h"
#include"local_include\BT.h"

int main()
{
    //init random
    srand(time(0));
    BooleanMatrix booleanMatrix(10, 10);
    PrintMatrix(booleanMatrix.differenceMatrix);
    func1();

    PrintMatrix(booleanMatrix.basicMatrix);
    cout << "Density: " << booleanMatrix.GetMatrixDensity() << endl;
    
}