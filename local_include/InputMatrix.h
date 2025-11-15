#ifndef INPUT_MATRIX_H
#define INPUT_MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> LeerManualmenteMatrizDiferencia()
{
    int filass, colss;
    cout << "Ingrese cantidad de filas de la MD: ";
    cin >> filass;
    cout << "Ingrese cantidad de columnas de la MD: ";
    cin >> colss;

    vector<vector<int>> M(filass, vector<int>(colss));

    cout << "Ingrese la matriz de diferencias (solo 0 y 1):\n";

    for(int i=0; i<filass; i++)
    {
        for(int j=0; j<colss; j++)
        {
            cin >> M[i][j];
        }
    }

    return M;
}

#endif
