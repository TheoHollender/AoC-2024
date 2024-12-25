
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

struct CMap {
    map<string, int> counter;

    int get (string &x) {
        auto it = counter.find(x);
        if (it == counter.end()) return 0;

        return (*it).second;
    }
    void insert (string x, int y) {
        counter[x] = get(x) + y;
    }
    int size () {
        int res = 0;
        for (auto v : counter) res += v.second;
        return res;
    }
};

vector<string> advance (vector<string> strings) {
    vector<string> result;

    for (string & s : strings) {
        if (s == "0") {
            result.push_back("1");
        } else if (s.size() % 2 == 0) {
            int rm = s.size() >> 1;

            result.push_back(to_string(atoll(s.substr(0, rm).c_str())));
            result.push_back(to_string(atoll(s.substr(rm).c_str())));
        } else {
            int v = atoll(s.c_str());

            result.push_back(to_string(v * 2024));
        }
    }

    return result;
}
CMap advance (CMap strings) {
    CMap result;

    for (auto v : strings.counter) {
        string s = v.first;
        if (s == "0") {
            result.insert("1", v.second);
        } else if (s.size() % 2 == 0) {
            int rm = s.size() >> 1;

            result.insert(to_string(atoll(s.substr(0, rm).c_str())), v.second);
            result.insert(to_string(atoll(s.substr(rm).c_str())), v.second);
        } else {
            int u = atoll(s.c_str());

            result.insert(to_string(u * 2024), v.second);
        }
    }

    return result;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> buffers = split(readlines(), " ");
    CMap mp;
    for (string s : buffers) mp.insert(s, 1);
    for (int i = 0; i < 25; i ++) {
        buffers = advance(buffers);
    }
    for (int i = 0; i < 75; i ++) {
        mp = advance(mp);
    }

    cout << buffers.size() << endl;
    cout << mp.size() << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
