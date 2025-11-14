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
    this->rows = rows;
    this->columns = columns; 

    differenceMatrix = GenerateNewDifferenceMatrix(rows, columns);
    BasicMatrix();
    CalcMatrixDensity();
}

float BooleanMatrix::GetMatrixDensity()
{
    return density;
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
void BooleanMatrix::BasicMatrix()
{
    vector<vector<int>> basicMatrix;

    for (int i{}; i < rows; i++)
    {
        bool isBasic{true};

        for (int j = 0; j < rows; j++)
        {
            if(i == j) continue;
            if(IsBSubRowOfA(differenceMatrix.at(j), differenceMatrix.at(i)))
            {
                isBasic = false;
            }
        }

        if(isBasic)
        {
            basicMatrix.push_back(differenceMatrix.at(i));
        }
    }

    
    
    this->basicMatrix = basicMatrix;
}

bool BooleanMatrix::IsBSubRowOfA(vector<int> rowA, vector<int> rowB)
{
    bool isBLessThanA{false};

    for (int i{}; i < columns; i++)
    {
        if(rowA.at(i) == 0 && rowB.at(i) == 1)
        {
            return false;
        }
        else if(rowA.at(i) == 1 && rowB.at(i) == 0)
        {
            isBLessThanA = true;
        }
    }

    return isBLessThanA;
    
}
void BooleanMatrix::CalcMatrixDensity()
{
    int countOnes{0};
    for (int i{}; i < rows; i++)
    {
        for (int j{}; j < columns; j++)
        {
            if(differenceMatrix.at(i).at(j) == 1)
            {
                countOnes++;
            }
        }
    }

    this->density = float(countOnes) / float((rows * columns));
}