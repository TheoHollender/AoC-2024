
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#define int long long

#define MULTITEST false

using namespace std;

void solve () {
    string buffer = readlines();

    int res1 = 0;
    int res2 = 0;
    bool state = true;

    const auto matchs = matches(
        buffer,
        std::vector<string>({
            "mul(%n,%n)",
            "do()",
            "don't()"
        })
    );

    for (auto match : matchs) {
        if (match.type == 0) {
            int val = match.revpath[0] * match.revpath[1];
            res1 += val;
            if (state) res2 += val;
        } else state = match.type == 1;
    }

    cout << res1 << endl << res2 << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
