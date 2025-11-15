#ifndef BT_H
#define BT_H

#include <vector>

class BT {
public:
    BT(int cols);

    void StartingRow();
    void NextRow(int skip);
    bool IsLastRow() const;
    bool IsTestor(const std::vector<std::vector<int>>& basicMatrix);

    int CalculateSkipProp1_4();
    int CalculateSkipProp1_5(const std::vector<std::vector<int>>& basicMatrix);

    std::vector<std::vector<int>> FindTypicalTestors(
        const std::vector<std::vector<int>>& basicMatrix);

private:
    int columns;
    std::vector<int> currentRow;
};

#endif
