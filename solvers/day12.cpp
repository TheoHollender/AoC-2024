
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

int R, C;

vector<string> grid;
vector<vector<bool>> used;
vector<pair<pair<int, int>, pair<int, int>>> path;

#define F(nx, ny) { if (nx < 0 || ny < 0 || nx >= R || ny >= C || grid[nx][ny] != c) { r2 ++; path.push_back({ { x, y }, { nx, ny } }); } else { dfs(nx, ny, c, r1, r2); } }
void dfs (int x, int y, char c, int &r1, int &r2) {
    if (used[x][y]) return ;
    r1 ++;
    used[x][y] = true;

    F(x + 1, y);
    F(x - 1, y);
    F(x, y + 1);
    F(x, y - 1);
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    grid = split(readlines(), "\n");
    R = grid.size();
    C = grid[0].size();
    used.resize(R, vector<bool>(C));

    for (int x = 0; x < R; x ++) {
        for (int y = 0; y < C; y ++) {
            int p = 0; int a = 0;
            dfs(x, y, grid[x][y], p, a);

            cout << x << " " << y << ": " << p << " " << a << endl;
            if (path.size() != 0) {
                set<pair<pair<int, int>, pair<int, int>>> epth;
                for (const auto u : path) epth.insert(u);

                int b = 0;
                for (auto u : path) {
                    int dx = u.second.first - u.first.first;
                    int dy = u.second.second - u.first.second;
                    cout << u.first.first << " " << u.first.second << " " << u.second.first << " " << u.second.second << "\n";

                    u.second.first  += dy;
                    u.first .first  += dy;
                    u.second.second += dx;
                    u.first .second += dx;
                    cout << u.first.first << " " << u.first.second << " " << u.second.first << " " << u.second.second << "\n";

                    if (epth.find(u) == epth.end()) {
                        cout << "SUCCESS\n";
                        b ++;
                    }
                }

                cout << "ON " << grid[x][y] << " " << a << " " << b << endl;

                path.clear();

                res2 += p * b;
            }

            res1 += p * a;
        }
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
