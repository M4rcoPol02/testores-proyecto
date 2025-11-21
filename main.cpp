#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include "local_include/Matrix.h"
#include "local_include/BT.h"
#include "local_include/YYC.h"
#include "local_include/matrix_operators.h"

using namespace std;

void showMenu();
int getInteger(const string& msg, int min, int max);
vector<vector<int>> inputMatrix();
vector<vector<int>> generateRandomMatrix();
void generateMatrixBFromTestors();
void createSection52Tables();
double calculateDensity(const vector<vector<int>>& matrix);
vector<vector<int>> getPredefinedMatrix();
void ejercicio4_YYC(vector<vector<int>>& matrix);
void usarTestoresComoMatriz(vector<vector<int>>& matrix);
vector<vector<int>> convertTestorsFormat(const vector<vector<int>>& testors, int numColumns);

vector<vector<int>> matrixA;
vector<vector<int>> matrixB;

int main() {
    srand(time(0));
    cout << "=== SISTEMA DE GENERACION DE MATRICES PARA TESTORES ===\n\n";

    while (true) {
        showMenu();
        int option = getInteger("Seleccione una opcion: ", 1, 11);

        switch (option) {
        case 1:
            cout << "\n--- CONFIGURAR MATRIZ A (manual) ---\n";
            matrixA = inputMatrix();
            cout << "Matriz A configurada (" << matrixA.size() << "x" << matrixA[0].size() << ")\n";
            cout << "Densidad: " << calculateDensity(matrixA) * 100 << "%\n";
            break;

        case 2:
            cout << "\n--- CONFIGURAR MATRIZ A (aleatoria) ---\n";
            matrixA = generateRandomMatrix();
            cout << "Matriz A configurada (" << matrixA.size() << "x" << matrixA[0].size() << ")\n";
            cout << "Densidad: " << calculateDensity(matrixA) * 100 << "%\n";
            break;

        case 3:
            cout << "\n--- CONFIGURAR MATRIZ A (predefinida) ---\n";
            matrixA = getPredefinedMatrix();
            cout << "Matriz A predefinida configurada (" << matrixA.size() << "x" << matrixA[0].size() << ")\n";
            cout << "Densidad: " << calculateDensity(matrixA) * 100 << "%\n";
            cout << "Matriz:\n";
            PrintMatrix(matrixA);
            break;

        case 4:
            if (matrixA.empty()) {
                cout << "\nERROR: Primero configure la Matriz A\n";
            } else {
                cout << "\n--- MATRIZ BASICA DE A (MB) ---\n";
                vector<vector<int>> MB = BooleanMatrix::BasicMatrix(matrixA);
                cout << "Tamano original: " << matrixA.size() << "x" << matrixA[0].size() << "\n";
                cout << "Tamano MB: " << MB.size() << "x" << MB[0].size() << "\n";
                cout << "Densidad original: " << calculateDensity(matrixA) * 100 << "%\n";
                cout << "Densidad MB: " << calculateDensity(MB) * 100 << "%\n";
                PrintMatrix(MB);
            }
            break;

        case 5:
            if (matrixB.empty()) {
                cout << "\nERROR: Primero configure la Matriz B\n";
            } else {
                cout << "\n--- MATRIZ BASICA DE B (MB) ---\n";
                vector<vector<int>> MB_B = BooleanMatrix::BasicMatrix(matrixB);
                cout << "Tamano original: " << matrixB.size() << "x" << matrixB[0].size() << "\n";
                cout << "Tamano MB: " << MB_B.size() << "x" << MB_B[0].size() << "\n";
                cout << "Densidad original: " << calculateDensity(matrixB) * 100 << "%\n";
                cout << "Densidad MB: " << calculateDensity(MB_B) * 100 << "%\n";
                PrintMatrix(MB_B);
            }
            break;

        case 6: {
            if (matrixA.empty()) {
                cout << "\nERROR: Primero configure la Matriz A\n";
            } else {
                cout << "\n--- Testores BT ---\n";
                auto MB = BooleanMatrix::BasicMatrix(matrixA);
                BT bt(MB[0].size());
                auto testors = bt.findTypicalTestors(MB);
                PrintTestorsList(testors);
            }
            break;
        }

        case 7: {
            if (matrixA.empty()) {
                cout << "\nERROR: Primero configure la Matriz A\n";
            } else {
                cout << "\n--- Testores YYC ---\n";
                auto MB = BooleanMatrix::BasicMatrix(matrixA);
                YYC yyc(MB[0].size());
                auto testors = yyc.findTypicalTestors(MB);
                PrintTestorsList(testors);
            }
            break;
        }

        case 8:
            if (matrixA.empty()) {
                cout << "\nERROR: Primero configure la Matriz A\n";
            } else {
                generateMatrixBFromTestors();
            }
            break;

        case 9:
            if (matrixA.empty() || matrixB.empty()) {
                cout << "\nERROR: Necesita ambas matrices A y B configuradas\n";
            } else {
                createSection52Tables();
            }
            break;

        case 10:
            if (matrixA.empty()) {
                cout << "\nERROR: Primero configure la Matriz A\n";
            } else {
                cout << "\n--- Construir B y testores típicos con YYC ---\n";
                ejercicio4_YYC(matrixA);
            }
            break;

        case 11:
            cout << "\n¡Hasta luego!\n";
            return 0;
        }

        cout << "\nPresione ENTER para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}

void showMenu() {
    cout << "\n======= SISTEMA DE MATRICES PARA TESTORES =======\n";
    cout << "1. Configurar Matriz A (manual)\n";
    cout << "2. Configurar Matriz A (aleatoria)\n";
    cout << "3. Configurar Matriz A (predefinida)\n";
    cout << "4. Ver Matriz Basica de A (MB)\n";
    cout << "5. Ver Matriz Basica de B (MB)\n";
    cout << "6. Calcular testores BT de A\n";
    cout << "7. Calcular testores YYC de A\n";
    cout << "8. Generar Matriz B desde testores de A\n";
    cout << "9. CREAR TABLAS SECCION 5.2 (Timing)\n";
    cout << "10. Construir B y testores típicos con YYC\n";
    cout << "11. Salir\n";
    cout << "=================================================\n";
}

int getInteger(const string& msg, int min, int max) {
    int x;
    while (true) {
        cout << msg;
        cin >> x;
        if (!cin.fail() && x >= min && x <= max) return x;
        cout << "Valor invalido. Intente nuevamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double calculateDensity(const vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0.0;
    int totalElements = matrix.size() * matrix[0].size();
    int ones = 0;
    for (const auto& row : matrix) {
        for (int value : row) {
            if (value == 1) ones++;
        }
    }
    return static_cast<double>(ones) / totalElements;
}

vector<vector<int>> inputMatrix() {
    int rows = getInteger("Filas (1-100): ", 1, 100);
    int columns = getInteger("Columnas (1-10): ", 1, 10);
    vector<vector<int>> m(rows, vector<int>(columns));
    cout << "\nIngrese valores 0/1:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            m[i][j] = getInteger("Valor [" + to_string(i) + "," + to_string(j) + "]: ", 0, 1);
        }
    }
    return m;
}

vector<vector<int>> generateRandomMatrix() {
    int rows = getInteger("Filas (1-100): ", 1, 100);
    int columns = getInteger("Columnas (1-10): ", 1, 10);
    char highDensity;
    cout << "¿Densidad mayor a 0.5? (s/n): ";
    cin >> highDensity;
    double targetDensity = (highDensity == 's' || highDensity == 'S') ? 
                           (0.5 + (rand() % 50) / 100.0) : 
                           ((rand() % 50) / 100.0);
    vector<vector<int>> m(rows, vector<int>(columns));
    for (auto& row : m) {
        for (int& value : row) {
            value = ((rand() % 100) / 100.0 < targetDensity) ? 1 : 0;
        }
    }
    cout << "\n--- Nueva matriz random (" << rows << "x" << columns << ") ---\n";
    return m;
}

vector<vector<int>> getPredefinedMatrix() {
    // Predefined matrix: 6x7 matrix as specified
    return {
        {1, 0, 1, 1, 1, 0, 1},  // Row 1
        {1, 1, 0, 1, 0, 1, 1},  // Row 2
        {0, 1, 1, 0, 1, 1, 1},  // Row 3
        {1, 1, 0, 1, 0, 1, 1},  // Row 4
        {1, 0, 1, 1, 1, 0, 1},  // Row 5
        {1, 1, 1, 1, 1, 1, 0}   // Row 6
    };
}

void generateMatrixBFromTestors() {
    cout << "\n--- Generando Matriz B desde testores BT de A ---\n";
    
    auto MB = BooleanMatrix::BasicMatrix(matrixA);
    BT bt(matrixA[0].size());
    auto testors = bt.findTypicalTestors(MB);

    if (testors.empty()) {
        cout << "\nNo existen testores. No se puede generar Matriz B.\n";
        return;
    }

    // Create matrix B manually from testors
    matrixB.clear();
    int columns = matrixA[0].size();
    
    for (const auto& testor : testors) {
        vector<int> row(columns, 0);
        for (int col : testor) {
            if (col > 0 && col <= columns) {
                row[col - 1] = 1;
            }
        }
        matrixB.push_back(row);
    }

    cout << "\nMatriz B generada desde testores BT de A (" << matrixB.size() << "x" << matrixB[0].size() << ")\n";
    cout << "Densidad: " << calculateDensity(matrixB) * 100 << "%\n";
}

vector<vector<int>> convertTestorsFormat(const vector<vector<int>>& testors, int numColumns) {
    vector<vector<int>> result;
    for (const auto& testor : testors) {
        vector<int> binary_testor(numColumns, 0);
        for (int col : testor) {
            if (col > 0 && col <= numColumns) {
                binary_testor[col - 1] = 1;
            }
        }
        result.push_back(binary_testor);
    }
    return result;
}

void createSection52Tables() {
    cout << "\n=== CREANDO TABLAS SECCION 5.2 ===\n";
    
    // Get testors for both matrices
    auto MB_A = BooleanMatrix::BasicMatrix(matrixA);
    auto MB_B = BooleanMatrix::BasicMatrix(matrixB);
    
    // Create YYC and BT instances to pass to timing functions
    YYC yyc_instance(MB_A[0].size());
    BT bt_instance(MB_A[0].size());
    
    BT bt_A(MB_A[0].size());
    BT bt_B(MB_B[0].size());
    
    auto testorsA_raw = bt_A.findTypicalTestors(MB_A);
    auto testorsB_raw = bt_B.findTypicalTestors(MB_B);
    
    cout << "Testores de A: " << testorsA_raw.size() << ", Testores de B: " << testorsB_raw.size() << endl;
    
    // Convert testors to the format expected by matrix_operators
    vector<vector<int>> testorsA = convertTestorsFormat(testorsA_raw, matrixA[0].size());
    vector<vector<int>> testorsB = convertTestorsFormat(testorsB_raw, matrixB[0].size());
    
    cout << "\n--- TABLA 5.2.1: OPERADOR PHI (φ^N(θ(A,B))) ---\n";
    auto phiResults = MatrixOperators::analyze_timing_phi_series(matrixA, matrixB, testorsA, testorsB, 5, yyc_instance, bt_instance);
    cout << MatrixOperators::format_timing_table(phiResults) << endl;
    
    cout << "\n--- TABLA 5.2.2: OPERADOR GAMMA (γ^N(θ(A,B))) ---\n";
    auto gammaResults = MatrixOperators::analyze_timing_gamma_series(matrixA, matrixB, testorsA, testorsB, 4, yyc_instance, bt_instance);
    cout << MatrixOperators::format_timing_table(gammaResults) << endl;
    
    cout << "=== TABLAS SECCION 5.2 COMPLETADAS ===\n";
}

void ejercicio4_YYC(vector<vector<int>>& matrix)
{
    if (matrix.empty()) {
        cout << "\nLa matriz actual está vacía. No se puede hacer el Ejercicio 4.1.\n";
        return;
    }

    int columnas = static_cast<int>(matrix[0].size());
    cout << "\n===== Construcción de B  =====\n";

    // 1) Testores típicos de A con YYC
    YYC yyc(columnas);
    auto testoresA = yyc.findTypicalTestors(matrix);

    cout << "\nTestores típicos de la matriz A:\n";
    PrintTestorsList(testoresA);

    if (testoresA.empty()) {
        cout << "\nA no tiene testores típicos, no se puede construir la matriz B.\n";
        return;
    }

    // 2) Construcción de B desde los testores típicos
    vector<vector<int>> B = BooleanMatrix::TestorsToMatrix(testoresA, columnas);

    cout << "\nMatriz B construida a partir de los testores típicos de A:\n";
    PrintMatrix(B);

    BT bt(columnas);
    auto testoresB = bt.findTypicalTestors(B);

    cout << "\nTestores típicos de la matriz B (BT):\n";
    PrintTestorsList(testoresB);

    // 3) (Opcional) actualizar matrix si deseas continuar con B
    matrix = B;
    cout << "\nMatriz A actualizada con la matriz B construida.\n";
}

void usarTestoresComoMatriz(vector<vector<int>>& matrix)
{
    int columnas = matrix[0].size();

    int metodo = getInteger("Usar testores de (1=BT, 2=YYC): ", 1, 2);

    vector<vector<int>> testors;
    auto MB = BooleanMatrix::BasicMatrix(matrix);

    if (metodo == 1) {
        BT bt(columnas);
        testors = bt.findTypicalTestors(MB);
    } else {
        YYC yyc(columnas);
        testors = yyc.findTypicalTestors(MB);
    }

    if (testors.empty()) {
        cout << "\nNo existen testores. No se puede convertir.\n";
        return;
    }

    matrix = BooleanMatrix::TestorsToMatrix(testors, columnas);

    cout << "\nNueva matriz creada desde testores (se imprimirá su MB con opción 1)\n";
}