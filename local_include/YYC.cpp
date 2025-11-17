#include "YYC.h"
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <set>
#include "ExecutionTime.h"

using namespace std;

vector<vector<int>> YYC::findTypicalTestors(const vector<vector<int>>& matrix) {

    ExecutionTime t{"Tiempo de ejecucion YYC"};

    vector<vector<int>> typicalTestors;

    if (matrix.empty()) return typicalTestors;

    int totalRows = matrix.size();
    int totalCols = matrix[0].size();

    //en cada columna de la primera fila de la matriz
    for (int col = 0; col < totalCols; col++) 
    {
        //si alguna columna tiene 1, agregarla como testor típico inicial
        if (matrix[0][col] == 1) 
        {
            // ❌ ERROR ORIGINAL: vector<int>(col)
            // ✔ FIX:
            typicalTestors.push_back({col});
        }
    }

    // Si no hay columnas con 1 en la primera fila, typicalTestors queda vacío.
    // Procesar filas restantes de forma incremental

    for (int row{1}; row < totalRows; row++) 
    {
        vector<vector<int>> newTypicalTestors;

        for (const vector<int>& testor : typicalTestors) 
        {
            // ¿existe columna del testor que tenga 1 en la fila actual?
            bool stillWorks = false;

            for (int column : testor) 
            {
                if (matrix[row][column] == 1) 
                {
                     stillWorks = true; 
                     break; 
                }
            }

            if (stillWorks) {
                newTypicalTestors.push_back(testor);
            } 
            else 
            {
                for (int newCol = 0; newCol < totalCols; newCol++) 
                {
                    if (matrix[row][newCol] == 1) 
                    {
                        if (find(testor.begin(), testor.end(), newCol) != testor.end()) continue;

                        vector<int> extended = testor;
                        extended.push_back(newCol);
                        sort(extended.begin(), extended.end());

                        if (findCompatibleSet(extended, newCol, matrix, row + 1)) {
                            newTypicalTestors.push_back(extended);
                        }
                    }
                }
            }
        }

        for (vector<int>& t : newTypicalTestors) 
            sort(t.begin(), t.end());

        sort(newTypicalTestors.begin(), newTypicalTestors.end());
        newTypicalTestors.erase(unique(newTypicalTestors.begin(), newTypicalTestors.end()),
                                newTypicalTestors.end());

        vector<vector<int>> filtered;

        // ❌ ERROR: método no estático
        // ✔ FIX: ahora es static
        sort(newTypicalTestors.begin(), newTypicalTestors.end(), YYC::compareBySizeThenLex);

        for (const vector<int>& candidate : newTypicalTestors) 
        {
            bool hasSubset = false;
            for (const vector<int>& kept : filtered) {
                if (kept.size() >= candidate.size()) break;
                if (isSubsetStrict(kept, candidate)) { 
                    hasSubset = true; 
                    break; 
                }
            }
            if (!hasSubset) filtered.push_back(candidate);
        }

        typicalTestors.swap(filtered);
    }
    return typicalTestors;
}

// === FIX: debe ser static ===
bool YYC::compareBySizeThenLex(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) 
        return a.size() < b.size();
    return a < b;
}

bool YYC::findCompatibleSet(const vector<int>& testor, int newCol, 
                           const vector<vector<int>>& matrix,int rowsUpTo) 
{
    vector<int> cols = testor;

    if (cols.empty()) return false;
    if (rowsUpTo > matrix.size()) rowsUpTo = matrix.size();

    vector<vector<int>> ref = getSubmatrix(matrix, cols, rowsUpTo);

    int countSingleOneRows = 0;
    for (const vector<int>& r : ref) 
    {
        int s = accumulate(r.begin(), r.end(), 0);
        if (s == 1) countSingleOneRows++;
    }
    if (countSingleOneRows < cols.size()) return false;

    vector<vector<int>> singleRows;
    for (const vector<int>& r : ref) {
        int s = accumulate(r.begin(), r.end(), 0);
        if (s == 1) singleRows.push_back(r);
    }

    int m = cols.size();
    vector<int> coverage(m, 0);
    for (const vector<int>& r : singleRows) {
        for (int i = 0; i < m; i++) {
            if (r[i] == 1) coverage[i] = 1;
        }
    }

    for (int i = 0; i < m; i++) 
        if (coverage[i] == 0) return false;

    return true; 
}

vector<vector<int>> YYC::getSubmatrix(const vector<vector<int>>& matrix, 
                                      const vector<int>& cols, int rowsUpTo) 
{
    vector<vector<int>> sub;
    if (cols.empty() || rowsUpTo <= 0) return sub;

    int actualRows = min(rowsUpTo, static_cast<int>(matrix.size()));

    for (int i = 0; i < actualRows; i++) {
        vector<int> row;
        for (int c : cols) {
            if (c < 0 || c >= matrix[i].size()) row.push_back(0);
            else row.push_back(matrix[i][c]);
        }
        sub.push_back(row);
    }
    return sub;
}

bool YYC::isSubsetStrict(const vector<int>& a, const vector<int>& b) 
{
    if (a.size() >= b.size()) return false;

    int indexA=0, indexB=0;
    while (indexA < a.size() && indexB < b.size()) 
    {
        if (a[indexA] == b[indexB]) { indexA++; indexB++; }
        else if (a[indexA] > b[indexB]) { indexB++; }
        else return false;
    }
    return (indexA == a.size());
}
