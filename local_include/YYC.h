#ifndef YYC_H
#define YYC_H

#include <vector>

class YYC {
public:
bool shouldDisplayTime{true};
    // Constructor por defecto
    YYC(int col);
    long long getVisitedNodes() const { return visitedNodes; }  
    void resetVisitedNodesIfExists();
    long long executionTimeMicroseconds = 0;
    double getExecutionTime() const { return executionTimeMicroseconds; }

    // Retorna la lista de testores típicos (cada testor representado como vector de índices de columnas)
    // La matriz es una matriz booleana (0/1) organizada por filas: matrix[row][col]
    std::vector<std::vector<int>> findTypicalTestors(const std::vector<std::vector<int>>& matrix);

private:
    
    long long visitedNodes = 0;   // NEW
    

    int currentAmountOfTestors{};
    // Comprueba si en la submatriz formada por las columnas 'testor' (ya ordenadas)
    // y las filas hasta rowsUpTo (exclusive) existe un conjunto compatible
    // al añadir la columna newCol. Implementa Algorithm 2 del paper.
    bool findCompatibleSet(const std::vector<int>& testor, int newCol,
                           const std::vector<std::vector<int>>& matrix,
                           int rowsUpTo);

    // Extrae submatriz formada por las columnas cols y filas 0..rowsUpTo-1
    std::vector<std::vector<int>> getSubmatrix(const std::vector<std::vector<int>>& matrix,
                                               const std::vector<int>& cols,
                                               int rowsUpTo);

    // Utilidad: comprobar si 'a' es subconjunto propio de 'b' (ambos ordenados)
    bool isSubsetStrict(const std::vector<int>& a, const std::vector<int>& b);
};

#endif // YYC_H