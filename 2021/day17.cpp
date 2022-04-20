#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <utility>
#include <algorithm>

using namespace std;

// target area: x=119..176, y=-141..-84

const int Y_LOWER_BOUND = -141;
const int Y_UPPER_BOUND = -84;
const int X_LOWER_BOUND = 119;
const int X_UPPER_BOUND = 176;

int findMinXSpeed() {
    for (int i = 1; i <= X_UPPER_BOUND; ++i) {
        int pos = i * (i + 1) / 2;
        if (pos >= X_LOWER_BOUND && pos <= X_UPPER_BOUND) { 
            return i;
        }
    }
    return INT_MAX;
}

int findMaxYSpeed() {
    int res = 0;
    for (int v = 1; v < 1000; ++v) {
        int curr_velocity = -1;
        int pos = v * (v + 1) / 2;
        while (true) {
            if (pos + curr_velocity < Y_LOWER_BOUND) { break; }
            pos += curr_velocity;
            --curr_velocity;
        }
        if (pos <= Y_UPPER_BOUND && pos >= Y_LOWER_BOUND) {
            res = v;
        }
    }
    return res;
}

void part1() {
    int res = findMaxYSpeed();
    cout << res * (res + 1) / 2 << endl;
}

void part2() {
    int res = 0;
    unordered_map<int, pair<int, int>> mp;
    int min_x_speed = findMinXSpeed();
    int max_y_speed = findMaxYSpeed();
    for (int x = min_x_speed; x <= X_UPPER_BOUND; ++x) {
        int pos = 0;
        int curr_v = x;
        int min_steps = INT_MAX, max_steps = 0;
        int steps = 0;
        while (pos <= X_UPPER_BOUND) { 
            ++steps;
            pos += curr_v;
            if (pos > X_UPPER_BOUND || !curr_v) { break; }
            --curr_v;
            if (pos >= X_LOWER_BOUND) { 
                min_steps = min(steps, min_steps);
                max_steps = max(steps, max_steps);
            }
        }
        if (pos <= X_UPPER_BOUND) { max_steps = INT_MAX; }
        mp[x] = {min_steps, max_steps};
    }

    for (int x = min_x_speed; x <= X_UPPER_BOUND; ++x) {
        auto [min_steps, max_steps] = mp[x];
        if (min_steps > max_steps) { continue; }
        for (int y = Y_LOWER_BOUND; y <= max_y_speed; ++y) {
            int pos = 0;
            int curr_v = y;
            int steps = 0;
            while (pos >= Y_LOWER_BOUND) {
                ++steps;
                pos += curr_v;
                --curr_v;
                if (pos < Y_LOWER_BOUND || steps > max_steps) { break; }
                if (pos <= Y_UPPER_BOUND && steps >= min_steps) {
                    ++res;
                    break;
                }
            }
        }
    }
    cout << res << endl;
}
int main() {
    cout << findMinXSpeed() << endl;
    part2();
    return 0;
}