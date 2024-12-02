
#include "lib/counter.h"
#include <bits/stdc++.h>
#define int long long

#define MULTITEST false

using namespace std;

Counter<int> c;

void solve () {
    vector<int> xs;
    vector<int> ys;

    while (1) {
        int x, y;
        cin >> x >> y;

        if (cin.fail()) break ;

        xs.push_back(x);
        ys.push_back(y);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    int res = 0;
    for (int i = 0; i < xs.size(); i ++) res += abs(xs[i] - ys[i]);

    cout << res << "\n";
    
    for (int u : ys) c.insert(u);

    int res2 = 0;
    for (int u : xs)
        res2 += u * c.get(u);

    cout << res2 << "\n";
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
