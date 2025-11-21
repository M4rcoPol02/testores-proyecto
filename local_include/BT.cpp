#include "BT.h"
#include <algorithm>
#include <stdexcept>
#include "ExecutionTime.h"

BT::BT(int numColumns) : n(numColumns) {
    if (n <= 0 || n > 60)
        throw std::invalid_argument("numColumns must be between 1 and 60");
}

// -------------------------------------------------------------
// PROPOSICIÓN 1.3 - Detector de Testores
// -------------------------------------------------------------
bool BT::isTestor(uint64_t mask, const std::vector<std::vector<int>>& MB) const {

    for (const auto& row : MB) {

        bool sharesOne = false;

        for (int c = 0; c < n; ++c) {
            uint64_t b = (1ULL << bit(c));
            if ((mask & b) && row[c] == 1) {
                sharesOne = true;
                break;
            }
        }

        if (!sharesOne) return false;
    }

    return true;
}

// -------------------------------------------------------------
// Irreducible (típico)
// -------------------------------------------------------------
bool BT::isTypical(uint64_t mask, const std::vector<std::vector<int>>& MB) const {

    for (int c = 0; c < n; ++c) {
        uint64_t b = (1ULL << bit(c));
        if (mask & b) {
            uint64_t m2 = mask & ~b;
            if (isTestor(m2, MB)) return false;  // reducible
        }
    }

    return true;
}

// 1 más a la derecha en una fila
int BT::rightmostOneInRow(const std::vector<int>& row) const {
    for (int c = n - 1; c >= 0; --c)
        if (row[c] == 1)
            return c;
    return -1;
}

// 1 más a la derecha en la máscara
int BT::rightmostOneInMask(uint64_t mask) const {
    for (int c = n - 1; c >= 0; --c) {
        uint64_t b = (1ULL << bit(c));
        if (mask & b) return c;
    }
    return -1;
}

bool BT::isSuperset(uint64_t a, uint64_t b) const {
    return ( (a & b) == b );
}

// -------------------------------------------------------------
// ALGORITMO BT COMPLETO
// -------------------------------------------------------------
std::vector<std::vector<int>>
BT::findTypicalTestors(const std::vector<std::vector<int>>& MB)
{
    executionTimeMicroseconds = 0; 
    auto globalStart = std::chrono::steady_clock::now();

    ExecutionTime t{"Tiempo de ejecuciónn BT"};
    if (MB.empty()) return {};

    uint64_t maxMask = (1ULL << n) - 1ULL;

    uint64_t mask = 1ULL;   // α inicial = [0..01]

    std::vector<uint64_t> typicalMasks;

    while (mask <= maxMask && mask != 0) {

        // ≡ PROPOSICIÓN 1.3
        if (isTestor(mask, MB)) {

            // ¿Es típico?
            if (isTypical(mask, MB)) {

                // Eliminar todos los típicos anteriores que sean superconjuntos
                std::vector<uint64_t> filtered;
                for (uint64_t t : typicalMasks) {
                    if (!isSuperset(t, mask))
                        filtered.push_back(t);
                }
                typicalMasks.swap(filtered);

                typicalMasks.push_back(mask);
            }

            // -------------------------------
            // PROPOSICIÓN 1.4 - Saltar superconjuntos
            // -------------------------------
            int k = rightmostOneInMask(mask);

            uint64_t newMask = 0;

            // mantener bits < k
            for (int c = 0; c < k; ++c) {
                uint64_t b = (1ULL << bit(c));
                if (mask & b) newMask |= b;
            }

            if (newMask <= mask) newMask = mask + 1;

            mask = newMask;
        }
        else {

            // -------------------------------------------
            // PROPOSICIÓN 1.5 CORREGIDA
            // -------------------------------------------
            std::vector<int> guiltyRightmost;

            // buscar filas culpables
            for (const auto& row : MB) {

                bool shares = false;
                for (int c = 0; c < n; ++c) {
                    uint64_t b = (1ULL << bit(c));
                    if ((mask & b) && row[c] == 1) {
                        shares = true;
                        break;
                    }
                }

                if (!shares) {
                    int r = rightmostOneInRow(row);
                    if (r >= 0)
                        guiltyRightmost.push_back(r);
                }
            }

            if (guiltyRightmost.empty()) {
                mask++;
                continue;
            }

            // el más pequeño (más a la izquierda)
            int k = *std::min_element(guiltyRightmost.begin(), guiltyRightmost.end());

            uint64_t newMask = 0;

            // indices < k se conservan
            for (int c = 0; c < k; ++c) {
                uint64_t b = (1ULL << bit(c));
                if (mask & b) newMask |= b;
            }

            // índice k = 0

            // indices > k = 1
            for (int c = k + 1; c < n; ++c) {
                uint64_t b = (1ULL << bit(c));
                newMask |= b;
            }

            if (newMask <= mask)
                mask++;
            else
                mask = newMask;
        }
    }

    // ---------------------------------------------------------
    // Convertir máscaras a testores con índices 1-based
    // ---------------------------------------------------------
    std::vector<std::vector<int>> result;

    for (uint64_t fm : typicalMasks) {
        std::vector<int> t;
        for (int c = 0; c < n; ++c) {
            uint64_t b = (1ULL << bit(c));
            if (fm & b)
                t.push_back(c + 1);  // 1-based
        }
        result.push_back(t);
    }

    auto totalDuration = std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::steady_clock::now() - globalStart);

    executionTimeMicroseconds = totalDuration.count();

     executionTimeMicroseconds = totalDuration.count();

    return result;
}