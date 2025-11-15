//prototipo del archivo YYC.cpp
#ifndef YYC_H
#define YYC_H

#include<iostream>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include "Matrix.h"


using namespace std; 


// - imprime en stdout los testores típicos para cada prefijo de filas y tiempos acumulados.
void RunYYCIncremental(const std::vector<std::vector<int>>& matrizCompleta); // o envez pon matrix

// Helper: imprime un conjunto de columnas (testor) en formato {c1,c2,...}
void PrintTestor(const std::vector<int>& testor);


#endif