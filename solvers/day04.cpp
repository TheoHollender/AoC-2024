
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

bool check_xmas (vector<string> &target, int x, int y, int dx, int dy) {
    return x + 3 * dx < target.size() && 0 <= x + 3 * dx &&
           y + 3 * dy < target[0].size() && 0 <= y + 3 * dy &&
           target[x][y] == 'X'
           && target[x + dx][y + dy] == 'M'
           && target[x + dx + dx][y + dy + dy] == 'A'
           && target[x + 3 * dx][y + 3 * dy] == 'S';  
}
#define E(a) if (a == 'M') {cm ++;} if (a == 'S') {cs ++;}
bool check_mas (vector<string> &target, int x, int y) {
    int cm = 0;
    int cs = 0;
    if (x < 1) return false;
    if (y < 1) return false;
    if (x + 1 >= target.size()) return false;
    if (y + 1 >= target[0].size()) return false;

    if (target[x][y] != 'A') return false;

    E (target[x + 1][y + 1])
    E (target[x - 1][y + 1])
    E (target[x + 1][y - 1])
    E (target[x - 1][y - 1])

    if (target[x + 1][y + 1] == target[x - 1][y - 1]) return false;

    return cm == 2 && cs == 2;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> buffers;
    while (!cin.fail()) {
        string b; cin >> b;
        if (cin.fail()) continue ;
        buffers.push_back(b);
    }

    for (int x = 0; x < buffers.size(); x ++) {
        for (int y = 0; y < buffers[0].size(); y ++) {
            if (check_xmas(buffers, x, y, 1, 0)) res1 ++;
            if (check_xmas(buffers, x, y, -1, 0)) res1 ++;
            if (check_xmas(buffers, x, y, 0, 1)) res1 ++;
            if (check_xmas(buffers, x, y, 0, -1)) res1 ++;
            if (check_xmas(buffers, x, y, 1, 1)) res1 ++;
            if (check_xmas(buffers, x, y, -1, 1)) res1 ++;
            if (check_xmas(buffers, x, y, 1, -1)) res1 ++;
            if (check_xmas(buffers, x, y, -1, -1)) res1 ++;

            if (check_mas(buffers, x, y)) res2 ++;
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
