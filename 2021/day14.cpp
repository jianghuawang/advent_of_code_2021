#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include<limits.h>

using namespace std;

void part1() {
    int steps = 10;
    unordered_map<string, char> mp;
    string poly_templ;
    getline(cin, poly_templ);
    string line;
    while (getline(cin, line)) {
        size_t pos = line.find('-');
        if (pos == string::npos) { continue; }
        mp[line.substr(0, pos - 1)] = line.back();
    }
    while (steps--) {
        string temp;
        for (int i = 0; i < poly_templ.size() - 1; ++i) {
            temp.push_back(poly_templ[i]); 
            if (mp.count(poly_templ.substr(i, 2))) {
                temp.push_back(mp[poly_templ.substr(i, 2)]);
            }
        }
        temp.push_back(poly_templ.back());
        poly_templ = temp;
    }
    vector<int> cnt(26);
    for (char c : poly_templ) {
        ++cnt[c - 'A'];
    }
    int min_cnt = 0x7fffffff, max_cnt = -1;
    for (int val : cnt) {
        if (!val) { continue; }
        min_cnt = min(min_cnt, val);
        max_cnt = max(max_cnt, val);
    }
    cout <<  (max_cnt - min_cnt) << endl;
}

void part2() {
    int steps = 40;
    unordered_map<string, char> rules;
    string poly_templ;
    getline(cin, poly_templ);
    string line;
    while (getline(cin, line)) {
        size_t pos = line.find('-');
        if (pos == string::npos) { continue; }
        rules[line.substr(0, pos - 1)] = line.back();
    }

    unordered_map<string, long long> pair_cnt;
    vector<long long> char_cnt(26);
    for (int i = 0; i < poly_templ.size() - 1; ++i) {
        ++char_cnt[poly_templ[i] - 'A'];
        pair_cnt[poly_templ.substr(i, 2)] += 1;
    }
    ++char_cnt[poly_templ.back() - 'A'];
    while (steps--) {
        unordered_map<string, long long> temp;
        for (auto& [str, times] : pair_cnt) {
            if (rules.count(str)) {
                char add = rules[str];
                char_cnt[add - 'A'] += times;
                temp[str.substr(0, 1) + add] += times;
                temp[add + str.substr(1)] += times;
            }
        }
        pair_cnt = temp;
    }
    long long min_cnt = LONG_MAX, max_cnt = 0;
    for (auto val : char_cnt) {
        if (!val) { continue; }
        min_cnt = min(min_cnt, val);
        max_cnt = max(max_cnt, val);
    }
    cout << max_cnt - min_cnt << endl;
}

int main(int argc, char** argv) {
    part2();
    return 0;
}