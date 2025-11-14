//0.01 proyecto mates discretas

#include<iostream>
#include"local_include\Matrix.h"


int main()
{
    //init random
    srand(time(0));
    BooleanMatrix booleanMatrix(5, 10);
    PrintMatrix(booleanMatrix.differenceMatrix);
    
}