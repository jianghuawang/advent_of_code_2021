#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Number {
    Number() {}
    explicit Number(int val) : isInt(true), val(val) {}

    pair<Number*, Number*> p{nullptr, nullptr};
    int val{0};
    bool isInt{false};
};

void clean(Number *n) {
    if (n->isInt) {
        delete n;
        return;
    }
    clean(n->p.first);
    clean(n->p.second);
    delete n;
}

Number* copy(Number* rhs) {
    if (rhs->isInt) { 
        return new Number(rhs->val);
    }
    Number *n = new Number;
    n->p.first = copy(rhs->p.first); 
    n->p.second = copy(rhs->p.second);
    return n;
}

Number* parseNumber(string s, int& pos) {
    if (s[pos] >= '0' && s[pos] <= '9') {
        return new Number(s[pos] - '0');
    }
    Number *n = new Number;
    n->p.first = parseNumber(s, ++pos);
    ++pos;
    n->p.second = parseNumber(s, ++pos);
    ++pos;
    return n;
}

void printNumber(Number *n) {
    if (n->isInt) {
        cout << n->val; 
        return; 
    }
    cout << "[";
    printNumber(n->p.first);
    cout << ",";
    printNumber(n->p.second);
    cout << "]";
}

void printlnNumber(Number *n) { 
    printNumber(n);
    cout << endl;
}

void explode(Number *n, Number *p, int level, int*& leftMost, int& rightVal, bool& happened) {
    if (n->isInt) { 
        if (happened && rightVal > 0) { 
            n->val += rightVal;
            rightVal = -1;
        } else {
            leftMost = &(n->val);
        }
        return;
    }
    if (!happened && level >= 4) {
        if (leftMost) { (*leftMost) += n->p.first->val; };
        rightVal = n->p.second->val;
        Number *new_num = new Number(0);
        if (n == p->p.first) { p->p.first = new_num;}
        else { p->p.second = new_num; }
        happened = 1;
        clean(n);
        return;
    }
    explode(n->p.first, n, level + 1, leftMost, rightVal, happened);
    if (happened && rightVal < 0) { return; }
    explode(n->p.second, n, level + 1, leftMost, rightVal, happened);
}

bool split(Number *n, Number *p) {
    if (n->isInt) {
        if (n->val < 10) { return false; }
        Number *new_n = new Number;
        new_n->p.first = new Number(n->val / 2);
        new_n->p.second = new Number((n->val + 1) / 2);
        if (p->p.first == n) { p->p.first = new_n; }
        else { p->p.second = new_n; }
        clean(n);
        return true;
    }
    return split(n->p.first, n) || split(n->p.second, n);
}

void reduce(Number *n) {
    while (true) {
        int *left_most = nullptr;
        int right_val = -1;
        bool explode_res = false;
        explode(n, nullptr, 0, left_most, right_val, explode_res);
        if (explode_res) { continue; }

        bool split_res = split(n, nullptr);
        if (!explode_res && !split_res) { break; }
    }
}

Number* add(Number *lhs, Number *rhs) {
    Number *n = new Number;
    n->p.first = lhs;
    n->p.second = rhs;
    reduce(n);
    return n;
}

int calMagnitude(Number *n) {
    if (n->isInt) { return n->val; }
    return 3 * calMagitude(n->p.first) + 2 * calMagitude(n->p.second);
}

void part1() {
    string line;
    vector<Number*> nums;
    while (getline(cin, line)) {
        int pos = 0;
        nums.push_back(parseNumber(line, pos));
    }

    Number *lhs = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        Number *rhs = nums[i];
        lhs = add(lhs, rhs);
    }
    printlnNumber(lhs);
    cout << calMagnitude(lhs) << endl;
    clean(lhs);
}

void part2() {
    string line;
    vector<Number*> nums;
    while (getline(cin, line)) {
        int pos = 0;
        nums.push_back(parseNumber(line, pos));
    }
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < nums.size(); ++j) {
            if (i == j) { continue; }
            Number *lhs = copy(nums[i]);
            Number *rhs = copy(nums[j]);
            res = max(res, calMagnitude(add(lhs, rhs)));
            clean(lhs);
            clean(rhs);
        }
    }   
    for (auto* num : nums) {
        clean(num);
    }
    cout << res << endl;
}

int main(int argc, char** argv) {
    part2();
    return 0;
}