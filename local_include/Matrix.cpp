#include<iostream>
#include<string>
#include<vector>
#include"Matrix.h"

using namespace std;


void PrintMatrix(vector<vector<int>> matrix)
{
    for (int i{}; i < matrix.size(); i++)
    {
        for (int j{}; j < matrix.at(i).size(); j++)
        {
            cout << matrix.at(i).at(j) << " ";
        }

        cout << endl;
    }
}
 

BooleanMatrix::BooleanMatrix(int rows, int columns)
{
    differenceMatrix = GenerateNewDifferenceMatrix(rows, columns);
}


vector<vector<int>> BooleanMatrix::GenerateNewDifferenceMatrix(int rows, int columns)
{
    vector<vector<int>> randDifferenceMatrix(rows, vector<int>(columns));
    for (int i{}; i < rows; i++)
    {
        for (int j{}; j < columns; j++)
        {
            randDifferenceMatrix.at(i).at(j) = rand() % 2;
        }
        
    }
    return randDifferenceMatrix;
    
}
void BooleanMatrix::BasicMatrix(vector<vector<int>>& differenceMatrix)
{
    return;
}
float BooleanMatrix::GetMatrixDensity(vector<vector<int>>& differenceMatrix)
{
    return 0.1f;
}