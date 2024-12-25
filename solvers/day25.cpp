
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

using b = bitset<35>;

optional<b> read () {
    b h;
    for (int y = 0; y < 7; y ++) {
        string bf;
        cin >> bf;
        if (cin.fail()) return {};
    
        for (int x = 0; x < 5; x ++)
            h[y * 5 + x] = bf[x] == '#';
    }

    return h;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<b> R;
    while (1) {
        const auto e = read();
        if (e.has_value()) {
            R.push_back(e.value());
        } else break ;
    }

    for (auto a : R)
        for (auto b : R)
            if (!((a & b).any()))
                res1 ++;

    cout << (res1 >> 1) << endl;
    cout << res2 << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
