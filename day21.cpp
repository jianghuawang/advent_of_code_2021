#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <chrono>

using namespace std;

typedef long long ll;

// Player 1 starting position: 5
// Player 2 starting position: 10

const int STARTPOS1 = 5;
const int STARTPOS2 = 10;

void update(int& currPos, int& dice, int& rolls, int& score) {
    int time = 3, val = 0;
    while (time--) {
        dice = (dice > 100) ? dice % 100 : dice;
        val += dice;
        ++dice;
    }
    currPos = ((val + currPos) % 10) ? ((val + currPos) % 10) : 10;
    score += currPos;
    rolls += 3;
}

void part1() {
    int res = 0;
    int dice = 1;
    int rolls = 0;
    int pos1 = STARTPOS1;
    int pos2 = STARTPOS2;
    int score1 = 0;
    int score2 = 0;
    while (score1 < 1000 && score2 < 1000) {
        update(pos1, dice, rolls, score1);
        if (score1 >= 1000) { break; }
        update(pos2, dice, rolls, score2);
    }
    res = rolls * min(score1, score2);
    cout << res << endl;
}

const int GOAL = 21;
const int RANGE = 10 + 1;

bool checkEmpty(ll dp[][RANGE][GOAL][RANGE]) {
    for (int i = 0; i < GOAL; i++) {
        for (int j = 0; j < RANGE; j++) {
            for (int k = 0; k < GOAL; k++) {
                for (int l = 0; l < RANGE; l++) {
                    if (dp[i][j][k][l]) { return false; }
                }
            }
        }
    }
    return true;
}

const vector<int> appears{0, 0, 0, 1, 3, 6, 7, 6, 3, 1};

ll win1 = 0;
ll win2 = 0;
// time spent: 0.64363700 sec
void part2_recursive(int player, int score1, int score2, int pos1, int pos2, ll numUni) {
    if (score1 >= GOAL) { 
        win1 += numUni;
        return;
    } else if (score2 >= GOAL) {
        win2 += numUni;
        return;
    }
    for (int val = 3; val <= 9; ++val) { 
        if (!player) { 
            int new_pos = ((pos1 + val) % 10) ? (pos1 + val) % 10 : 10;
            part2_recursive(1 - player, score1 + new_pos, score2, new_pos, pos2, appears[val] * numUni);
        } else {
            int new_pos = ((pos2 + val) % 10) ? (pos2 + val) % 10 : 10;
            part2_recursive(1 - player, score1, score2 + new_pos, pos1, new_pos, appears[val] * numUni);
        }
    }
}

void update(ll input[][RANGE][GOAL][RANGE], ll output[][RANGE][GOAL][RANGE], int player) {
    for (int i = 0; i < GOAL; i++) {
        for (int j = 0; j < RANGE; j++) {
            for (int k = 0; k < GOAL; k++) {
                for (int l = 0; l < RANGE; l++) {
                    for (int val = 3; val <= 9; ++val) {
                        if (!player) {
                            int new_pos = j + val;
                            new_pos = (new_pos % 10) ? new_pos % 10 : 10;
                            if (new_pos + i >= GOAL) {
                                win1 += appears[val] * input[i][j][k][l];
                            } else {
                                output[new_pos + i][new_pos][k][l] += appears[val] * input[i][j][k][l];
                            }
                        } else {
                            int new_pos = l + val;
                            new_pos = (new_pos % 10) ? new_pos % 10 : 10;
                            if (new_pos + k >= GOAL) {
                                win2 += appears[val] * input[i][j][k][l];
                            } else {
                                output[i][j][new_pos + k][new_pos] += appears[val] * input[i][j][k][l];
                            }
                        }
                    }
                }
            }
        }
    }
}
// time spent: 0.06644100s
void part2_iterative() {
    ll dp[GOAL][RANGE][GOAL][RANGE];
    ll temp[GOAL][RANGE][GOAL][RANGE];
    memset(dp, 0, sizeof(dp));
    dp[0][STARTPOS1][0][STARTPOS2] = 1;
    while (true) {
        memset(temp, 0, sizeof(temp));
        update(dp, temp, 0);
        memset(dp, 0, sizeof(dp));
        update(temp, dp, 1);
        if (checkEmpty(dp)) { break; }
    }
    
}
int main(int argc, char* argv[]) {
    clock_t start, end;
    start = clock();
    part2_recursive(0, 0, 0, STARTPOS1, STARTPOS2, 1);
    end = clock();
    cout << win1 <<", " << win2 << endl;
    printf ("time spent: %0.8f sec\n",
            ((float) end - start)/CLOCKS_PER_SEC);
    return 0;
}