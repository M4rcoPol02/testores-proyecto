//0.01 proyecto mates discretas

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "local_include/Matrix.h"
#include "local_include/YYC.h"
#include "local_include/BT.h"
#include "local_include/InputMatrix.h"

int main()
{
<<<<<<< HEAD
    //init random
    srand(time(0));

    BooleanMatrix booleanMatrix(10, 5);
=======
    cout << "¿Desea ingresar manualmente la Matriz de Diferencias? (1=si, 0=no): ";
    int opcion = 0;
    cin >> opcion;

    if(opcion == 1) //INGRESA MATRIZ MANUAL
    {
        vector<vector<int>> M = LeerManualmenteMatrizDiferencia(); //Se ingresa MD manualmente
        BooleanMatrix manualBM(M);

        cout << "MD ingresada:\n";
        PrintMatrix(manualBM.differenceMatrix);

        cout << "MB calculada:\n";
        PrintMatrix(manualBM.basicMatrix);

        cout << "Density: " << manualBM.GetMatrixDensity() << endl;

        // Escoger Algo
            cout << "¿Que algoritmo deasea utilizar? (1=YYC, 0=BT): ";
            int opcion2 = 0;
            cin >> opcion2;

            if (opcion2 == 1){
                RunYYCIncremental(manualBM.basicMatrix);
            } else if (opcion2 == 0){
                    cout <<"Starting BT Algorithm..." << endl;
                    BT bt(manualBM.basicMatrix.at(0).size());
                
                    cout << "Finding Typical Testors..." << endl;
                    vector<vector<int>> typicalTestors = bt.FindTypicalTestors(manualBM.basicMatrix);
                
                    cout << "Typical Testors found:" << endl;
                    
                    PrintMatrix(typicalTestors);
            }
        return 0;
    }


    //MATRIZ ALEATORIA
    srand(time(0));   //init random
    BooleanMatrix booleanMatrix(5, 5);
    
>>>>>>> 1c75b993aa648acf0a4f10db062bb2e361571b3c
    cout << "Difference Matrix: " << endl;
    PrintMatrix(booleanMatrix.differenceMatrix);

    cout << "Basic Matrix: " << endl;
    PrintMatrix(booleanMatrix.basicMatrix);
    cout << "Density: " << booleanMatrix.GetMatrixDensity() << endl;

    
    cout << "Starting YYC Incremental Algorithm..." << endl;
    YYC yyc;

    cout << "Finding Typical Testors..." << endl;

    PrintTestorsList(yyc.findTypicalTestors(booleanMatrix.basicMatrix));

    cout << endl;

    cout <<"Starting BT Algorithm..." << endl;
    BT bt(booleanMatrix.basicMatrix.at(0).size());

    cout << "Finding Typical Testors..." << endl;
    vector<vector<int>> typicalTestors = bt.FindTypicalTestors(booleanMatrix.basicMatrix);

    cout << "Typical Testors found:" << endl;
    
    PrintMatrix(typicalTestors);
    
}
