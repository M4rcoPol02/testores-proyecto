#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// Imprime un testor (sumo 1 porque el usuario ve columnas desde 1)
void imprimirTestor(const vector<int>& t) {
    cout << "{";
    for (int i = 0; i < t.size(); i++) {
        cout << t[i] + 1;
        if (i < t.size() - 1) cout << ",";
    }
    cout << "}";
}

// Genera TODAS las combinaciones posibles de columnas
vector<vector<int>> generarCombinaciones(int n) {
    vector<vector<int>> combs;
    combs.push_back({}); //init cnjto vacio combs = [{}]

    for (int col = 0; col < n; col++) { //Para cada columna, duplica las combinaciones existentes agregándola
        int tam = combs.size();         // 1 //
        for (int i = 0; i < tam; i++) { // 0 //Para cada combinación existente
            auto nueva = combs[i];      // Copia combinación existente (copia elemento de combs[actual])
            nueva.push_back(col);       // Agrega el valor del elemento
            combs.push_back(nueva);     // Añade a la lista
        }
    }

    combs.erase(combs.begin()); // se elimina solo la combinacion(cnjto) vacia
    return combs;
}

// Verifica si una combinación "cubre" todas las filas
bool esCobertura(const vector<vector<int>>& matriz, const vector<int>& cols) {
    for (const auto& fila : matriz) {
        bool ok = false;
        for (int c : cols) {
            if (fila[c] == 1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

// Verifica si A es subconjunto de B
bool esSubconjunto(const vector<int>& A, const vector<int>& B) {
    for (int x : A) {
        bool encontrado = false;
        for (int y : B) if (x == y) encontrado = true;
        if (!encontrado) return false;
    }
    return true;
}

// Calcula testores típicos con fuerza bruta
vector<vector<int>> calcularTestores(const vector<vector<int>>& matriz, int nCols) {
    auto todas = generarCombinaciones(nCols); //Genera TODAS las combinaciones posibles de columnas (posibes testores tipicos)
    vector<vector<int>> coberturas;

    // 1) guardar solo las coberturas
    for (auto& comb : todas)
        if (esCobertura(matriz, comb))
            coberturas.push_back(comb);

    // 2) filtrar las MINIMALES (testores típicos)
    vector<vector<int>> tipicos;
    for (auto& c : coberturas) {
        bool minimal = true;
        for (auto& d : coberturas) {
            if (d.size() < c.size() && esSubconjunto(d, c)) {
                minimal = false;
                break;
            }
        }
        if (minimal) tipicos.push_back(c);
    }

    return tipicos;
}

// Algoritmo PRINCPAL  [YYC].mini
void RunYYCIncremental(const vector<vector<int>>& matriz) {
    int filas = matriz.size();         // Total filas de la matriz
    int cols = matriz[0].size();       // Total columnas de la matriz

    cout << "Iteracion | Testores |         Tiempo acumulado (ms)\n";
    cout << "----------------------------------------------------\n";

    auto inicio = chrono::high_resolution_clock::now(); // para capturar el tiempo inicial
    double tiempoAcum = 0;

    for (int f = 1; f <= filas; f++) { // se analiza la matriz incrementalmente fila a fila
        vector<vector<int>> sub(matriz.begin(), matriz.begin() + f); //se toman solo las primeras "f" filas

        auto t0 = chrono::high_resolution_clock::now(); // tiempo t0
        auto testores = calcularTestores(sub, cols); // calcula testores típicos para esta submatriz
        auto t1 = chrono::high_resolution_clock::now(); // tiempo t1

        double ms = chrono::duration<double, milli>(t1 - t0).count(); // [t1-t0] para cada calculo de testor tipico
        tiempoAcum += ms; // acumular tiempo de cada paso

        cout << "    " << f << "     | ";         // Muestra resultados en formato de tabla
        if (testores.empty()) cout << "Ninguno";
        else {
            for (int i = 0; i < testores.size(); i++) {
                imprimirTestor(testores[i]);      // Imprime cada testor
                if (i < testores.size() - 1) cout << ", ";
            }
        }
        cout << " | " << tiempoAcum << "\n";
    }

    auto fin = chrono::high_resolution_clock::now(); // tiempo final
    double total = chrono::duration<double, milli>(fin - inicio).count();
    cout << "\nTiempo total: " << total << " ms\n";
}