
#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;


void PrintMatrix(vector<vector<int>> matrix);

class BooleanMatrix
{
    private:
    int rows,columns;
    float density;
    vector<vector<int>> GenerateNewDifferenceMatrix(int rows, int columns);
    void BasicMatrix();
    bool IsBSubRowOfA(vector<int> rowA, vector<int> rowB);
    void CalcMatrixDensity();

    public:
    vector<vector<int>> differenceMatrix;
    vector<vector<int>> basicMatrix;
    BooleanMatrix(int rows, int columns);
    float GetMatrixDensity();

    
   
};

#endif 


