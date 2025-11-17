#ifndef YYC_H
#define YYC_H

#include <vector>
#include <algorithm>    // necesario para sort
using std::vector;

class YYC 
{
public:
    vector<vector<int>> findTypicalTestors(const vector<vector<int>>& matrix);

private:
    bool findCompatibleSet(const vector<int>& testor, int newCol, 
                           const vector<vector<int>>& matrix, int rowsUpTo);

    vector<vector<int>> getSubmatrix(const vector<vector<int>>& matrix, 
                                     const vector<int>& cols, int rowsUpTo);

    bool isSubsetStrict(const vector<int>& a, const vector<int>& b);

    // DEBE SER static PARA PODER PASAR A sort
    static bool compareBySizeThenLex(const vector<int>& a, const vector<int>& b);
};

#endif
