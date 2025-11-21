#pragma once
#include <vector>
#include <cstdint>



class BT {
public:
bool shouldDisplayTime{true};
    long long executionTimeMicroseconds = 0;
    long long getVisitedNodes() const { return visitedNodes; }
    double getExecutionTime() const { return executionTimeMicroseconds; }
    explicit BT(int numColumns);
    void resetVisitedNodesIfExists();

    // MB es vector<vector<int>> con valores 0 y 1
    std::vector<std::vector<int>>
    findTypicalTestors(const std::vector<std::vector<int>>& MB);

private:

    long long visitedNodes = 0;   // NEW
  
    int n; // número de columnas

    inline int bit(int col) const { return (n - 1 - col); }

    bool isTestor(uint64_t mask, const std::vector<std::vector<int>>& MB) const;
    bool isTypical(uint64_t mask, const std::vector<std::vector<int>>& MB) const;

    int rightmostOneInRow(const std::vector<int>& row) const;
    int rightmostOneInMask(uint64_t mask) const;

    bool isSuperset(uint64_t a, uint64_t b) const;
};
