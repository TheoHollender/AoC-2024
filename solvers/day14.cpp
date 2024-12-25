
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

int width = 101;
int height = 103;
int cx = width >> 1;
int cy = height >> 1;

int simulate (int coordinate, int speed, int time, int boundary) {
    coordinate += speed * time;
    
    if (coordinate < 0) {
        coordinate  = - coordinate;
        coordinate %= boundary;

        coordinate = boundary - coordinate;
    }

    coordinate %= boundary;
    return coordinate;
}

struct Point {
    int x, y, vx, vy;
};

void simulate (vector<Point> &points) {
    for (Point & p : points) {
        p.x = simulate(p.x, p.vx, 1, width);
        p.y = simulate(p.y, p.vy, 1, height);
    }
}
void display (vector<Point> &points, int time) {
    vector<string> strings(height, string(width, ' '));
    for (Point & p : points) {
        strings[p.y][p.x] = '*';
    }

    cout << "============ " << time << " ============" << endl;
    for (auto s : strings) cout << s << endl;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    std::string buffer = readlines();
    cout << buffer << endl;
    const auto m = matches(buffer, {
        "p=%n,%n v=%n,%n"
    });

    int A[4] = { 0, 0, 0, 0 };
    vector<Point> points;
    for (auto d : m) {
        int x = d.revpath[3];
        int y = d.revpath[2];
        int vx = d.revpath[1];
        int vy = d.revpath[0];
        points.push_back({ x, y, vx, vy });

        int rx = simulate(x, vx, 100, width);
        int ry = simulate(y, vy, 100, height);

        if (rx == cx || ry == cy) continue ;

        int ax = rx < cx ? 0 : 2;
        int ay = ry < cy ? 0 : 1;
        A[ax + ay] ++;
    }

    res1 = A[0] * A[1] * A[2] * A[3];

    for (int i = 0; i < width * height; i ++) {
        display(points, i);
        simulate(points);
    }

    cout << res1 << endl;
    cout << res2 << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
