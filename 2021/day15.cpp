#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <queue>
#include <utility>

using namespace std;

const vector<int> direction{-1, 0, 1, 0, -1};

struct Node {
    Node() {}
    Node(int x, int y, int dist) : x(x), y(y), dist(dist) {}
    int x, y, dist;
};

class Cmp {
public:
    bool operator()(const Node& lhs, const Node& rhs) const { 
        return lhs.dist > rhs.dist;
    }
};

int minDist(vector<vector<int>>& table) {
    int row = table.size();
    int col = table[0].size();
    vector<vector<int>> dist(row, vector<int>(col, INT_MAX));
    priority_queue<Node, vector<Node>, Cmp> q;
    dist[0][0] = 0;
    q.push(Node(0, 0, 0));

    while (q.size()) { 
        Node n = q.top();
        q.pop();
        if (dist[n.x][n.y] < n.dist) { continue; }
        for (int i = 0; i < direction.size() - 1; ++i) {
            int new_x = n.x + direction[i];
            int new_y = n.y + direction[i + 1];
            if (new_x < 0 || new_x >= row || new_y < 0 || new_y >= col) { continue; }
            if (n.dist + table[new_x][new_y] < dist[new_x][new_y]) { 
                dist[new_x][new_y] = n.dist + table[new_x][new_y];
                q.push(Node(new_x, new_y, dist[new_x][new_y]));
            }
        }
    }

    return dist[row - 1][col - 1];
}

void part1() {
    string line;
    vector<vector<int>> table;
    while (getline(cin, line)) {
        vector<int> curr_line;
        for (char c : line) {
            curr_line.push_back(c - '0');
        }
        table.push_back(curr_line);
    }
    cout << minDist(table) << endl;
}

void fillTable(vector<vector<int>>& table, int row, int col, int i, int j) {
    int delta_x = 0, delta_y = -100;
    if (j) { swap(delta_x, delta_y); }

    for (int x = i * row; x < i * row + row; ++x) {
        for (int y = j * col; y < j * col + col; ++y) {
            int val = table[x + delta_x][y + delta_y];
            table[x][y] = (val == 9) ? 1 : val + 1;
        }
    }
}

void part2() {
    string line;
    vector<vector<int>> table;
    while (getline(cin, line)) {
        vector<int> curr_line;
        for (char c : line) {
            curr_line.push_back(c - '0');
        }
        table.push_back(curr_line);
    }
    int row = table.size();
    int col = table[0].size();
    vector<vector<int>> full_table(5 * row, vector<int>(5 * col));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) { full_table[i][j] = table[i][j]; }
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (!i && !j) { continue; }
            fillTable(full_table, row, col, i, j);
        }
    }
    cout << minDist(full_table) << endl;
}

int main(int argc, char** argv) {
    part1();
    return 0;
}