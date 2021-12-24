#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

void correctRange(int& start, int& end) {
    start = (start < -50) ? -50 : start; 
    end = (end > 50) ? 50 : end;
}

void part1() {
    int x_s, x_e, y_s, y_e, z_s, z_e, res = 0;
    char *ops = NULL;
    size_t len = 0;
    ssize_t nread;
    int cubes[100 + 1][100 + 1][100 + 1];
    memset(cubes, 0, sizeof(cubes));
    while ((nread = getdelim(&ops, &len, ' ', stdin)) != -1) {
        scanf("x=%d..%d,y=%d..%d,z=%d..%d\n", &x_s, &x_e, &y_s, &y_e, &z_s, &z_e);
        int val = (nread == 3) ? 1 : 0;
        correctRange(x_s, x_e);
        correctRange(y_s, y_e);
        correctRange(z_s, z_e);
        for (int x = x_s; x <= x_e; ++x) {
            for (int y = y_s; y <= y_e; ++y) {
                for (int z = z_s; z <= z_e; ++z) {
                    cubes[x + 50][y + 50][z + 50] = val;
                }
            }
        }
    }
    for (int x = 0; x <= 100; ++x) {
        for (int y = 0; y <= 100; ++y) {
            for (int z = 0; z <= 100; ++z) {
                res += cubes[x][y][z];
            }
        }
    }
    free(ops);
    cout << res << endl;
}

struct Box {
    Box() {}
    Box(int f[], int t[]) {
        memcpy(from, f, sizeof(from));
        memcpy(to, t, sizeof(to));
    }
    long long vol() {
        return (long long)(to[0] - from[0] + 1) * (to[1] - from[1] + 1) * (to[2] - from[2] + 1);
    }
    int from[3];
    int to[3];
};

struct SigBox {
    SigBox() {}
    SigBox(Box& b, bool on) : box(b), on(on) {}
    SigBox(Box&& b, bool on) : box(b), on(on) {}
    Box box;
    bool on{false};

};

bool intersect(const Box& lhs, const Box& rhs, SigBox& sb) {
    int from[3];
    int to[3];
    for (int i = 0; i < 3; ++i) {
        from[i] = max(lhs.from[i], rhs.from[i]);
        to[i] = min(lhs.to[i], rhs.to[i]);
        if (from[i] > to[i]) { return false; }
    }
    sb = SigBox(Box(from, to), false);
    return true;
}

long long countCubes(vector<SigBox>& sboxes) {
    long long res = 0;
    for (auto& sb : sboxes) {
        if (sb.on) {
            res += sb.box.vol();
        } else {
            res -= sb.box.vol();
        }
    }
    return res;
}

void part2() {
    int from[3], to[3];
    char *ops = NULL;
    size_t len = 0;
    ssize_t nread;
    vector<SigBox> sboxes;
    while ((nread = getdelim(&ops, &len, ' ', stdin)) != -1) {
        scanf("x=%d..%d,y=%d..%d,z=%d..%d\n", from, to, from + 1, to + 1, from + 2, to + 2);
        Box b(from, to);
        int size = sboxes.size();
        for (int i = 0; i < size; ++i) {
            SigBox new_sb;
            if (intersect(b, sboxes[i].box, new_sb)) {
                new_sb.on = !sboxes[i].on;
                sboxes.push_back(new_sb);
            }
        }
        if (nread == 3) { sboxes.push_back(SigBox(b, true)); }
    }
    free(ops);
    cout << countCubes(sboxes) << endl;
}

int main(int argc, char** argv) {
    part2();
    return 0;
}