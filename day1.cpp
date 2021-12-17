#include <iostream>
#include <vector>

void part1() {
    int count = 2000;
    int prev = 0x7fffffff, curr, res = 0;
    while (count--) {
        std::cin >> curr;
        if (curr > prev) {
            ++res;
        }
        prev = curr;
    }
    std::cout << res << std::endl;
}

void part2() {
    int count = 2000, res = 0;
    std::vector<int> nums(2000); 
    for (int i = 0; i < count; ++i) {
        std::cin >> nums[i]; 
    }
    int prev = 0x7fffffff;
    int curr = 0;
    for (int i = 0; i < count; ++i) {
        curr += nums[i];
        if (i >= 2) {
            if (curr > prev) { ++res; }
            prev = curr;
            curr -= nums[i - 2];
        }
    }
    std::cout << res << std::endl;
}
int main(int argc, char **argv) {
    part2();
    return 0;
}