#include <stdio.h>
#include <math.h>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void part1() {
    vector<int> pos;
    int val;
    int min_val = 0, max_val = 0;
    int res = INT_MAX;
    while (scanf("%d,", &val) == 1) {
        min_val = min(min_val, val);
        max_val = max(max_val, val);
        pos.push_back(val);
    }
    for (int i = min_val; i <= max_val; ++i) {
        int sum = 0;
        for (int p : pos) {
            sum += abs(p - i);
        }
        res = min(res, sum);
    }
    cout << res << endl;
}

void part2() {
    unordered_map<int, int> cnts;
    int val;
    int min_val = 0, max_val = 0;
    int res = INT_MAX;
    while (scanf("%d,", &val) == 1) {
        min_val = min(min_val, val);
        max_val = max(max_val, val);
        ++cnts[val];
    }
    for (int i = min_val; i <= max_val; ++i) {
        int sum = 0;
        for (auto& [val, cnt] : cnts) {
            int steps = abs(val - i);
            sum += ((1 + steps) * steps / 2) * cnt;
        }
        res = min(res, sum);
    }
    cout << res << endl;
}

int main(int argc, char **argv) {
    part2();
    return 0;
}