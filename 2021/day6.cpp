#include <iostream>
#include <stdio.h>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

void part1() {
    int days = 80, val = 0;
    string num;
    queue<int> q;
    while (scanf("%d,", &val) == 1) {
        q.push(val);
    }
    while (days--) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            int age = q.front();
            q.pop();
            if (age) {
                q.push(age - 1);
            } else {
                q.push(6);
                q.push(8);
            }
        }
    }
    cout << q.size() << endl;
}

void part2() {
    int days = 256, val = 0;
    unsigned long long res = 0;
    vector<unsigned long long> arr(9);
    while (scanf("%d,", &val) == 1) {
        ++arr[val];
    }
    while (days--) {
        vector<unsigned long long> temp(9);
        for (int i = 0; i < arr.size(); ++i) {
            if (!i) {
                temp[6] += arr[i];
                temp[8] += arr[i];
            } else {
                temp[i - 1] += arr[i];
            }
        }
        arr = temp;
    }
    for (auto& val : arr) { res += val; }
    cout << res << endl;
}
int main() {
    part1();
    // part2();
    return 0;
}