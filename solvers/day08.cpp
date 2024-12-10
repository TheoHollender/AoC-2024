
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> grid = split(readlines(), "\n");
    vector<string> egrid(grid.size(), string(grid[0].size(), '.'));
    vector<string> mgrid(grid.size(), string(grid[0].size(), '.'));

    for (int x = 0; x < grid.size(); x ++) {
        for (int y = 0; y < grid[x].size(); y ++) {
            if (grid[x][y] == '.' || grid[x][y] == '#') continue ;
            for (int z = 0; z < grid.size(); z ++) {
                for (int w = 0; w < grid[z].size(); w ++) {
                    if (grid[z][w] != grid[x][y]) continue ;
                    if (z == x && y == w) {
                        if (mgrid[x][y] == '.') {
                            mgrid[x][y] = '#';
                            res2 ++;
                        }
                        continue ;
                    }
                    
                    int nx = x + (x - z);
                    int ny = y + (y - w);
                    if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size()) continue ;

                    if (egrid[nx][ny] == '.') {
                        egrid[nx][ny] = '#';
                        res1 ++;
                    }

                    nx = z;
                    ny = w;
                    int dx = (x - z);
                    int dy = (y - w);
                    //int dd = gcd(abs(dx), abs(dy));
                    //dx /= dd;
                    //dy /= dd;

                    //cout << dx << " " << dy << " " << dd <<endl;

                    while (!(nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size())) {
                        if (mgrid[nx][ny] == '.') {
                            mgrid[nx][ny] = '#';
                            res2 ++;
                        }
                        nx += dx;
                        ny += dy;
                    }
                }
            }
        }
    }
    for (auto l : grid) cout << l << endl;
    for (auto l : egrid) cout << l << endl;
    for (auto l : mgrid) cout << l << endl;

    cout << res1 << endl;
    cout << res2 << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
