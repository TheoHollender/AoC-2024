
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

#define FIXED 0
#define AND 1
#define OR 2
#define XOR 3

struct Gate {
    int type;
    string p1, p2;
    bool v, c;
    string line;

    bool isValid = false;
};

bool computes_sum (map<string, Gate> &gates, int r, bool ep) {
    int x = 0;
    int y = 0;
    for (auto u : gates) {
        Gate &g = gates[u.first];
        if (g.type == FIXED) {
            string line = g.line;
            if ((line[0] == 'x' || line[0] == 'y') && line[3] == ':') {
                g.c = atoll(line.substr(1, 2).c_str()) <= r;
                if (line[0] == 'x' && g.c) x += (1LL << atoll(line.substr(1, 2).c_str())) * g.v;
                if (line[0] == 'y' && g.c) y += (1LL << atoll(line.substr(1, 2).c_str())) * g.v;
            }
        } else g.c = false;
    }

    while (1) {
        bool found = false;
        for (auto &u : gates) {
            Gate & g = gates[u.first];

            if (g.type == FIXED || g.c) continue ;

            Gate r1 = gates[g.p1];
            Gate r2 = gates[g.p2];
            if (!r1.c || !r2.c) continue ;

            if (g.type == XOR) g.v = r1.v ^  r2.v;
            if (g.type == OR)  g.v = r1.v || r2.v;
            if (g.type == AND) g.v = r1.v && r2.v;
            g.c = true;
            found = true;
        }
        if (!found) break ;
    }

    int z = 0;
    for (auto u : gates) {
        string name = u.first;
        if (u.second.c) {
            if (name[0] == 'z') z += u.second.v * (1LL << atoll(name.substr(1).c_str()));
            if (name[0] == 'z' && atoll(name.substr(1).c_str()) > r) {
                return false;
            }
        }
        if (name[0] == 'z' && atoll(name.substr(1, 2).c_str()) <= r && !u.second.c) {
            return false;
        }
    }

    if (((x + y) & ((1LL << (r + 1)) - 1LL)) != z) {
        return false;
    }
    if (ep) {
        for (auto g: gates) {
            if (!g.second.c) continue ;
            gates[g.first].isValid = true;
        }
    }
    return true;
}

void put_random (map<string, Gate> &gates) {
    for (auto g : gates) {
        Gate &f = gates[g.first];

        if (f.type == FIXED)
            f.v = rand() % 2 == 1;
    }
}
bool csst (map<string, Gate> &gates, int r) {
    const int ITER = 64;
    for (int i = 0; i < ITER; i ++) {
        put_random(gates);
        if (!computes_sum(gates, r, i + 1 == ITER)) return false;
    }
    return true;
}
optional<pair<set<string>, map<string, Gate>>> find_repair (map<string, Gate> gates, int r) {
    if (r >= 44) return { { {}, gates } };
    if (csst(gates, r)) return find_repair(gates, r + 1);
    vector<string> invalid;
    vector<string> einvalid;
    for (auto g : gates)
        if (g.second.c && !g.second.isValid && g.second.type != FIXED)
            invalid.push_back(g.first);
    for (auto g : gates)
        if (!g.second.isValid && g.second.type != FIXED)
            einvalid.push_back(g.first);
    vector<vector<string>> order = { invalid, einvalid };

    for (auto ev : order) {
        for (auto s1 : invalid) {
            for (auto s2 : ev) {
                map<string, Gate> new_gates = gates;
                swap(new_gates[s1], new_gates[s2]);

                if (csst(new_gates, r)) {
                    const auto res = find_repair(new_gates, r + 1);
                    if (!res.has_value()) continue ;

                    const auto v = res.value();
                    set<string> s = v.first;
                
                    s.insert(s1);
                    s.insert(s2);
                    return { { s, v.second } };
                }
            }
        }
    }

    return {};
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    map<string, Gate> gates;

    while (1) {
        string line;
        getline(cin, line);
        if (line == "") break ;

        vector<string> sp = split(line, ": ");

        gates[sp[0]] = { FIXED, "", "", sp[1] == "1", true, line };
    }

    int cN = 0;

    while (1) {
        string line;
        getline(cin, line);
        if (cin.fail()) break ;

        vector<string> sp = split(line, " -> ");
        vector<string> par = split(sp[0], " ");

        int type;
        if (par[1] == "XOR") type = XOR;
        if (par[1] == "OR")  type = OR;
        if (par[1] == "AND") type = AND;

        gates[sp[1]] = { type, par[0], par[2], false, false, line };
        cN ++;
    }

    while (cN) {
        for (auto &u : gates) {
            Gate & g = gates[u.first];

            if (g.type == FIXED || g.c) continue ;

            Gate r1 = gates[g.p1];
            Gate r2 = gates[g.p2];
            if (!r1.c || !r2.c) continue ;

            if (g.type == XOR) g.v = r1.v ^  r2.v;
            if (g.type == OR)  g.v = r1.v || r2.v;
            if (g.type == AND) g.v = r1.v && r2.v;
            g.c = true;
            cN --;
        }
    }

    for (int i = 0; ; i ++) {
        string s = "z";
        if (i < 10) s += "0";
        s += to_string(i);

        auto it = gates.find(s);
        if (it == gates.end()) break ;

        res1 += (1LL << i) * ((*it).second.v);
    }

    for (int r = 0; r < 45; r ++) {
        string s = "x";
        if (r < 10) s += "0";
        s += to_string(r);
        string s1 = "y";
        if (r < 10) s1 += "0";
        s1 += to_string(r);

        int h = (rand() % 3) + 1;
        gates[s].v = (h & 1) == 1;
        gates[s1].v = (h & 2) == 2; 
    }
    int falser = 0;
    const auto res = find_repair(gates, 0);
    set<string> swaps = res.value().first; 

    cout << res1 << endl;
    bool first = true;
    for (auto s : swaps) {
        if (!first) cout << ",";
        first = false;
        cout << s;
    }
    cout << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
