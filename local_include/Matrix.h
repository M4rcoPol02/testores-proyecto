#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class BooleanMatrix
{
private:
    int rows = 0;
    int columns = 0;

    std::vector<std::vector<int>> differenceMatrix;
    std::vector<std::vector<int>> basicMatrix;

    float density = 0.0f;

public:
    // Constructores
    BooleanMatrix() = default;
    BooleanMatrix(const std::vector<std::vector<int>>& matrix);
    BooleanMatrix(int rows, int columns);

    // Funciones principales
    void BasicMatrix();                                // versión de instancia
    std::vector<std::vector<int>> GetBasicMatrix() const { return basicMatrix; }
    std::vector<std::vector<int>> GetMatrix() const { return differenceMatrix; }

    float GetMatrixDensity();

    // ========= NUEVO (static) =========
    // Función directa: recibe una matriz y devuelve la matriz básica
    static std::vector<std::vector<int>> BasicMatrix(const std::vector<std::vector<int>>& matrix);

    // Utilidades
    static std::vector<std::vector<int>> TestorsToMatrix(const std::vector<std::vector<int>>& testors, int numColumns);

private:
    void CalcMatrixDensity();
    static bool IsBSubRowOfA(const std::vector<int>& rowA, const std::vector<int>& rowB);

    static std::vector<std::vector<int>> GenerateNewDifferenceMatrix(int rows, int columns);
};

void PrintMatrix(const std::vector<std::vector<int>>& matrix);
void PrintTestorsList(const std::vector<std::vector<int>>& testors);

#endif
