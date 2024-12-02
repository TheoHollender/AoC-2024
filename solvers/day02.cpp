#include <bits/stdc++.h>
#include "lib/array.h"
#include "lib/stdin.h"
#define int long long

#define MULTITEST false

using namespace std;

bool safe (vector<int> &v) {
    vector<int> d = uncumul(v);

    set<int> e;
    for (int u : d) {
        e.insert(u >> 31);
        if (u == 0) return false;
        if (abs(u) > 3) return false;
    }

    return e.size() == 1;
}
bool safeWithoutOne (vector<int> &v) {
    assert(v.size() > 1);
    vector<int> u;
    if (safe(v)) return true;

    for (int i = 0; i < v.size(); i ++) {
        u.clear();

        int j = 0;
        for (int e : v) if ((j ++) != i) u.push_back(e);

        if (safe(u))
            return true;
    }
    return false;
}

void solve () {
    vector<vector<int>> grid = read_grid();

    int res1 = 0;
    for (auto u : grid) {
        if (safe(u)) {
            res1 ++;
        }
    }
    
    int res2 = 0;
    for (auto u : grid) {
        if (safeWithoutOne(u)) {
            res2 ++;
        }
    }
    
    cout << res2 << "\n";
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}