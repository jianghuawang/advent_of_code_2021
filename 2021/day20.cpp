#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;

const vector<int> direction{-1, 0, 1};
unordered_map<char, int> mp{{'#', 1}, {'.', 0}};

int getIdx(vector<string>& image, int i, int j, int time) {
    int res = 0;
    int offset = 8;
    for (int delta_i : direction) {
        for (int delta_j : direction) {
            int curr_i = i + delta_i;
            int curr_j = j + delta_j;
            if (curr_i < 0 || curr_i >= image.size() ||
                curr_j < 0 || curr_j >= image[0].size()) {
                res |= (time % 2 ? 1 : 0) << (offset--);
            } else {
                res |= mp[image[curr_i][curr_j]] << (offset--);
            }
        }
    }
    return res;
}

void initImage(vector<string>& image) {
    string line;
    image.push_back(string(102, '.'));
    while (getline(cin, line)) {
        if (line.size() == 1) { continue; }
        image.push_back("." + line.substr(0, 100) + ".");
    }
    image.push_back(string(102, '.'));
}

void enhanceImage(string& algo, vector<string>& image, int time) {
    vector<string> temp;
    int rows = image.size(), cols = image.size();
    char c = (time % 2) ? '.' : '#';
    temp.push_back(string(cols + 2, c));
    for (int i = 0; i < rows; ++i) {
        string curr;
        curr.push_back(c);
        for (int j = 0; j < cols; ++j) {
            int idx = getIdx(image, i, j, time);
            curr.push_back(algo[idx]);
        }
        curr.push_back(c);
        temp.push_back(curr);
    }
    temp.push_back(string(cols + 2, c));
    image = temp;
}

int countLight(vector<string>& image) {
    int res = 0;
    for (int i = 0; i < image.size(); ++i) {
        for (int j = 0; j < image[0].size(); ++j) {
            if (image[i][j] == '#') { ++res; }
        }
    }
    return res;
}
void part1() {
    int times = 2;
    string algo;
    getline(cin, algo);
    vector<string> image;
    initImage(image);

    int curr_time = 0;
    while (curr_time < times) {
        enhanceImage(algo, image, curr_time);
        ++curr_time;
    }
    cout << countLight(image) << endl;
}

void part2() {
    int times = 50;
    string algo;
    getline(cin, algo);
    vector<string> image;
    initImage(image);
    
    int curr_time = 0;
    while (curr_time < times) {
        enhanceImage(algo, image, curr_time);
        ++curr_time;
    }

    cout << countLight(image) << endl;
}

int main(int argc, char **argv) {
    clock_t start, end;
    start = clock();
    part2();
    end = clock();
    printf ("time spent: %0.8f sec\n",
            ((float) end - start)/CLOCKS_PER_SEC);
    return 0;
}