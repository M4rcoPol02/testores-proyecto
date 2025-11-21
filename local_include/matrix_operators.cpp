#include "matrix_operators.h"
#include "YYC.h"
#include "BT.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include<iostream>

std::vector<std::vector<int>> MatrixOperators::phi_operator(const std::vector<std::vector<int>>& A, int N) {
    if (N < 1) throw std::invalid_argument("N debe ser >= 1");
    if (A.empty()) return A;

    std::vector<std::vector<int>> result = A;
    for (int i = 1; i < N; ++i) {
        for (size_t row = 0; row < result.size(); ++row) {
            result[row].insert(result[row].end(), A[row].begin(), A[row].end());
        }
    }
    return result;
}

std::vector<std::vector<int>> MatrixOperators::theta_operator(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    if (A.empty() || B.empty()) throw std::invalid_argument("Matrices vacías");
    std::vector<std::vector<int>> result;
    for (const auto& rowA : A) {
        for (const auto& rowB : B) {
            std::vector<int> new_row;
            new_row.insert(new_row.end(), rowA.begin(), rowA.end());
            new_row.insert(new_row.end(), rowB.begin(), rowB.end());
            result.push_back(new_row);
        }
    }
    return result;
}

std::vector<std::vector<int>> MatrixOperators::gamma_operator(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    if (A.empty() || B.empty()) throw std::invalid_argument("Matrices vacías");
    int colsA = count_cols(A);
    int colsB = count_cols(B);
    std::vector<std::vector<int>> result;
    for (const auto& rowA : A) {
        std::vector<int> new_row = rowA;
        new_row.insert(new_row.end(), colsB, 0);
        result.push_back(new_row);
    }
    for (const auto& rowB : B) {
        std::vector<int> new_row(colsA, 0);
        new_row.insert(new_row.end(), rowB.begin(), rowB.end());
        result.push_back(new_row);
    }
    return result;
}

std::vector<std::vector<int>> MatrixOperators::gamma_power(const std::vector<std::vector<int>>& A, int N) {
    if (N < 1) throw std::invalid_argument("N debe ser >= 1");
    std::vector<std::vector<int>> result = A;
    for (int i = 1; i < N; ++i) {
        result = gamma_operator(result, A);
    }
    return result;
}

int MatrixOperators::predict_phi_theta_testors_count(const std::vector<std::vector<int>>& typical_testors_A, const std::vector<std::vector<int>>& typical_testors_B, int N) {
    int total = 0;
    for (const auto& testor : typical_testors_A) total += static_cast<int>(std::pow(N, testor.size()));
    for (const auto& testor : typical_testors_B) total += static_cast<int>(std::pow(N, testor.size()));
    return total;
}

int MatrixOperators::predict_gamma_theta_testors_count(const std::vector<std::vector<int>>& typical_testors_A, const std::vector<std::vector<int>>& typical_testors_B, int N) {
    int base_testors = typical_testors_A.size() + typical_testors_B.size();
    return static_cast<int>(std::pow(base_testors, N));
}

std::vector<TimingAnalysis> MatrixOperators::analyze_timing_phi_series(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, const std::vector<std::vector<int>>& typical_testors_A, const std::vector<std::vector<int>>& typical_testors_B, int max_N, YYC& yyc_instance, BT& bt_instance) {
    std::vector<TimingAnalysis> results;
    auto theta_AB = theta_operator(A, B);

    for (int N = 1; N <= max_N; ++N) {
        TimingAnalysis r;
        r.N = N;
        r.matrix_formula = "phi^" + std::to_string(N) + "(theta(A,B))";

        try {
            auto phi_theta = phi_operator(theta_AB, N);
            r.rows = count_rows(phi_theta);
            r.cols = count_cols(phi_theta);
            r.predicted_testors = predict_phi_theta_testors_count(typical_testors_A, typical_testors_B, N);

            auto sorted_matrix = sort_rows_by_ones(phi_theta);

            yyc_instance.shouldDisplayTime = false;
            yyc_instance.findTypicalTestors(phi_theta);
            r.yyc_time_any_order = yyc_instance.getExecutionTime();

            YYC yyc_sorted(r.cols);
            yyc_sorted.shouldDisplayTime = false;
            yyc_sorted.findTypicalTestors(sorted_matrix);
            r.yyc_time_sorted_ones = yyc_sorted.getExecutionTime();
            std::cout <<  yyc_sorted.getExecutionTime();
            bt_instance.shouldDisplayTime = false;
            bt_instance.findTypicalTestors(phi_theta);
            r.bt_time_any_order = bt_instance.getExecutionTime();

            BT bt_sorted(r.cols);
            bt_sorted.shouldDisplayTime = false;
            bt_sorted.findTypicalTestors(sorted_matrix);
            r.bt_time_sorted_ones = bt_sorted.getExecutionTime();

        } catch (const std::exception& e) {

        }
        results.push_back(r);
    }
    return results;
}

