#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

/*
  Initial solution for part1. Work perfectly, but I find that it is more compact to combine these
  functions into one function. The current solution uses the same idea. 
*/

// void determineType(const std::string& binary_code, int& pos, int& res);

// void parseLiteral(const std::string& binary_code, int& pos) {
//     while (binary_code[pos] == '1') {
//             pos += 5;
//         }
//     pos += 5;
// }

// void parseOperatorMode0(const std::string& binary_code, int& pos, int& res) {
//     int total_len = stoi(binary_code.substr(pos, 15), 0, 2);
//     pos += 15;
//     int curr = pos;
//     while ((pos - curr) < total_len) {
//         determineType(binary_code, pos, res);
//     }
// }

// void parseOperatorMode1(const std::string& binary_code, int& pos, int& res) {
//     int sub_num = stoi(binary_code.substr(pos, 11), 0, 2);
//     pos += 11;
//     int cnt = 0;
//     while (cnt < sub_num) {
//         determineType(binary_code, pos, res);
//         ++cnt;
//     }   
// }

// void determineType(const std::string& binary_code, int& pos, int& res) {
//     int ver_num = stoi(binary_code.substr(pos, 3), 0, 2);
//     pos += 3;
//     res += ver_num;
//     int type = stoi(binary_code.substr(pos, 3), 0, 2);
//     pos += 3;
//     if (type == 4) {
//         parseLiteral(binary_code, pos);
//     } else {
//         char length_type = binary_code[pos++];
//         if (length_type == '0') {
//             parseOperatorMode0(binary_code, pos, res);
//         } else {
//             parseOperatorMode1(binary_code, pos, res);
//         }
//     }
// }

// spend a lot of time on part1, do not notice that the whole input contains a single packets!!
void parsePacket(const string& binary_code, int& pos, int& res) {
    int ver_num = stoi(binary_code.substr(pos, 3), 0, 2);
    pos += 3;
    res += ver_num;
    int type = stoi(binary_code.substr(pos, 3), 0, 2);
    pos += 3;
    if (type == 4) { 
        while (binary_code[pos] == '1') {
            pos += 5;
        }
        pos += 5;
    } else {
        char length_type = binary_code[pos++];
        if (length_type == '0') {
            int total_len = stoi(binary_code.substr(pos, 15), 0, 2);
            pos += 15;
            int curr = pos;
            while ((pos - curr) < total_len) {
                parsePacket(binary_code, pos, res);
            }
        } else {
            int sub_num = stoi(binary_code.substr(pos, 11), 0, 2);
            pos += 11;
            int cnt = 0;
            while (cnt < sub_num) {
                parsePacket(binary_code, pos, res);
                ++cnt;
            }
        }
    }
    return;
}

void part1() {
    unordered_map<char, string> mp({{'0', "0000"},
                                    {'1', "0001"},
                                    {'2', "0010"},
                                    {'3', "0011"},
                                    {'4', "0100"},
                                    {'5', "0101"},
                                    {'6', "0110"},
                                    {'7', "0111"},
                                    {'8', "1000"},
                                    {'9', "1001"},
                                    {'A', "1010"},
                                    {'B', "1011"},
                                    {'C', "1100"},
                                    {'D', "1101"},
                                    {'E', "1110"},
                                    {'F', "1111"}});    
    string line, binary_code;
    int res = 0, pos = 0;
    getline(std::cin, line);
    for (auto c : line) {
        binary_code += mp[c];
    }
    // determineType(binary_code, pos, res);
    parsePacket(binary_code, pos, res);
    cout << res << endl;
}

void processPacket(long long operand, int type, long long& val, long long prevVal) {
    switch (type) {
        case 0:
            val += operand;
            break;
        case 1:
            val = (prevVal < 0) ? 1 : val;
            val *= operand;
            break;
        case 2:
            val = (prevVal < 0) ? 0x7fffffff : val;
            val = min(val, operand);
            break;
        case 3:
            val = (prevVal < 0) ? 0 : val;
            val = max(val, operand);
            break;
        case 5:
            val = (prevVal < 0) ? operand : prevVal > operand;
            break;
        case 6:
            val = (prevVal < 0) ? operand : prevVal < operand;
            break;
        case 7:
            val = (prevVal < 0) ? operand : prevVal == operand;
            break;
        default:
            cout << "no matching type" << endl;
    }
}


long long parsePacket(const string& binary_code, int& pos) {
    int ver_num = stoi(binary_code.substr(pos, 3), 0, 2);
    pos += 3;
    int type = stoi(binary_code.substr(pos, 3), 0, 2);
    pos += 3;
    long long val = 0;
    if (type == 4) { 
        string string_val;
        while (binary_code[pos] == '1') {
            string_val += binary_code.substr(pos + 1, 4);
            pos += 5;
        }
        string_val += binary_code.substr(pos + 1, 4);
        pos += 5;
        val = stol(string_val, 0, 2);
    } else {
        char length_type = binary_code[pos++];
        if (length_type == '0') {
            int total_len = stoi(binary_code.substr(pos, 15), 0, 2);
            pos += 15;
            int curr = pos;
            long long prev_val = -1;
            long long curr_val = 0;
            while ((pos - curr) < total_len) {
                curr_val = parsePacket(binary_code, pos);
                processPacket(curr_val, type, val, prev_val);
                prev_val = curr_val;
            }
        } else if (length_type == '1') {
            int sub_num = stoi(binary_code.substr(pos, 11), 0, 2);
            pos += 11;
            int cnt = 0;
            long long prev_val = -1;
            long long curr_val = 0;
            while (cnt < sub_num) {
                curr_val = parsePacket(binary_code, pos);
                processPacket(curr_val, type, val, prev_val);
                prev_val = curr_val;
                ++cnt;
            }
        }
    }
    return val;
}

void part2() {
    unordered_map<char, string> mp({{'0', "0000"},
                                    {'1', "0001"},
                                    {'2', "0010"},
                                    {'3', "0011"},
                                    {'4', "0100"},
                                    {'5', "0101"},
                                    {'6', "0110"},
                                    {'7', "0111"},
                                    {'8', "1000"},
                                    {'9', "1001"},
                                    {'A', "1010"},
                                    {'B', "1011"},
                                    {'C', "1100"},
                                    {'D', "1101"},
                                    {'E', "1110"},
                                    {'F', "1111"}});    
    string line, binary_code;
    int pos = 0;
    getline(std::cin, line);
    for (auto c : line) {
        binary_code += mp[c];
    }
    cout << parsePacket(binary_code, pos) << endl;
}

int main(int argc, char** argv) {
    part2();
    return 0;
}