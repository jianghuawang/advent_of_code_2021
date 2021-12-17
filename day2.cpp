#include <iostream>
#include <string>

using std::string;

void part1() {
    int hori = 0, vert = 0;
    string command, op;
    int val = 0;
    while (getline(std::cin, command)) {
        std::size_t found = command.find(' ');
        if (found == string::npos) { break; }
        op = command.substr(0, found);
        val = stoi(command.substr(found + 1));
        if (op == "forward") { 
            hori += val;
        } else if (op == "down") {
            vert += val;
        } else {
            vert -= val;
        }
    }
    std::cout << "horizontal = " << hori << ", vertical = " << vert << std::endl;
    std::cout << hori * vert << std::endl;
}

void part2() {
    int hori = 0, vert = 0, aim = 0;
    string command, op;
    int val = 0;
    while (getline(std::cin, command)) {
        std::size_t found = command.find(' ');
        if (found == string::npos) { break; }
        op = command.substr(0, found);
        val = stoi(command.substr(found + 1));
        if (op == "forward") { 
            hori += val;
            vert += val * aim;
        } else if (op == "down") {
            aim += val;
        } else {
            aim -= val;
        }
    }
    std::cout << "horizontal = " << hori << ", vertical = " << vert << std::endl;
    std::cout << hori * vert << std::endl;
}
int main() {
    part2();
    return 0;
}