std::vector<TimingAnalysis> MatrixOperators::analyze_timing_gamma_series(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, const std::vector<std::vector<int>>& typical_testors_A, const std::vector<std::vector<int>>& typical_testors_B, int max_N, YYC& yyc_instance, BT& bt_instance) {
    std::vector<TimingAnalysis> results;
    auto base_matrix = theta_operator(A, B);

    for (int N = 1; N <= max_N; ++N) {
        TimingAnalysis r;
        r.N = N;
        r.matrix_formula = "gamma^" + std::to_string(N) + "(theta(A,B))";

        try
        {
            auto current_matrix = base_matrix;
            for (int i = 1; i < N; ++i) {
                current_matrix = gamma_operator(current_matrix, base_matrix);
            }
            r.rows = count_rows(current_matrix);
            r.cols = count_cols(current_matrix);
            r.predicted_testors = predict_gamma_theta_testors_count(typical_testors_A, typical_testors_B, N);

            auto sorted_matrix = sort_rows_by_ones(current_matrix);

            yyc_instance.shouldDisplayTime = false;
            yyc_instance.findTypicalTestors(current_matrix);
            r.yyc_time_any_order = yyc_instance.getExecutionTime() / 1e6;

            YYC yyc_sorted(r.cols);
            yyc_sorted.shouldDisplayTime = false;
            yyc_sorted.findTypicalTestors(sorted_matrix);
            r.yyc_time_sorted_ones = yyc_sorted.getExecutionTime() / 1e6;

            bt_instance.shouldDisplayTime = false;
            
            bt_instance.findTypicalTestors(current_matrix);
            r.bt_time_any_order = bt_instance.getExecutionTime() / 1e6 ;

            BT bt_sorted(r.cols);
            bt_sorted.shouldDisplayTime = false;
            bt_sorted.findTypicalTestors(sorted_matrix);
            r.bt_time_sorted_ones = bt_sorted.getExecutionTime() / 1e6 ;

        } 
        catch(std::exception a)
        {

        }
        results.push_back(r);
    }
    return results;
}

int MatrixOperators::count_rows(const std::vector<std::vector<int>>& matrix) {
    return static_cast<int>(matrix.size());
}

int MatrixOperators::count_cols(const std::vector<std::vector<int>>& matrix) {
    return matrix.empty() ? 0 : static_cast<int>(matrix[0].size());
}

int MatrixOperators::count_ones(const std::vector<int>& row) {
    return std::accumulate(row.begin(), row.end(), 0);
}

std::vector<std::vector<int>> MatrixOperators::sort_rows_by_ones(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) return matrix;
    
    // Create a vector to store rows with their ones count
    std::vector<std::pair<int, std::vector<int>>> rows_with_count;
    
    // Calculate ones count for each row and store with the row
    for (size_t i = 0; i < matrix.size(); ++i) {
        int ones = count_ones(matrix[i]);
        rows_with_count.push_back(std::make_pair(ones, matrix[i]));
    }
    
    // Sort by ones count (ascending)
    for (size_t i = 0; i < rows_with_count.size(); ++i) {
        for (size_t j = i + 1; j < rows_with_count.size(); ++j) {
            if (rows_with_count[j].first < rows_with_count[i].first) {
                // Swap the pairs
                std::pair<int, std::vector<int>> temp = rows_with_count[i];
                rows_with_count[i] = rows_with_count[j];
                rows_with_count[j] = temp;
            }
        }
    }
    
    // Extract just the sorted rows
    std::vector<std::vector<int>> sorted;
    for (size_t i = 0; i < rows_with_count.size(); ++i) {
        sorted.push_back(rows_with_count[i].second);
    }
    
    return sorted;
}
std::string MatrixOperators::format_timing_table(const std::vector<TimingAnalysis>& results) {
    std::stringstream ss;
    ss << std::left << std::setw(4) << "N"
       << std::setw(25) << "Matrix"
       << std::setw(8) << "Rows"
       << std::setw(8) << "Cols"
       << std::setw(12) << "|Psi*|"
       << std::setw(15) << "YYC_Any(s)"
       << std::setw(15) << "YYC_Sorted(s)"
       << std::setw(15) << "BT_Any(s)"
       << std::setw(15) << "BT_Sorted(s)"
       << "\n";
    ss << std::string(110, '-') << "\n";
    for (const auto& r : results) {
        ss << std::left << std::setw(4) << r.N
           << std::setw(25) << r.matrix_formula
           << std::setw(8) << r.rows
           << std::setw(8) << r.cols
           << std::setw(12) << r.predicted_testors
           << std::setw(15) << std::fixed << std::setprecision(6) << r.yyc_time_any_order
           << std::setw(15) << std::fixed << std::setprecision(6) << r.yyc_time_sorted_ones
           << std::setw(15) << std::fixed << std::setprecision(6) << r.bt_time_any_order
           << std::setw(15) << std::fixed << std::setprecision(6) << r.bt_time_sorted_ones
           << "\n";
    }
    return ss.str();
}
