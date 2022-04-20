#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

void part1() {
    string line;
    int res = 0;
    unordered_map<char, char> st({{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}});
    unordered_map<char, int> points({{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}});
    while (getline(cin, line)) {
        stack<char> s;
        for (char c : line) {
            if (st.count(c)) {
                s.push(c);
            } else {
                if (s.empty() || st[s.top()] != c) {
                    res += points[c];
                    break;
                } else {
                    s.pop();
                }
            }
        }
    }
    cout << res << endl;
}

void part2() {
    string line;
    int res = 0;
    unordered_map<char, char> st({{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}});
    unordered_map<char, int> points({{')', 1}, {']', 2}, {'}', 3}, {'>', 4}});
    vector<unsigned long> incomplete_scores;
    while (getline(cin, line)) {
        stack<char> s;
        unsigned long score = 0;
        bool corrupt = false;
        for (char c : line) {
            if (st.count(c)) {
                s.push(c);
            } else {
                if (s.empty() || st[s.top()] != c) {
                    corrupt = true;
                    break;
                } else {
                    s.pop();
                }
            }
        }
        if (corrupt) { continue; }
        while (s.size()) {
            score = score * 5 + points[st[s.top()]];
            s.pop();
        }
        incomplete_scores.push_back(score);
    }
    sort(incomplete_scores.begin(), incomplete_scores.end());
    cout << incomplete_scores.size() << endl;
    cout << incomplete_scores[incomplete_scores.size() / 2] << endl;
}
int main(int argc, char** argv) {
    part2();
    return 0;
}