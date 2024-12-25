
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

bool startsWith (string &A, string &B, int off = 0) {
    if (off == B.size()) return true;
    if (off == A.size()) return false;

    return A[off] == B[off] && startsWith(A, B, off + 1);
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    string buffer;
    getline(cin, buffer);

    vector<string> values = split(buffer, ", ");

    while (1) {
        string line; cin >> line;
        if (cin.fail()) break ;

        vector<bool> reach(line.size() + 1, false);
        vector<int> cnt(line.size() + 1, 0);
        reach[0] = true;
        cnt[0] = 1;

        for (int i = 0; i < line.size(); i ++) {
            if (!reach[i]) continue ;

            string lmp = line.substr(i);

            for (string &bf : values) {
                if (startsWith(lmp, bf)) {
                    reach[i + bf.size()] = true;
                    cnt[i + bf.size()] += cnt[i];
                }
            }
        }

        if (reach.back()) res1 ++;
        res2 += cnt.back();
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
