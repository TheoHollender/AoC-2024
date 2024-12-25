
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

vector<int> run_program (int rA, int rB, int rC, vector<int> program) {
    int pc = 0;

    vector<int> res;

    while (pc < program.size()) {
        int op = program[pc];
        int lt = program[pc + 1];
        int cm = program[pc + 1];

        if (lt == 4) cm = rA;
        else if (lt == 5) cm = rB;
        else if (lt == 6) cm = rC;
        pc += 2;

        if (op == 0) rA >>= cm;
        if (op == 1) rB ^= lt;
        if (op == 2) rB = cm & 7;
        if (op == 3 && rA != 0)
            pc = lt;
        if (op == 4) rB ^= rC;
        if (op == 5) {
            res.push_back(cm & 7);
        }
        if (op == 6) {
            rB = rA >> cm;
        }
        if (op == 7) {
            rC = rA >> cm;
        }
    }

    return res;
}

void show (vector<int> res) {
    bool first = true;
    for (int u: res) {
        if (!first) cout << ",";
        first = false;
        cout << u;
    }
    cout << endl;
}


bool matches (vector<int> &a, vector<int> &b, int offset) {
    if (a.size() != b.size()) return false;
    if (offset == a.size()) return true;
    return a[offset] == b[offset] && matches(a, b, offset + 1);
}
int solve (vector<int> program, int current = 0, int size = -2) {
    if (size == -2) size = program.size() - 1;
    if (size == -1) return current;
    for (int i = 0; i < 8; i ++) {
        int lcl = current + (i << (size * 3));

        vector<int> m = run_program(lcl, 0, 0, program);
        cout << lcl << ": "; show(m);
        if (matches(m, program, size)) {
            int nxt = solve(program, lcl, size - 1);
            if (nxt != -1) return nxt;
        }
    }

    return -1;
}
void solve () {
    int res2 = 0;

    int rA, rB, rC;

    string buffer; cin >> buffer; cin >> buffer; cin >> rA;
    cin >> buffer; cin >> buffer; cin >> rB;
    cin >> buffer; cin >> buffer; cin >> rC;
    cin >> buffer;

    vector<int> program = readline();

    vector<int> res1 = run_program(rA, rB, rC, program); show(res1);
    cout << solve(program) << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
