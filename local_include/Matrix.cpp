#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
using namespace std;

// ========================================
//          CONSTRUCTORES
// ========================================
BooleanMatrix::BooleanMatrix(const vector<vector<int>>& matrix)
{
    rows = matrix.size();
    columns = rows > 0 ? matrix[0].size() : 0;
    differenceMatrix = matrix;
    BasicMatrix();
    CalcMatrixDensity();
}

BooleanMatrix::BooleanMatrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    differenceMatrix = GenerateNewDifferenceMatrix(rows, columns);
    BasicMatrix();
    CalcMatrixDensity();
}

// ========================================
//           STATIC BasicMatrix()
// ========================================
vector<vector<int>> BooleanMatrix::BasicMatrix(const vector<vector<int>>& matrix)
{
    BooleanMatrix obj(matrix);
    return obj.basicMatrix;
}

// ========================================
//            GENERA MATRIZ BÁSICA
// ========================================
void BooleanMatrix::BasicMatrix()
{
    vector<vector<int>> result;

    for (int i = 0; i < rows; i++)
    {
        bool isBasic = true;
        for (int j = 0; j < rows; j++)
        {
            if (i == j) continue;
            if (IsBSubRowOfA(differenceMatrix[j], differenceMatrix[i]))
            {
                isBasic = false;
                break;
            }
        }
        if (isBasic)
            result.push_back(differenceMatrix[i]);
    }
    basicMatrix = result;
}

// ========================================
//     DEFINICIÓN DE SUBFILA (del texto)
// ========================================
bool BooleanMatrix::IsBSubRowOfA(const vector<int>& A, const vector<int>& B)
{
    bool strictlySmaller = false;
    for (size_t i = 0; i < A.size(); i++)
    {
        if (A[i] == 0 && B[i] == 1) return false;
        if (A[i] == 1 && B[i] == 0) strictlySmaller = true;
    }
    return strictlySmaller;
}

// ========================================
//        GENERA MATRIZ DE DIFERENCIA
// ========================================
vector<vector<int>> BooleanMatrix::GenerateNewDifferenceMatrix(int rows, int columns)
{
    vector<vector<int>> m(rows, vector<int>(columns));
    for (auto& r : m)
        for (auto& v : r)
            v = rand() % 2;
    return m;
}

// ========================================
//            MATRIZ DE DENSIDAD
// ========================================
void BooleanMatrix::CalcMatrixDensity()
{
    int ones = 0;
    for (auto& r : differenceMatrix)
        for (auto v : r)
            if (v == 1) ones++;

    density = float(ones) / float(rows * columns);
}

float BooleanMatrix::GetMatrixDensity()
{
    return density;
}

// ========================================
//   CONVERTIR TESTORES A MATRIZ BOOLEANA
// ========================================
vector<vector<int>> BooleanMatrix::TestorsToMatrix(const vector<vector<int>>& testors, int numColumns)
{
    vector<vector<int>> result;
    for (const auto& t : testors)
    {
        vector<int> row(numColumns, 0);
        for (int col : t) row[col] = 1;
        result.push_back(row);
    }
    return result;
}

// ========================================
//           IMPRIMIR MATRIZ
// ========================================
// ========================================
//           IMPRIMIR MATRIZ (MEJORADA)
// ========================================
void PrintMatrix(const vector<vector<int>>& matrix)
{
    if (matrix.empty()) {
        cout << "Matriz vacia\n";
        return;
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Encabezado informativo
    cout << "Matriz: " << rows << " filas x " << cols << " columnas\n";

    // Encabezado de columnas
    cout << "    ";
    for (int j = 0; j < cols; j++)
        cout << setw(2) << j + 1 << " ";
    cout << "\n    ";
    for (int j = 0; j < cols; j++)
        cout << "---";
    cout << endl;

    // Imprimir filas con formato consistente
    for (int i = 0; i < rows; i++) {
        // Etiqueta de fila alineada
        cout << setw(2) << i + 1 << " |";
        
        // Contenido de la fila
        for (int j = 0; j < cols; j++) {
            cout << " " << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// ========================================
//         IMPRIMIR TESTORES
// ========================================
void PrintTestorsList(const vector<vector<int>>& testors)
{
    if (testors.empty()) {
        cout << "No testores encontrados\n";
        return;
    }

    for (size_t i = 0; i < testors.size(); i++)
    {
        cout << "T" << i + 1 << ": (";
        for (size_t j = 0; j < testors[i].size(); j++)
        {
            cout << "c" << (testors[i][j]);
            if (j + 1 < testors[i].size()) cout << ",";
        }
        cout << ")\n";
    }
}
