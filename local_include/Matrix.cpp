#include<iostream>
#include<string>
#include<vector>
#include"Matrix.h"
#include<iomanip>

using namespace std;


void PrintMatrix(const vector<vector<int>>& matrix)
{
    if (matrix.empty()) {
        cout << "Matrix is empty!" << endl;
        return;
    }
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Calculate the maximum row number digits
    int maxRowDigits = to_string(rows).length();
    int rowLabelWidth = maxRowDigits + 1; // "f" + digits
    
    // Print column headers with proper spacing
    cout << string(rowLabelWidth + 1, ' '); // Space for row labels + extra
    for (int col = 0; col < cols; col++) {
        cout << "c" << (col + 1) << " ";
    }
    cout << endl;
    
    // Print separator line that matches exactly
    cout << string(rowLabelWidth + 1, ' ');
    for (int col = 0; col < cols; col++) {
        cout << "---";
    }
    cout << endl;
    
    // Print matrix with perfectly aligned row labels
    for (int row = 0; row < rows; row++) {
        // Print row label with consistent width
        cout << "f" << (row + 1) 
             << string(rowLabelWidth - to_string(row + 1).length() - 1, ' ')
             << "|";
        
        // Print row data
        for (int col = 0; col < cols; col++) {
            cout << " " << matrix[row][col] << " ";
        }
        cout << endl;
    }
}

void PrintTestorsList(const vector<vector<int>>& testors) {
    if (testors.empty()) {
        cout << "No se encontraron testores\n";
        return;
    }
    
    for (size_t i = 0; i < testors.size(); i++) {
        cout << "f" << (i + 1) << " (";
        for (size_t j = 0; j < testors[i].size(); j++) {
            cout << "c" << (testors[i][j] + 1);
            if (j < testors[i].size() - 1) {
                cout << ",";
            }
        }
        cout << ")\n";
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

bool BooleanMatrix::IsBSubRowOfA(const vector<int>& rowA, const vector<int>& rowB)
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