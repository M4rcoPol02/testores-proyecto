#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include "local_include/Matrix.h"
#include "local_include/BT.h"
#include "local_include/YYC.h"

using namespace std;

// ==== PROTOTIPOS ====
void mostrarMenu();
int pedirEntero(const string& msg, int min, int max);
vector<vector<int>> ingresarMatriz();
vector<vector<int>> generarMatrizRandom();
void usarTestoresComoMatriz(vector<vector<int>>& matrix);

// =========================================================
//                         MAIN
// =========================================================
int main() {
    srand(time(0));

    vector<vector<int>> matrix = generarMatrizRandom();

    while (true) {
        vector<vector<int>> MB = BooleanMatrix::BasicMatrix(matrix);

        mostrarMenu();
        int opcion = pedirEntero("Seleccione una opción: ", 1, 7);

        switch (opcion) {
        case 1:
            cout << "\n--- MATRIZ BÁSICA (MB) ACTUAL ---\n";
            cout << "Tamaño original: " << matrix.size() << "x" << matrix[0].size() << "\n";
            cout << "Tamaño MB: " << MB.size() << "x" << MB[0].size() << "\n";
            PrintMatrix(MB);
            break;

        case 2:
            matrix = ingresarMatriz();
            break;

        case 3:
            matrix = generarMatrizRandom();
            break;

        case 4: {
            cout << "\n--- Testores BT ---\n";
            BT bt(MB[0].size());
            auto testors = bt.findTypicalTestors(MB);
            PrintTestorsList(testors);
            break;
        }

        case 5: {
            cout << "\n--- Testores YYC ---\n";
            YYC yyc(MB[0].size());
            auto testors = yyc.findTypicalTestors(MB);
            PrintTestorsList(testors);
            break;
        }

        case 6:
            usarTestoresComoMatriz(matrix);
            break;

        case 7:
            cout << "\n¡Hasta luego!\n";
            return 0;
        }

        cout << "\nPresione ENTER para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}

// =========================================================
//                     MENÚ PRINCIPAL
// =========================================================
void mostrarMenu() {
    cout << "\n======= CALCULADORA DE TESTORES =======\n";
    cout << "1. Ver matriz básica actual (MB)\n";
    cout << "2. Ingresar matriz manual\n";
    cout << "3. Randomizar matriz\n";
    cout << "4. Calcular testores BT\n";
    cout << "5. Calcular testores YYC\n";
    cout << "6. Usar testores como nueva matriz\n";
    cout << "7. Salir\n";
    cout << "========================================\n";
}

// =========================================================
//                     INPUT SEGURO
// =========================================================
int pedirEntero(const string& msg, int min, int max) {
    int x;

    while (true) {
        cout << msg;
        cin >> x;

        if (!cin.fail() && x >= min && x <= max)
            return x;

        cout << "Valor inválido. Intente nuevamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// =========================================================
//         INGRESO MANUAL (SIN BooleanMatrix)
// =========================================================
vector<vector<int>> ingresarMatriz() {
    int filas = pedirEntero("Filas: ", 1, 100);
    int columnas = pedirEntero("Columnas: ", 1, 15);  // Cambiado de 100 a 15

    vector<vector<int>> m(filas, vector<int>(columnas));

    cout << "\nIngrese valores 0/1:\n";
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            m[i][j] = pedirEntero(
                "Valor [" + to_string(i) + "," + to_string(j) + "]: ", 0, 1
            );

    return m;
}

// =========================================================
//         RANDOM MATRIX (SIN BooleanMatrix)
// =========================================================
vector<vector<int>> generarMatrizRandom() {
    int filas = rand() % 50 + 1;    // 50-99 rows
    int columnas = rand() % 11 + 5;  // Cambiado: 5-15 columns (antes 20-49)

    vector<vector<int>> m(filas, vector<int>(columnas));

    for (auto& row : m)
        for (int& v : row)
            v = rand() % 2;

    cout << "\n--- Nueva matriz random (" << filas << "x" << columnas << ") ---\n";
    return m;
}

// =========================================================
//       USAR TESTORES COMO NUEVA MATRIZ DIFERENCIA
// =========================================================
void usarTestoresComoMatriz(vector<vector<int>>& matrix)
{
    int columnas = matrix[0].size();

    int metodo = pedirEntero("Usar testores de (1=BT, 2=YYC): ", 1, 2);

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