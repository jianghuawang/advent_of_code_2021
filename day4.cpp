#include <stdio.h>
#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int BOARD_NUM = 100;

class Point {
public:
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& p) : x(p.x), y(p.y) {}
    
    int x, y;
};

class Board {
public:
    Board() : bd(5, vector<int>(5)) {}
    vector<vector<int>> bd;
    unordered_map<int, Point> mp;
};

void preProcess(vector<int>& randNums, vector<Board>& boards) {
    int rand_num;
    int rand_cnt = 99;
    scanf("%d", &rand_num);
    randNums.push_back(rand_num);
    while (rand_cnt--) {
        scanf(",%d", &rand_num);
        randNums.push_back(rand_num);
    }

    for (int cnt = 0; cnt < BOARD_NUM; ++cnt) {
        auto& bd = boards[cnt].bd;
        auto& mp = boards[cnt].mp;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                int val = 0;
                scanf("%d", &val);
                bd[i][j] = val;
                mp.insert({val, Point(i, j)});
            }
        }
    }
}

bool check(vector<vector<int>>& bd, Point& p) {
    bool res_row = true, res_col = true;
    int x = p.x;
    int y = p.y;
    int temp_x = 0;
    int temp_y = 0;
    while (temp_y < 5) {
        if (bd[x][temp_y++] > 0) {
            res_row = false;
        }
        if (bd[temp_x++][y] > 0) {
            res_col = false;
        }
    }
    return res_row || res_col;
}

int calResult(vector<vector<int>>& boards, int num) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (boards[i][j] > 0) { sum += boards[i][j]; }
        }
    }
    return num * sum;
}

int part1() {
    vector<int> rand_nums;
    vector<Board> boards(BOARD_NUM);
    preProcess(rand_nums,boards);
    for (int num : rand_nums) {
        for (int i = 0; i < boards.size(); ++i) {
            auto& bd = boards[i].bd;
            auto& mp = boards[i].mp;
            if (mp.find(num) != mp.end()) {
                Point p = mp[num];
                bd[p.x][p.y] = INT_MIN;
                if (check(bd, p)) {
                    return calResult(bd, num);
                }
            }
        }
    }
    return 0;
}

int part2() {
    vector<int> rand_nums;
    vector<Board> boards(BOARD_NUM);
    preProcess(rand_nums,boards);
    bool st[BOARD_NUM];
    memset(st, 0, sizeof(st));
    int fin_count = 0;
    for (int num : rand_nums) {
        for (int i = 0; i < boards.size(); ++i) {
            if (st[i]) { continue; }
            auto& bd = boards[i].bd;
            auto& mp = boards[i].mp;
            if (mp.find(num) != mp.end()) {
                Point p = mp[num];
                bd[p.x][p.y] = INT_MIN;
                if (check(bd, p)) {
                    if (fin_count < BOARD_NUM - 1) {
                        st[i] = 1;
                        ++fin_count;
                    } else {
                        return calResult(bd, num);
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    cout << part2() << endl;
    return 0;
}