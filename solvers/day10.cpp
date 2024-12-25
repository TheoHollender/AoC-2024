
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

void dfs (int x, int y, vector<string> &buffers, set<pair<int, int>> &v) {
    if (buffers[x][y] == '9') v.insert({ x, y });
    for (int dx = -1; dx <= 1; dx ++) {
        for (int dy = -1; dy <= 1; dy ++) {
            if (abs(dx) + abs(dy) != 1) continue ;

            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= buffers.size() || ny >= buffers[0].size()) continue ;

            if (buffers[nx][ny] == buffers[x][y] + 1)
                dfs(nx, ny, buffers, v);
        }
    }
}
int dfs2 (int x, int y, vector<string> &buffers) {
    if (buffers[x][y] == '9') return 1;
    int res = 0;
    for (int dx = -1; dx <= 1; dx ++) {
        for (int dy = -1; dy <= 1; dy ++) {
            if (abs(dx) + abs(dy) != 1) continue ;

            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= buffers.size() || ny >= buffers[0].size()) continue ;

            if (buffers[nx][ny] == buffers[x][y] + 1) {
                res += dfs2(nx, ny, buffers);
            }
        }
    }

    return res;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> buffers = split(readlines(), "\n");

    for (int i = 0; i < buffers.size(); i ++)
        for (int j = 0; j < buffers[i].size(); j ++) {
            set<pair<int, int>> v;
            if (buffers[i][j] == '0')
                dfs(i, j, buffers, v);
            res1 += v.size();
            if (buffers[i][j] == '0') {
                res2 += dfs2(i, j, buffers);
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
