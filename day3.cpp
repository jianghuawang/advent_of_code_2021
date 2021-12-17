#include <string.h>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;

void part1() {
    string num, gamma_str, epsilon_str;
    int gamma = 0, epsilon = 0;
    int line_num = 0;
    int one_count[12];
    memset(one_count, 0, sizeof(one_count));
    while (getline(std::cin, num)) {
        ++line_num;
        for (int i = 0; i < num.length(); ++i) {
            one_count[i] += num[i] - '0';
        }        
    }
    int half = line_num / 2;
    for (int i = 0; i < 12; ++i) {
        if (one_count[i] > half) {
            gamma_str.push_back('1');
            epsilon_str.push_back('0');
        } else {
            gamma_str.push_back('0');
            epsilon_str.push_back('1');
        }
    }
    gamma = stoi(gamma_str, 0, 2);
    epsilon = stoi(epsilon_str, 0, 2);
    std::cout << gamma << ", " << epsilon << std::endl;
    std::cout << gamma * epsilon << std::endl;
}

int process(vector<string> input, int one_count, bool o2) {
    int curr_bit = 0;
    int zero_count = input.size() - one_count;
    char select;
    while (input.size() > 1 && curr_bit < 12) {
        vector<string> temp;
        if (o2) {
            select = '1' - ((one_count >= zero_count) ? 0 : 1);
        } else {
            select = '1' - ((one_count >= zero_count) ? 1 : 0);
        }
        int next_one_count = 0;
        for (auto& str : input) {
            if (str[curr_bit] == select) {
                temp.push_back(str);
                next_one_count += str[curr_bit + 1] - '0';
            }
        }
        input = temp;
        ++curr_bit;
        zero_count = temp.size() - next_one_count;
        one_count = next_one_count;
    }
    return stoi(input[0], 0, 2);
}

void part2() {
    string num;
    vector<string> reports;
    int line_num = 0;
    int first_one_count = 0;
    int first_zero_count = 0;
    while (getline(std::cin, num)) {
        ++line_num;
        first_one_count += num[0] - '0';
        reports.push_back(num);
    }
    int o2_gen_rating = process(reports, first_one_count, true);
    int co2_scrub_rating = process(reports, first_one_count, false);
    std::cout << o2_gen_rating << ", " << co2_scrub_rating << std::endl;
    std::cout << o2_gen_rating * co2_scrub_rating << std::endl;
}

int main() {
    // part1();
    part2();
    return 0;
}