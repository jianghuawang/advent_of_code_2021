#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void dfs(unordered_map<string, unordered_set<string>>& adjList,
        unordered_set<string> visited, int& res, const string& node, bool twice) {
    if (node == "end") {
        ++res;
        return;
    }
    if (node[0] >= 'a' && node[0] <= 'z') {
        visited.insert(node);
    }
    for (auto& neighbor : adjList[node]) { 
        if (!visited.count(neighbor)) {
            dfs(adjList, visited, res, neighbor, twice);
        } else if (neighbor != "start" && twice) {
            dfs(adjList, visited, res, neighbor, false);
        }
    }
}

void part1() {
    unordered_map<string, unordered_set<string>> adj_list;
    unordered_set<string> visited;
    string line;
    int res = 0;
    while (getline(cin, line)) {
        size_t pos = line.find('-');
        string st = line.substr(0, pos);
        string end = line.substr(pos + 1);
        adj_list[st].insert(end);
        adj_list[end].insert(st);
    }
    dfs(adj_list, visited, res, "start", false);
    cout << res << endl;
}

void part2() {
    unordered_map<string, unordered_set<string>> adj_list;
    unordered_set<string> visited;
    string line;
    int res = 0;
    while (getline(cin, line)) {
        size_t pos = line.find('-');
        string st = line.substr(0, pos);
        string end = line.substr(pos + 1);
        adj_list[st].insert(end);
        adj_list[end].insert(st);
    }
    dfs(adj_list, visited, res, "start", true);
    cout << res << endl;
}

int main(int argc, char** argv) {
    part2();
    return 0;
}