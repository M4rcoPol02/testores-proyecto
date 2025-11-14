
#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;


void PrintMatrix(vector<vector<int>> matrix);

class BooleanMatrix
{
    public:
    vector<vector<int>> differenceMatrix;
    vector<vector<int>> basicMatrix;
    int density;
    BooleanMatrix(int rows, int columns);

    private:
    vector<vector<int>> GenerateNewDifferenceMatrix(int rows, int columns);
    void BasicMatrix(vector<vector<int>>& differenceMatrix);
    float GetMatrixDensity(vector<vector<int>>& differenceMatrix);
   
};

#endif 


