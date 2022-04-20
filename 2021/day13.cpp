#include <vector>
#include <iostream>
#include <string>

using namespace std;

void part1() {
    const int row = 895, col = 1308;
    vector<vector<bool>> paper(row, vector<bool>(col, false));
    string line;
    int cnt = 0;
    while (getline(cin, line)) {
        int x = 0, y = 0;
        size_t pos = line.find(',');
        if (!line.size()) { break; }
        x = stoi(line.substr(0, pos));
        y = stoi(line.substr(pos + 1));
        paper[y][x] = 1;
    }
    getline(cin, line);
    size_t pos = line.find('=');
    int fold = stoi(line.substr(pos + 1));
    int res = 0;
    for (int l = 2, j = fold + 1; j < col; ++j, l += 2) {
        for (int i = 0; i < row; ++i) {
            paper[i][j - l] = paper[i][j - l] || paper[i][j];
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < fold; ++j) {
            res += paper[i][j];
        }
    }
    cout << res << endl;
}

void part2() {
    int row = 895, col = 1308;
    vector<vector<bool>> paper(row, vector<bool>(col, false));
    string line;
    int cnt = 0;
    while (getline(cin, line)) {
        int x = 0, y = 0;
        size_t pos = line.find(',');
        if (!line.size()) { break; }
        x = stoi(line.substr(0, pos));
        y = stoi(line.substr(pos + 1));
        paper[y][x] = 1;
    }
    while (getline(cin, line)) {
        size_t pos = line.find('=');
        char dir = line[pos - 1];
        int fold_idx = stoi(line.substr(pos + 1));
        
        if (dir == 'x') {
            for (int l = 2, j = fold_idx + 1; j < col; ++j, l += 2) {
                for (int i = 0; i < row; ++i) {
                    paper[i][j - l] = paper[i][j - l] || paper[i][j];
                }
            }
            col = fold_idx;
        } else {
            for (int l = 2, i = fold_idx + 1; i < row; ++i, l += 2) {
                for (int j = 0; j < col; ++j) {
                    paper[i - l][j] = paper[i - l][j] || paper[i][j];
                }
            }
            row = fold_idx;
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (paper[i][j]) { cout << '#'; }
            else { cout << '.'; }
        }
        cout << endl;
    }
}
int main(int argc, char** argv) {
    part2();
    return 0;
}