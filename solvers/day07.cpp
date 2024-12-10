
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

int concatenate (int a, int b) {
    string _a = to_string(a);
    string _b = to_string(b);
    string _c = _a + _b;

    return atoll(_c.c_str());
}

bool can_solve (vector<int> &vals, int offset, int target, int curr = 0, bool conc = false) {
    if (curr > target) return false;
    if (offset == vals.size())
        return target == curr;

    if (curr != 0 && can_solve(vals, offset + 1, target, curr * vals[offset], conc))
        return true;
    if (conc && curr != 0 && can_solve(vals, offset + 1, target, concatenate(curr, vals[offset]), conc))
        return true;

    return can_solve(vals, offset + 1, target, curr + vals[offset], conc);
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> lines = split(readlines(), "\n");

    for (auto line : lines) {
        vector<string> buffers = split(line, ": ");

        int target = atoll(buffers[0].c_str());

        vector<string> nums = split(buffers[1], " ");
        vector<int> vals;
        for (auto num : nums)
            vals.push_back( atoll(num.c_str()) );
        
        if (can_solve(vals, 0, target)) {
            res1 += target;
        }
        if (can_solve(vals, 0, target, 0, true)) {
            res2 += target;
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
