
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

pair<bool, int> compute (vector<string> grid, int sx, int sy, int dx, int dy) {
    int N = grid.size();
    int M = grid[0].size();
    set<pair<pair<int, int>, pair<int, int>>> visited;
    set<pair<int, int>> cells;

    bool first = true;
    int x = sx; int y = sy;
    int res = 0;
    while (visited.find({ { x, y }, {dx, dy} }) == visited.end()) {
        visited.insert({ { x, y }, { dx, dy } });
        if (grid[x][y] == '.') {
            grid[x][y] = 'X';
            res ++;
            cells.insert({ x, y });
        }
        int nx = x + dx;
        int ny = y + dy;

        bool valid = true;
        if (nx < 0 || ny < 0)  return { true, res };
        if (nx >= N || ny >= M) return { true, res };

        if (valid && (grid[nx][ny] == '#' || grid[nx][ny] == 'O')) valid = false;
        if (!valid) {
            int ndy = -dx;
            int ndx = dy;
            dx = ndx; dy = ndy;
            continue ;
        }

        x = nx;
        y = ny;
    }

    return { false, res + 1 };
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> grid = split(readlines(), "\n");

    int N = grid.size();
    int M = grid[0].size();

    int sx = 0;
    int sy = 0;
    int dx = - 1;
    int dy = 0;

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < M; j ++) {
            if (grid[i][j] == '^') {
                sx = i;
                sy = j;
            }
        }
    }

    cout << compute( grid, sx, sy, dx, dy ).second << endl;

    for (int ox = 0; ox < N; ox ++) {
        for (int oy = 0; oy < M; oy ++) {
            if (grid[ox][oy] == '#') continue ;

            cout << ox << " " << oy << endl;
        
            grid[ox][oy] = 'O';
            if (!compute(grid, sx, sy, dx, dy).first) res2 ++;
            grid[ox][oy] = '.';
        }
    }
    cout << res2 << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
