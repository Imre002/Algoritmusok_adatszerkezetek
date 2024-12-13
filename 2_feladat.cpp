#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<int> rowCount(n, 0);
    vector<int> colCount(n, 0);

    // Count the number of coins in each row and column
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'o') {
                rowCount[i]++;
                colCount[j]++;
            }
        }
    }

    vector<pair<int, int>> moves;
    vector<bool> rowCleared(n, false);
    vector<bool> colCleared(n, false);

    // Continue until all coins are removed
    while (true) {
        int maxRow = -1, maxRowCount = 0;
        for (int i = 0; i < n; i++) {
            if (!rowCleared[i] && rowCount[i] > maxRowCount) {
                maxRow = i;
                maxRowCount = rowCount[i];
            }
        }

        int maxCol = -1, maxColCount = 0;
        for (int j = 0; j < n; j++) {
            if (!colCleared[j] && colCount[j] > maxColCount) {
                maxCol = j;
                maxColCount = colCount[j];
            }
        }

        if (maxRowCount == 0 && maxColCount == 0) {
            break;
        }

        if (maxRowCount >= maxColCount) {
            moves.push_back({1, maxRow + 1});
            rowCleared[maxRow] = true;
            for (int j = 0; j < n; j++) {
                if (grid[maxRow][j] == 'o') {
                    colCount[j]--;
                }
            }
            rowCount[maxRow] = 0;
        } else {
            moves.push_back({2, maxCol + 1});
            colCleared[maxCol] = true;
            for (int i = 0; i < n; i++) {
                if (grid[i][maxCol] == 'o') {
                    rowCount[i]--;
                }
            }
            colCount[maxCol] = 0;
        }
    }

    // Output the result
    cout << moves.size() << endl;
    for (const auto& move : moves) {
        cout << move.first << " " << move.second << endl;
    }

    return 0;
}
