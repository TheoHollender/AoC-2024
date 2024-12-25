
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

struct State {
    int x, y, dir;

    bool operator< (const State &other) const {
        return x < other.x;
    }
};

vector<string> buffers;
pair<int, int> find_node (char c) {
    for (int y = 0; y < buffers.size(); y ++) {
        for (int x = 0; x < buffers[y].size(); x ++) {
            if (buffers[y][x] == c) {
                buffers[y][x] = '.';
                return { x, y };
            }
        }
    }
    return { - 1, - 1 };
}

vector<pair<State, int>> neighbours (State s, int ccost) {
    vector<pair<State, int>> res;
    int x = s.x;
    int y = s.y;
    res.push_back({ { x, y, (s.dir + 1) & 3 }, ccost + 1000 });
    res.push_back({ { x, y, (s.dir + 3) & 3 }, ccost + 1000 });

    int nx = x + dx[s.dir];
    int ny = y + dy[s.dir];
    if (buffers[ny][nx] == '.') {
        res.push_back({ { nx, ny, s.dir }, ccost + 1 });
    }

    return res;
}
vector<pair<State, int>> prev_neighbours (State s, int ccost) {
    vector<pair<State, int>> res;
    int x = s.x;
    int y = s.y;
    res.push_back({ { x, y, (s.dir + 1) & 3 }, ccost - 1000 });
    res.push_back({ { x, y, (s.dir + 3) & 3 }, ccost - 1000 });

    int nx = x - dx[s.dir];
    int ny = y - dy[s.dir];
    if (buffers[ny][nx] == '.') {
        res.push_back({ { nx, ny, s.dir }, ccost - 1 });
    }

    return res;
}

template <typename T>
using v = vector<T>;

pair<int, int> dijkstra(pair<int, int> start, pair<int, int> target) {
    State __default = { -1, -1, -1 };
    v<v<v<int>>> distances (buffers.size(), v<v<int>>( buffers[0].size(), v<int> (4, 1e18) ));
    v<v<v<State>>> parents (buffers.size(), v<v<State>>( buffers[0].size(), v<State> (4, __default) ));
    v<v<v<bool>>> used (buffers.size(), v<v<bool>>( buffers[0].size(), v<bool> (4, false) ));
    priority_queue<pair<int, State>> pairs;
    cout << start.first << " " << start.second << endl;
    cout << target.first << " " << target.second << endl;

    distances[start.second][start.first][1] = 0;
    pairs.push({ 0, { start.first, start.second, 1 } });

    vector<State> bck_prop;

    int min_dist = 1e18;

    while (pairs.size() != 0) {
        auto __curr = pairs.top();
        int dist = - __curr.first;
        State cr = __curr.second;
        cout << cr.x << " " << cr.y << " " << cr.dir << ": " << dist << endl;
        pairs.pop();
        if (cr.x == target.first && cr.y == target.second) {
            min_dist = min(min_dist, dist);
            if (dist == min_dist) {
                bck_prop.push_back( cr );
                used[cr.y][cr.x][cr.dir] = true;
            }
        }

        if (distances[cr.y][cr.x][cr.dir] != dist) continue ;
    
        for (auto nxt : neighbours( cr, dist )) {
            State nxts = nxt.first;
            int nxtc = nxt.second;

            if (distances[nxts.y][nxts.x][nxts.dir] <= nxtc) continue ;

            distances[nxts.y][nxts.x][nxts.dir] = nxtc;
            parents[nxts.y][nxts.x][nxts.dir] = nxts;
            pairs.push({ - nxtc, nxts });
        }
    }

    set<pair<int, int>> targets;
    for (int i = 0; i < bck_prop.size(); i ++) {
        State s = bck_prop[i];
        targets.insert({ s.x, s.y });
        int dist = distances[s.y][s.x][s.dir];
        cout << s.x << " " << s.y << " " << s.dir << endl;

        for (auto nxt : prev_neighbours(s, dist)) {
            State nxts = nxt.first;
            int nxtc = nxt.second;
            if (used[nxts.y][nxts.x][nxts.dir]) continue ;
            if (nxtc != distances[nxts.y][nxts.x][nxts.dir]) continue ;

            bck_prop.push_back(nxts);
            used[nxts.y][nxts.x][nxts.dir] = true;
        }
    }

    return { min_dist, targets.size() };
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    buffers = split(readlines(), "\n");
    pair<int, int> _start = find_node('S');
    pair<int, int> _end   = find_node('E');

    const auto res = dijkstra(_start, _end);
    res1 = res.first;
    res2 = res.second;

    cout << res1 << endl;
    cout << res2 << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
