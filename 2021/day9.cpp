#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const vector<int> direction({-1, 0, 1, 0, -1});

void part1() {
    string line;
    vector<vector<int>> arr;
    int res = 0;
    while (getline(cin, line)) {
        vector<int> curr;
        for (auto c : line) {
            curr.push_back(c - '0');
        }
        arr.push_back(curr);
    }
    int row = arr.size();
    int col = arr[0].size();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i > 0 && arr[i - 1][j] <= arr[i][j]) { continue; }
            if (i < row - 1 && arr[i + 1][j] <= arr[i][j]) { continue; }
            if (j > 0 && arr[i][j - 1] <= arr[i][j]) { continue; }
            if (j < col - 1 && arr[i][j + 1] <= arr[i][j]) { continue; }
            res += 1 + arr[i][j];
        }
    }
    cout << res << endl;
}

int dfs(vector<vector<int>>& arr, vector<vector<bool>>& visited, int i, int j) {
    int val = arr[i][j];
    visited[i][j] = 1;
    int res = 1;
    for (int x = 0; x < direction.size() - 1; ++x) {
        int new_i = i + direction[x];
        int new_j = j + direction[x + 1];
        if (new_i < 0 || new_i >= arr.size() || new_j < 0 || new_j >= arr[0].size()
            || visited[new_i][new_j] || arr[new_i][new_j] <= val || arr[new_i][new_j] == 9) {
                continue;
        }
        res += dfs(arr, visited, new_i, new_j);
    }
    return res;
}

void part2() {
    string line;
    vector<vector<int>> arr;
    priority_queue<int, vector<int>, greater<int>> q;
    int res = 1;
    while (getline(cin, line)) {
        vector<int> curr;
        for (auto c : line) {
            curr.push_back(c - '0');
        }
        arr.push_back(curr);
    }
    int row = arr.size();
    int col = arr[0].size();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i > 0 && arr[i - 1][j] <= arr[i][j]) { continue; }
            if (i < row - 1 && arr[i + 1][j] <= arr[i][j]) { continue; }
            if (j > 0 && arr[i][j - 1] <= arr[i][j]) { continue; }
            if (j < col - 1 && arr[i][j + 1] <= arr[i][j]) { continue; }
            vector<vector<bool>> visited(row, vector<bool>(col, false));
            int size = dfs(arr, visited, i, j);
            if (q.size() == 3) {
                size = max(size, q.top());
                q.pop();
            }
            q.push(size);
        }
    }
    while (q.size()) {
        res *= q.top();
        q.pop();
    }
    cout << res << endl;
}

int main() {
    part2();
    return 0;
}