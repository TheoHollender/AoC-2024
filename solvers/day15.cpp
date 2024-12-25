
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

int solve1 (vector<string> buffer, string moves) {
    int res1 = 0;
    for (char c : moves) {
        int dx = 0;
        int dy = 0;
        if (c == '<') dx = - 1;
        if (c == '>') dx = 1;
        if (c == '^') dy = - 1;
        if (c == 'v') dy = 1;
        if (dx == 0 && dy == 0) continue ;

        int sx = -1; int sy = -1;
        for (int x = 0; x < buffer[0].size(); x ++) {
            for (int y = 0; y < buffer.size(); y ++) {
                if (buffer[y][x] == '@') {
                    sx = x;
                    sy = y;
                    x = 1000;
                    break;
                }
            }
        }

        if (sx == -1) break ;
        
        int ex = -1;
        int ey = -1;
        bool valid = true;
        set<pair<int, int>> vpoints; vpoints.insert({ sx, sy });
        vector<pair<int, int>> move_points;
        vector<pair<int, int>> parent_pnts;
        move_points.push_back({ sx, sy });
        parent_pnts.push_back({ -1, -1 });

        for (int i = 0; valid && i < move_points.size(); i ++) {
            int x = move_points[i].first;
            int y = move_points[i].second;
            cout << "COMPUTING " << x << " " << y << endl;
            if (buffer[y][x] == '.') continue ;
            if (buffer[y][x] == '#') {
                valid = false;
                continue ;
            }

            int nx = x + dx;
            int ny = y + dy;
            if (vpoints.find({ nx, ny }) == vpoints.end()) {
                move_points.push_back({ nx, ny });
                parent_pnts.push_back({ x, y });
                vpoints.insert({ nx, ny });
            } else {
                for (int j = 0; j < move_points.size(); j ++) {
                    if (move_points[j] == make_pair( nx, ny )) {
                        parent_pnts[j] = { x, y };
                        break ;
                    }
                }
            }
            if (buffer[ny][nx] == '[' || buffer[ny][nx] == ']') {
                int vy = ny;
                int vx = buffer[ny][nx] == '[' ? nx + 1 : nx - 1;
                cout << "LCL " << nx << " " << ny << " " << vx << " " << vy << endl;

                if (vpoints.find({ vx, vy }) == vpoints.end()) {
                    move_points.push_back({ vx, vy });
                    parent_pnts.push_back({ -1, -1 });
                    vpoints.insert({ vx, vy });
                }
            }
        }

        if (!valid) continue ;

        for (int i = move_points.size() - 1; i >= 0; i --) {
            int x = move_points[i].first;
            int y = move_points[i].second;
            int px = parent_pnts[i].first;
            int py = parent_pnts[i].second;

            if (px == -1) buffer[y][x] = '.';
            else buffer[y][x] = buffer[py][px];
        }
        for (auto s : buffer) cout << s << endl;
    }

    for (int x = 0; x < buffer[0].size(); x ++) {
        for (int y = 0; y < buffer.size(); y ++) {
            if (buffer[y][x] != '[') continue ;

            res1 += 100 * y + x;
        }
    }
    return res1;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    string lines = readlines();
    vector<string> fs = split(lines, "\n\n");

    vector<string> buffer = split(fs[0], "\n");

    string moves = fs[1];

    for (string &s : buffer) {
        string m = s;
        s.resize(m.size() * 2, '.');
        for (int i = 0; i < m.size(); i ++) {
            s[i * 2] = m[i];
            s[i * 2 + 1] = m[i];
            if (m[i] == '@') {
                s[i * 2 + 1] = '.';
            }
            if (m[i] == 'O') {
                s[i * 2] = '[';
                s[i * 2 + 1] = ']';
            }
        }
    }
    res1 = solve1(buffer, moves);

    cout << res1 << endl;
    cout << res2 << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
