
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

pair<int, int> find (vector<string> &buffers, char c) {
    for (int x = 0; x < buffers.size(); x ++)
        for (int y = 0; y < buffers.size(); y ++)
            if (buffers[x][y] == c)
                return { x, y };
    return { - 1, - 1 };
}
vector<vector<int>> bfs (int x, int y, vector<string> &buffers) {
    vector<vector<int>> distances(buffers.size(), vector<int>(buffers[0].size(), 1e9));

    distances[x][y] = 0;
    queue<pair<int, int>> points;
    points.push({ x, y });

    #define F(nx, ny) if (buffers[nx][ny] != '#' && distances[nx][ny] == 1e9) { distances[nx][ny] = distances[x][y] + 1; points.push({ nx, ny }); }
    while (points.size() != 0) {
        int x = points.front().first;
        int y = points.front().second;
        points.pop();

        F(x + 1, y);
        F(x - 1, y);
        F(x, y + 1);
        F(x, y - 1);
    }

    return distances;
}

vector<pair<int, int>> neighbours (vector<string> &map, int x, int y, int d = 1) {
    vector<pair<int, int>> result;
    for (int dx = -d; dx <= d; dx ++) {
        for (int dy = -d; dy <= d; dy ++) {
            if (abs(dx) + abs(dy) > d) continue ;
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= map.size() || ny < 0 || ny >= map[0].size()) continue ;
            if (map[nx][ny] != '#')
                result.push_back({ nx, ny });
        }
    }
    return result;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> mp = split(readlines(), "\n");

    const auto pE = find(mp, 'E');
    const auto dE = bfs(pE.first, pE.second, mp);
    const auto pS = find(mp, 'S');
    const auto dS = bfs(pS.first, pS.second, mp);

    int dist = dE[pS.first][pS.second];
    for (int x = 1; x + 1 < mp.size(); x ++) {
        for (int y = 1; y + 1 < mp[x].size(); y ++) {
            pair<int, int> p1 = { x, y };
            for (auto p2 : neighbours(mp, x, y, 2)) {
                int d1 = dS[p1.first][p1.second];
                int d2 = dE[p2.first][p2.second];

                int dT = d1 + d2 + abs(p1.first - p2.first) + abs(p1.second - p2.second);
                if (dT <= dist - 100) res1 ++;
            }
            for (auto p2 : neighbours(mp, x, y, 20)) {
                int d1 = dS[p1.first][p1.second];
                int d2 = dE[p2.first][p2.second];

                int dT = d1 + d2 + abs(p1.first - p2.first) + abs(p1.second - p2.second);
                if (dT <= dist - 100) res2 ++;
            }
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
