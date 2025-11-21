#pragma once

#include <vector>
#include <string>
#include "YYC.h"
#include "BT.h"

struct TimingAnalysis {
    int N;
    std::string matrix_formula;
    int rows;
    int cols;
    int predicted_testors;
    double yyc_time_any_order;
    double yyc_time_sorted_ones;
    double bt_time_any_order;
    double bt_time_sorted_ones;
};

class MatrixOperators {
public:
    // Operadores
    static std::vector<std::vector<int>> phi_operator(const std::vector<std::vector<int>>&, int N);
    static std::vector<std::vector<int>> theta_operator(const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&);
    static std::vector<std::vector<int>> gamma_operator(const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&);
    static std::vector<std::vector<int>> gamma_power(const std::vector<std::vector<int>>&, int N);

    // Predicciones
    static int predict_phi_theta_testors_count(const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&, int N);
    static int predict_gamma_theta_testors_count(const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&, int N);

    // Análisis de tiempo
    static std::vector<TimingAnalysis> analyze_timing_phi_series(
        const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&,
        const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&,
        int max_N);

    static std::vector<TimingAnalysis> analyze_timing_gamma_series(
        const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&,
        const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&,
        int max_N);

    // Herramientas auxiliares
    static int count_rows(const std::vector<std::vector<int>>&);
    static int count_cols(const std::vector<std::vector<int>>&);
    static int count_ones(const std::vector<int>&);
    static std::vector<std::vector<int>> sort_rows_by_ones(const std::vector<std::vector<int>>&);

    // Formato de salida
    static std::string format_timing_table(const std::vector<TimingAnalysis>&);
};