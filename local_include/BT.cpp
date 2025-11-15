#include "BT.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

BT::BT(int cols) : columns(cols) {}

void BT::StartingRow() {
    currentRow.assign(columns, 0);
    currentRow.back() = 1;
}


void BT::NextRow(int skip) {
    int value = 0;
    for (int bit : currentRow) value = (value << 1) | bit;

    value += skip;

    int maxValue = (1 << columns) - 1;
    if (value > maxValue) {
        value = maxValue; 
    }

    currentRow.clear();
    for (int i = columns - 1; i >= 0; i--) {
        currentRow.push_back((value >> i) & 1);
    }
}


//1.3
bool BT::IsTestor(const vector<vector<int>>& basicMatrix) {
    for (const auto& mbRow : basicMatrix) {
        bool coversRow = false;
        for (int j = 0; j < columns; j++) {
            if (currentRow[j] == 1 && mbRow[j] == 1) {
                coversRow = true;
                break;
            }
        }
        if (!coversRow) return false;
    }
    return true;
}

//1.4
int BT::CalculateSkipProp1_4() {
    int lastOnePos = -1;
    for (int j = 0; j < columns; j++) {
        if (currentRow[j] == 1) lastOnePos = j;
    }
    if (lastOnePos == -1) return 0; 

    int k = columns - lastOnePos - 1; 
    return (1 << k) - 1; 
}

//1.5
int BT::CalculateSkipProp1_5(const vector<vector<int>>& basicMatrix) {
    vector<int> failingRows;

    for (int i = 0; i < basicMatrix.size(); i++) {
        bool fails = true;
        for (int j = 0; j < columns; j++) {
            if (basicMatrix[i][j] == 1 && currentRow[j] == 1) {
                fails = false;
                break;
            }
        }
        if (fails) failingRows.push_back(i);
    }

    if (failingRows.empty()) return -1; 

    int pivot = -1;
    for (int rowIdx : failingRows) {
        const auto& row = basicMatrix[rowIdx];

        for (int j = columns - 1; j >= 0; j--) {
            if (row[j] == 1 && j > pivot) {
                pivot = j;
                break;
            }
        }
    }

    int bitsRight = columns - pivot - 1;
    return (1 << bitsRight) - 1; 
}

bool BT::IsLastRow() const {
    for (int bit : currentRow) {
        if (bit == 0) return false;
    }
    return true;
}

vector<vector<int>> BT::FindTypicalTestors(const vector<vector<int>>& basicMatrix) {
    vector<vector<int>> typicalTestors;

    StartingRow();

    while (true) {
        if (IsTestor(basicMatrix)) {
            bool isTypical = true;
            for (const auto& t : typicalTestors) {
                bool subset = true;
                for (int j = 0; j < columns; j++) {
                    if (t[j] == 1 && currentRow[j] == 0) {
                        subset = false;
                        break;
                    }
                }
                if (subset) {
                    isTypical = false;
                    break;
                }
            }

            if (isTypical) {
                typicalTestors.push_back(currentRow);

                vector<vector<int>> filtered;
                for (auto& t : typicalTestors) {
                    bool superset = false;
                    for (auto& o : typicalTestors) {
                        if (t != o) {
                            bool isSuperset = true;
                            for (int j = 0; j < columns; j++) {
                                if (o[j] == 1 && t[j] == 0) {
                                    isSuperset = false;
                                    break;
                                }
                            }
                            if (isSuperset) {
                                superset = true;
                                break;
                            }
                        }
                    }
                    if (!superset) filtered.push_back(t);
                }
                typicalTestors = filtered;
            }

            // Proposition 1.4
            int skip = CalculateSkipProp1_4();
            NextRow(skip + 1);
        }
        else {
            // Proposition 1.5
            int skip = CalculateSkipProp1_5(basicMatrix);
            if (skip < 0) skip = 0;
            NextRow(skip + 1);
        }

        if (IsLastRow()) break;
    }

    return typicalTestors;
}

