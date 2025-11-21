#include "YYC.h"
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <set>
#include "ExecutionTime.h"
#include <iostream>
// ------------------------------
// findTypicalTestors
// Implementa Algorithm 1 (YYC) tal como se describe en el paper.
// ------------------------------

YYC::YYC(int algo)
{

}
std::vector<std::vector<int>> YYC::findTypicalTestors(const std::vector<std::vector<int>>& matrix) {
std::vector<std::vector<int>> typicalTestors;

     executionTimeMicroseconds = 0; 
    auto globalStart = std::chrono::steady_clock::now();
    currentAmountOfTestors = 0;  // Reset counter
    
    // Vector para almacenar tiempos entre testores
    std::vector<long long> timesBetweenTestors;
    auto lastTestorTime = globalStart;

    if (matrix.empty()) {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now() - globalStart);
        std::cout << "Tiempo total de ejecución YYC: " << duration.count() << " microseconds" << std::endl;
        return typicalTestors;
    }
    size_t totalRows = matrix.size();
    size_t totalCols = matrix[0].size();

    // Validación simple: todas las filas deben tener totalCols columnas
    for (const auto& r : matrix) {
        if (r.size() != totalCols) return typicalTestors; // matriz inconsistente -> devuelve vacío
    }

    // Inicializa con las columnas que tienen '1' en la primera fila (r1)
    for (size_t col = 0; col < totalCols; ++col) {
        if (matrix[0][col] == 1) {
            visitedNodes++;
            typicalTestors.push_back(std::vector<int>{static_cast<int>(col)});


            auto currentTime = std::chrono::steady_clock::now();
            auto timeSinceLast = std::chrono::duration_cast<std::chrono::microseconds>(
                currentTime - lastTestorTime).count();
            timesBetweenTestors.push_back(timeSinceLast);
            lastTestorTime = currentTime;
            currentAmountOfTestors++;
        }
    }

    // Si no hay columnas con 1 en la primera fila, typicalTestors queda vacío.
    // Procesar filas restantes de forma incremental
    for (size_t row = 1; row < totalRows; ++row) {
        std::vector<std::vector<int>> newTypicalTestors;

        for (const auto& testor : typicalTestors) {
            // ¿existe columna del testor que tenga 1 en la fila actual?
            bool stillWorks = false;
            for (int c : testor) {
                if (matrix[row][c] == 1) { stillWorks = true; break; }
            }

            if (stillWorks) {
                // Conserva el testor tal cual
                newTypicalTestors.push_back(testor);
            } else {
                // Necesitamos probar extensiones con cada columna que tenga 1 en la fila actual
                for (size_t newCol = 0; newCol < totalCols; ++newCol) {
                    if (matrix[row][newCol] == 1) {
                        // evita duplicar si newCol ya está presente
                        if (std::find(testor.begin(), testor.end(), static_cast<int>(newCol)) != testor.end()) continue;
                        std::vector<int> extended = testor;
                        extended.push_back(static_cast<int>(newCol));
                        std::sort(extended.begin(), extended.end());

                        visitedNodes++;
                        // findCompatibleSet debe considerar filas hasta row (inclusive) -> rowsUpTo = row+1
                        if (findCompatibleSet(extended, static_cast<int>(newCol), matrix, static_cast<int>(row + 1))) {
                            newTypicalTestors.push_back(extended);

                        }
                    }
                }
            }
        }

        // normalizar: ordenar columnas en cada testor, eliminar duplicados
        for (auto& t : newTypicalTestors) {
            std::sort(t.begin(), t.end());
        }
        std::sort(newTypicalTestors.begin(), newTypicalTestors.end());
        newTypicalTestors.erase(std::unique(newTypicalTestors.begin(), newTypicalTestors.end()), newTypicalTestors.end());

        // Filtrado de mínima minimalidad: eliminar superset si existe un subconjunto
        // Construimos una nueva lista manteniendo solo los mínimos
        std::vector<std::vector<int>> filtered;
        // Ordenamos por tamaño ascendente para que los subconjuntos pequeños se inserten primero
        std::sort(newTypicalTestors.begin(), newTypicalTestors.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      if (a.size() != b.size()) return a.size() < b.size();
                      return a < b;
                  });

        for (const auto& cand : newTypicalTestors) {
            bool hasSubset = false;
            for (const auto& kept : filtered) {
                if (kept.size() >= cand.size()) break; // kept más grande o igual -> no puede ser subconjunto propio
                if (isSubsetStrict(kept, cand)) { hasSubset = true; break; }
            }
            if (!hasSubset){
                
                filtered.push_back(cand);
                if (row == totalRows - 1) { // Solo en la última iteración
    auto currentTime = std::chrono::steady_clock::now();
    auto timeSinceLast = std::chrono::duration_cast<std::chrono::microseconds>(
        currentTime - lastTestorTime).count();
    timesBetweenTestors.push_back(timeSinceLast);
    lastTestorTime = currentTime;
    currentAmountOfTestors++;
    
    if(shouldDisplayTime)
    {

        std::cout << "  Tiempo elapsado desde anterior testor: " << timeSinceLast << " microseconds" << std::endl;
    }
}


            } 
        }
        shouldDisplayTime = true;
        // sustituir typicalTestors por los filtrados
        typicalTestors.swap(filtered);
        
    }

    auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::steady_clock::now() - globalStart);

    executionTimeMicroseconds = totalDuration.count();

    if(shouldDisplayTime)
    {
        std::cout << "Tiempo total de ejecución YYC: " << totalDuration.count() << " microseconds" << std::endl;
    }

    // MOSTRAR TIEMPOS ACUMULADOS ENTRE TESTORES (después del tiempo total)
    if (!timesBetweenTestors.empty()) {

        long long accumulatedTime = 0;
        for (size_t i = 0; i < timesBetweenTestors.size(); i++) {
            accumulatedTime += timesBetweenTestors[i];
           
        }
    }

    for (auto& testor : typicalTestors) {
    for (int& col : testor) {
        col = col + 1;  // Convertir de índice 0-based a 1-based
    }
}
    // Final: typicalTestors contiene los TTs encontrados
    return typicalTestors;
}

