#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;

const int BOARD_SIZE = 1000;

void count(vector<vector<int>>& board, int x1, int y1, int x2, int y2,int delta_x, int delta_y, int& res) {
    while (x1 != x2 || y1 != y2) {
        if (++board[x1][y1] == 2) { ++res; }
        y1 += delta_y;
        x1 += delta_x;
    }
    if (++board[x1][y1] == 2) { ++res; }
}

void part1() {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE));
    int cnt = 500, res = 0;
    int x1, x2, y1, y2;
    while (scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
        if (x1 == x2 || y1 == y2) {
            int dir_y = (y2 > y1) ? 1 : (y2 == y1) ? 0 : -1;
            int dir_x = (x2 > x1) ? 1 : (x2 == x1) ? 0 : -1;
            count(board, x1, y1, x2, y2, dir_x, dir_y, res);
        }
    }
    printf("%d\n", res);
}

void part2() {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE));
    int cnt = 500, res = 0;
    int x1, x2, y1, y2;
    while (scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
        if (x1 == x2 || y1 == y2 || abs(y1 - y2) == abs(x1 - x2)) {
            int dir_y = (y2 > y1) ? 1 : (y2 == y1) ? 0 : -1;
            int dir_x = (x2 > x1) ? 1 : (x2 == x1) ? 0 : -1;
            count(board, x1, y1, x2, y2, dir_x, dir_y, res);
        }
    }
    printf("%d\n", res);
}
int main() {
    part2();
    return 0;
}