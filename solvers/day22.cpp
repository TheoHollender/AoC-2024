
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

int prune (int x) {
    return x % 16777216;
}
int compute (int x) {
    x = prune((x << 6) ^ x);
    x = prune((x >> 5) ^ x);
    return prune((x * 2048) ^ x);
}
int compute (int x, int n) {
    if (n == 0) return x;
    return compute(compute(x), n - 1);
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<int> values;
    while (1) {
        int x;
        cin >> x;
        if (cin.fail()) break ;

        values.push_back(x);
    }

    for (int u : values)
        res1 += compute(u, 2000);

    map<vector<int>, int> sequences;
    for (int u : values) {
        set<vector<int>> seen;
        int h = u;
        for (int r = 0; r + 4 < 2000; r ++) {
            h = compute(h);

            int r0 = h;           
            int r1 = compute(h);  
            int r2 = compute(r1); 
            int r3 = compute(r2); 
            int r4 = compute(r3); 
            r0 = r0 % 10;
            r1 = r1 % 10;
            r2 = r2 % 10;
            r3 = r3 % 10;
            r4 = r4 % 10;

            vector<int> u = {
                r1 - r0,
                r2 - r1,
                r3 - r2,
                r4 - r3
            };

            if (seen.find(u) != seen.end()) continue;
            seen.insert(u);
            sequences[u] = sequences[u] + r4;
            res2 = max(res2, sequences[u]);
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
