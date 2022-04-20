#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

struct Number {
    Number() {}
    explicit Number(int val) : isInt(true), val(val) {}

    vector<Number> nums;
    int val{0};
    bool isInt{false};
};

Number parseNumber(string s, int& pos) {
    if (s[pos] >= '0' && s[pos] <= '9') {
        return Number(s[pos] - '0');
    }
    Number n;
    n.nums.push_back(parseNumber(s, ++pos));
    ++pos;
    n.nums.push_back(parseNumber(s, ++pos));
    ++pos;
    return n;
}

void printNumber(Number& n) {
    if (n.isInt) {
        cout << n.val; 
        return;
    }
    cout << "[";
    printNumber(n.nums[0]);
    cout << ",";
    printNumber(n.nums[1]);
    cout << "]";
}

void printlnNumber(Number& n) { 
    printNumber(n);
    cout << endl;
}

struct Exploder {
    void explode(Number& n, int level) {
        if (n.isInt) { 
            if (happened && rightVal > 0) { 
                n.val += rightVal;
                rightVal = -1;
            } else {
                leftMost = &(n.val);
            }
            return;
        }
        if (!happened && level >= 4) {
            if (leftMost) { (*leftMost) += n.nums[0].val; }
            rightVal = n.nums[1].val;
            n.nums.clear();
            n.isInt = true;
            n.val = 0;
            happened = 1;
            return;
        }
        explode(n.nums[0], level + 1);
        if (happened && rightVal < 0) { return; }
        explode(n.nums[1], level + 1);
    }
    bool explode(Number& n) {
        explode(n, 0);
        return happened;
    }
    int* leftMost{nullptr}, rightVal{-1};
    bool happened{false};
};

struct Splitter {
    bool split(Number& n) {
        if (n.isInt) {
            if (n.val < 10) { return false; }
            n.nums.push_back(Number(n.val / 2));
            n.nums.push_back(Number((n.val + 1) / 2));
            n.isInt = false;
            n.val = 0;
            return true;
        }
        return split(n.nums[0]) || split(n.nums[1]);
    }
};

void reduce(Number& n) {
    while (true) {
        Exploder e;
        bool explode_res = e.explode(n);
        if (explode_res) { continue; }
        Splitter s;
        bool split_res = s.split(n);
        if (!explode_res && !split_res) { break; }
    }
}

Number add(Number& lhs, Number &rhs) {
    Number n;
    n.nums.push_back(lhs);
    n.nums.push_back(rhs);

    reduce(n);
    return n;
}

int calMagnitude(Number& n) {
    if (n.isInt) { return n.val; }
    return 3 * calMagnitude(n.nums[0]) + 2 * calMagnitude(n.nums[1]);
}

void part1() {
    string line;
    vector<Number> nums;
    while (getline(cin, line)) {
        int pos = 0;
        nums.push_back(parseNumber(line, pos));
    }

    Number lhs = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        Number& rhs = nums[i];
        lhs = add(lhs, rhs);
    }
    printlnNumber(lhs);
    cout << calMagnitude(lhs) << endl;
}

void part2() {
    string line;
    vector<Number> nums;
    while (getline(cin, line)) {
        int pos = 0;
        nums.push_back(parseNumber(line, pos));
    }
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            Number add_res = add(nums[i], nums[j]);
            res = max(res, calMagnitude(add_res));
            add_res = add(nums[j], nums[i]);
            res = max(res, calMagnitude(add_res));
        }
    }   

    cout << res << endl;
}

int main(int argc, char** argv) {
    clock_t start, end;
    start = clock();
    part2();
    end = clock();
    printf ("time spent: %0.8f sec\n",
            ((float) end - start)/CLOCKS_PER_SEC);
    return 0;
}