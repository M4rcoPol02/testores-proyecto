#ifndef BT_H
#define BT_H

#include <vector>

class BT {
private:
    std::vector<int> currentRow;
    int columns;
    
    void StartingRow();
    void NextRow(int skip);
    bool IsTestor(const std::vector<std::vector<int>>& basicMatrix);
    int CalculateSkipProp1_4();
    int CalculateSkipProp1_5(const std::vector<std::vector<int>>& basicMatrix);
    bool IsLastRow() const;

public:
    BT(int cols);
    std::vector<std::vector<int>> FindTypicalTestors(const std::vector<std::vector<int>>& basicMatrix);
};

#endif