// ------------------------------
// findCompatibleSet  (Algorithm 2 del paper)
// Recibe "testor" (vector de columnas ya ordenado) y columna nueva newCol.
// rowsUpTo: filas que deben considerarse (normalmente fila actual + 1)
// ------------------------------
bool YYC::findCompatibleSet(const std::vector<int>& testor, int /*newCol*/,
                            const std::vector<std::vector<int>>& matrix,
                            int rowsUpTo) {
    // Guardamos las columnas candidatas: testor (ya incluye newCol)
    std::vector<int> cols = testor;

    if (cols.empty()) return false;
    if (rowsUpTo <= 0) return false;
    if (rowsUpTo > static_cast<int>(matrix.size())) rowsUpTo = static_cast<int>(matrix.size());

    // Construir submatriz RefSM con filas 0..rowsUpTo-1 y columnas cols
    auto ref = getSubmatrix(matrix, cols, rowsUpTo);

    // Condition1: número de filas con suma == 1 >= |cols|
    int countSingleOneRows = 0;
    for (const auto& r : ref) {
        int s = std::accumulate(r.begin(), r.end(), 0);
        if (s == 1) ++countSingleOneRows;
    }
    bool condition1 = (countSingleOneRows >= static_cast<int>(cols.size()));
    if (!condition1) return false;

    // Redefinir RefSM -> filas con suma == 1
    std::vector<std::vector<int>> singleRows;
    for (const auto& r : ref) {
        int s = std::accumulate(r.begin(), r.end(), 0);
        if (s == 1) singleRows.push_back(r);
    }

    // Condition2: para cada columna candidata, existe al menos una fila en singleRows
    // que tenga 1 en esa columna. (i.e., cada columna tiene su "fila típica" única)
    // Mapear índice de columna en 'cols' a su posición en la submatriz (0..cols.size()-1)
    size_t m = cols.size();
    std::vector<int> coverage(m, 0);
    for (const auto& r : singleRows) {
        for (size_t j = 0; j < m; ++j) {
            if (r[j] == 1) coverage[j] = 1;
        }
    }
    for (size_t j = 0; j < m; ++j) {
        if (coverage[j] == 0) return false; // alguna columna no tiene fila única
    }

    return true; // ambas condiciones satisfechas => compatible set existe
}

// ------------------------------
// getSubmatrix: filas [0..rowsUpTo-1], columnas 'cols' (los índices de columnas)
// ------------------------------
std::vector<std::vector<int>> YYC::getSubmatrix(const std::vector<std::vector<int>>& matrix,
                                                const std::vector<int>& cols,
                                                int rowsUpTo) {
    std::vector<std::vector<int>> sub;
    if (cols.empty() || rowsUpTo <= 0) return sub;
    int actualRows = std::min(rowsUpTo, static_cast<int>(matrix.size()));
    for (int i = 0; i < actualRows; ++i) {
        std::vector<int> row;
        row.reserve(cols.size());
        for (int c : cols) {
            if (c < 0 || c >= static_cast<int>(matrix[i].size())) {
                // índice inválido: empujar 0 para mantener dimensiones (pero idealmente evitar)
                row.push_back(0);
            } else {
                row.push_back(matrix[i][c]);
            }
        }
        sub.push_back(std::move(row));
    }
    return sub;
}

// ------------------------------
// isSubsetStrict: true si 'a' es subconjunto propio de 'b' (ambos ordenados, sin repetidos)
// ------------------------------
bool YYC::isSubsetStrict(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() >= b.size()) return false;
    size_t ia = 0, ib = 0;
    while (ia < a.size() && ib < b.size()) {
        if (a[ia] == b[ib]) { ++ia; ++ib; }
        else if (a[ia] > b[ib]) { ++ib; }
        else return false; // elemento de a no en b
    }
    return (ia == a.size());
}

void YYC::resetVisitedNodesIfExists()
{
    visitedNodes = 0;
}