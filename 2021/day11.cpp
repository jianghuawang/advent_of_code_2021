#include <vector>
#include <iostream>
#include <string>

using namespace std;

const vector<int> delta({-1, 0, 1});

void flash(vector<vector<int>>& energy, vector<vector<bool>>& flashed,
            int& res, int i, int j) {
    ++res;
    flashed[i][j] = true;
    for (const int delta_i : delta) {
        for (const int delta_j : delta) {
            int new_i = i + delta_i;
            int new_j = j + delta_j;
            if (new_i < 0 || new_i >= flashed.size() || new_j < 0
                || new_j >= flashed[0].size() || flashed[new_i][new_j]) {
                    continue;
            }
            if (++energy[new_i][new_j] > 9) { flash(energy, flashed, res, new_i, new_j); }
        }
    }
    energy[i][j] = 0;
}
void part1() {
    int steps = 100, res = 0;
    string line;
    vector<vector<int>> energy;
    while (getline(cin, line)) {
        vector<int> line_energy;
        for (char val : line) {
            line_energy.push_back(val - '0');
        }
        energy.push_back(line_energy);
    }
    int row = energy.size();
    int col = energy[0].size();
    while (steps--) {
        vector<vector<bool>> flashed(row, vector<bool>(col, false));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (flashed[i][j]) { continue; }
                if (++energy[i][j] > 9) { 
                    flash(energy, flashed, res, i, j);
                }
            }
        }
    }
    cout << res << endl;
}

void part2() {
    int res = 0;
    string line;
    vector<vector<int>> energy;
    while (getline(cin, line)) {
        vector<int> line_energy;
        for (char val : line) {
            line_energy.push_back(val - '0');
        }
        energy.push_back(line_energy);
    }
    int row = energy.size();
    int col = energy[0].size();
    while (++res) {
        vector<vector<bool>> flashed(row, vector<bool>(col, false));
        int cnt = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (flashed[i][j]) { continue; }
                if (++energy[i][j] > 9) { 
                    flash(energy, flashed, cnt, i, j);
                }
            }
        }
        if (cnt == row * col) { break; }
    }
    cout << res << endl;
}

int main(int argc, char** argv) {
    part2();
    return 0;
}