
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

const int KN_A = 10;

const int KD_L = 0;
const int KD_R = 1;
const int KD_T = 2;
const int KD_D = 3;
const int KD_A = 4;

struct State {
    int kN = KN_A;
    int k1 = KD_A;
    int k2 = KD_A;
    bool operator< (const State &other) const {
        if (kN != other.kN) return kN < other.kN;
        if (k1 != other.k1) return k1 < other.k1;
        return k2 < other.k2;
    }
};

vector<vector<int>> grid_kD = {
    {   -1, KD_T, KD_A },
    { KD_L, KD_D, KD_R }
};
vector<vector<int>> grid_kN = {
    {   7,     8,    9 },
    {   4,     5,    6 },
    {   1,     2,    3 },
    {  -1,     0, KN_A }
};

int in_dir (vector<vector<int>> &keyboard, int src, int dir) {
    int x = -1;
    int y = -1;
    for (int sx = 0; sx < keyboard.size(); sx ++) {
        for (int sy = 0; sy < keyboard[sx].size(); sy ++) {
            if (keyboard[sx][sy] == src) {
                x = sx;
                y = sy;
            }
        }
    }
    if (x == -1) return -1;

    if (dir == KD_L) y --;
    if (dir == KD_R) y ++;
    if (dir == KD_T) x --;
    if (dir == KD_D) x ++;

    if (x < 0 || x >= keyboard.size()) return -1;
    if (y < 0 || y >= keyboard[x].size()) return -1;
    return keyboard[x][y];
}
vector<pair<State, int>> neighbours (pair<State, int> &_state, vector<int> &code) {
    State state = _state.first;
    int target  = code[_state.second];
    
    vector<pair<State, int>> res;
    if (state.k2 == KD_A) {
        if (state.k1 == KD_A) {
            if (target == state.kN)
                res.push_back({ state, _state.second + 1 });
        } else {
            int nkN = in_dir(grid_kN, state.kN, state.k1);
            if (nkN != -1)
                res.push_back({ { nkN, state.k1, state.k2 }, _state.second });
        }
    } else {
        int nk1 = in_dir(grid_kD, state.k1, state.k2);
        if (nk1 != -1) res.push_back({ { state.kN, nk1, state.k2 }, _state.second });
    }

    for (int dir = 0; dir < 4; dir ++) {
        int nk2 = in_dir(grid_kD, state.k2, dir);
        if (nk2 != -1) res.push_back({ { state.kN, state.k1, nk2 }, _state.second });
    }

    return res;
}
int distance (vector<int> code) {
    map<pair<State, int>, int> distances; 
    distances[{ { KN_A, KD_A, KD_A }, 0 }] = 0;

    queue<pair<State, int>> q;
    q.push({ { KN_A, KD_A, KD_A }, 0 });
    while (q.size() != 0) {
        pair<State, int> _state = q.front();
        q.pop();

        if (_state.second == code.size()) return distances[_state];
        const auto neigh = neighbours(_state, code);

        for (pair<State, int> nxt : neigh) {
            auto it = distances.find(nxt);
            if (it != distances.end()) continue ;

            distances[nxt] = distances[_state] + 1;
            q.push(nxt);
        }
    }

    return -1;
}

struct KeyBoardDMap {
    vector<vector<int>> pressTime;
};
KeyBoardDMap kbdmaphuman () {
    return { 
        {
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 }
        }
    };
}
int get_mx (vector<vector<int>> &grid) {
    int res = 0;
    for (auto u : grid)
        for (int j : u)
            res = max(res, j);
    return res;
}
vector<int> distances (KeyBoardDMap &mp, vector<vector<int>> &grid, int source) {
    // cout << "==== " << source << " ====" << endl;
    map<pair<int, int>, int> distances;
    distances[{ source, KD_A }] = 0;
    vector<int> result(get_mx(grid) + 1);

    priority_queue<pair<int, pair<int, int>>> pqueue;
    pqueue.push({ 0, { source, KD_A } });
    while (pqueue.size() != 0) {
        const auto curr = pqueue.top();
        int dist = -curr.first;
        int vnd0 = curr.second.first;
        int vnd1 = curr.second.second;
        pqueue.pop();

        if (vnd1 == KD_A && vnd0 != source) continue ;
        if (distances[{ vnd0, vnd1 }] != dist) continue ;

        for (int dir = 0; dir < 5; dir ++) {
            int nnd0 = dir == 5 ? vnd0 : in_dir(grid, vnd0, dir);
            if (nnd0 == -1) continue ;
            int nnd1 = dir;
            int next = dist + mp.pressTime[vnd1][nnd1];
            // cout << vnd0 << " " << vnd1 << " " << dist << " -> " << nnd0 << " " << nnd1 << " " << next << endl;
            pair<int, int> st = { nnd0, nnd1 };
            
            auto it = distances.find(st);
            int lccost = 1e18;
            if (it != distances.end()) lccost = (*it).second;

            if (next >= lccost) continue ;

            distances[st] = next;
            pqueue.push({ - next, st });
        }
    }

    for (int i = 0; i < result.size(); i ++) {
        if (i == source) {
            result[i] = 1;
        } else result[i] = distances[{ i, KD_A }];
    }
    
    return result;
}
KeyBoardDMap kbdmapingrid (KeyBoardDMap &map, vector<vector<int>> &grid) {
    KeyBoardDMap dmap;
    int mx = get_mx(grid);
    dmap.pressTime.resize(mx + 1);
    for (int src = 0; src <= mx; src ++)
        dmap.pressTime[src] = distances(map, grid, src);

    return dmap;
}

KeyBoardDMap kbdmap (int iteration) {
    KeyBoardDMap current = kbdmaphuman();

    for (int i = 0; i < iteration; i ++) {
        current = kbdmapingrid(current, grid_kD);
    }
    current = kbdmapingrid(current, grid_kN);
    return current;
}
int compute (vector<int> code, KeyBoardDMap &map) {
    int state = 10;
    int res = 0;
    for (int u : code) {
        res += map.pressTime[state][u];
        state = u;
    }
    return res;
}

int compute (string code) {
    vector<int> _code;
    for (char c : code) {
        if (c == 'A') _code.push_back(KN_A);
        else _code.push_back(c - '0');
    }

    int alpha = atoll( code.substr(0, 3).c_str() );
    return alpha * distance(_code);
}
int compute (string code, int iteration) {
    KeyBoardDMap map = kbdmap(iteration);
    vector<int> _code;
    for (char c : code) {
        if (c == 'A') _code.push_back(KN_A);
        else _code.push_back(c - '0');
    }

    int alpha = atoll( code.substr(0, 3).c_str() );
    return alpha * compute(_code, map);
}
void solve () {
    int res1 = 0;
    int res2 = 0;

    while (1) {
        string buffer;
        cin >> buffer;
        if (cin.fail()) break ;

        res1 += compute(buffer);
        res2 += compute(buffer, 25);
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
