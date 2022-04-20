#include <iostream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

inline int calVal(char c) {
    return (1 << (c - 'a'));
}

int calVal(string& s) {
    int res = 0;
    for (int i = 0; i < s.size(); ++i) {
        res |= calVal(s[i]);
    }
    return res;
}

int calTransVal(string& s, unordered_map<char, int>& mp) {
    int res = 0;
    for (auto c : s) {
        res |= mp[c];
    }
    return res;
}


void part1() {
    unordered_set<int> st({2, 4, 3, 7});
    string line;
    int res = 0;
    while (getline(std::cin, line)) {
        auto pos = line.find('|');
        istringstream is(line.substr(pos + 1));
        string digit;
        while (is >> digit) {
            if (st.count(digit.size())) {
                ++res;
            }
        }
    }
    cout << res << endl;
}

bool strCmp(string& lhs, string& rhs) {
    return lhs.size() < rhs.size();
}

void findMapping(vector<string>& patterns, vector<string>& cmp, unordered_map<int, int>& digitMapping) {
    unordered_map<char, int> mp;
    std::sort(patterns.begin(), patterns.end(), strCmp);
    
    // process 1
    digitMapping[calVal(patterns[0])] = 1;
    mp['c'] = calVal(patterns[0]);
    mp['f'] = mp['c'];
    // process 7
    digitMapping[calVal(patterns[1])] = 7;
    mp['a'] = calVal(patterns[1]) ^ mp['c']; // defined
    // process 4 
    digitMapping[calVal(patterns[2])] = 4;
    mp['b'] = calVal(patterns[2]) ^ mp['c'];
    mp['d'] = mp['b'];
    // process 2 3 5
    int five;
    for (int i = 3; i < 6; ++i) {
        int rep = calVal(patterns[i]);
        if ((rep & mp['b']) == mp['b']) {
            five = rep;
            break;
        }
    }
    digitMapping[five] = 5;
    // define f and c
    mp['f'] = mp['f'] & five; // defined
    mp['c'] = mp['c'] ^ mp['f']; // defined
    mp['g'] = five ^ mp['a'] ^ mp['b'] ^ mp['f']; // defined
    int two;
    int three;
    for (int i = 3; i < 6; ++i) {
        int rep = calVal(patterns[i]);
        if (rep == five) { continue; }
        else if (rep & mp['f']) { three = rep; }
        else { two = rep; }
    }
    digitMapping[two] = 2;
    digitMapping[three] = 3;
    mp['d'] &= mp['d'] & two; // defined
    mp['b'] ^= mp['d']; // defined
    mp['e'] = (two ^ three) ^ mp['f']; // defined
    digitMapping[calTransVal(cmp[0], mp)] = 0;
    digitMapping[calTransVal(cmp[6], mp)] = 6;
    digitMapping[calTransVal(cmp[9], mp)] = 9;
    digitMapping[calTransVal(cmp[8], mp)] = 8;
}

// elegant solution using set logic, seen from https://www.reddit.com/r/adventofcode/comments/rc0ucn/2021_day_8_part_2_my_logic_on_paper_based_on_sets/
void findMapping(vector<string>& patterns, unordered_map<int, int>& digitMapping) {
    std::sort(patterns.begin(), patterns.end(), strCmp);

    int seven = calVal(patterns[1]);
    int four = calVal(patterns[2]);
    int six;
    digitMapping[calVal(patterns[0])] = 1;
    digitMapping[seven] = 7;
    digitMapping[four] = 4;
    digitMapping[calVal(patterns.back())] = 8;
    // process 6 segment digits
    for (int i = 6; i < 9; ++i) {
        int res = calVal(patterns[i]);
        if ((four & res) == four) { 
            digitMapping[res] = 9; 
        } else if ((seven & res) == seven) { 
            digitMapping[res] = 0; 
        } else { 
            digitMapping[res] = 6;
            six = res;
        }
    }
    // process 5 segment digits
    for (int i = 3; i < 6; ++i) {
        int res = calVal(patterns[i]);
        if ((seven & res) == seven) { digitMapping[res] = 3; }
        else if ((res & six) == res) { digitMapping[res] = 5; }
        else { digitMapping[res] = 2; }
    }
}

void part2() {
    string line;
    vector<string> cmp({"abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg"});
    int res = 0;
    while (getline(std::cin, line)) {
        auto pos = line.find('|');
        istringstream is(line.substr(0, pos));
        vector<string> patterns;
        unordered_map<int, int> digit_mapping;
        string digit;
        while (is >> digit) {
            patterns.push_back(digit);
        }
        findMapping(patterns, digit_mapping);
        istringstream iss(line.substr(pos + 1));
        int entry = 0;
        while (iss >> digit) {
            int val = calVal(digit);
            entry = entry * 10 + digit_mapping[val];
        }
        res += entry;
    }
    cout << res << endl;
}

int main(int argc, char** argv) {
    part2();
    return 0;
}