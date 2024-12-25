
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

set<string> roads;
set<string> city;

bool has_road (string &c1, string &c2) {
    string r1 = c1 + "-" + c2;
    string r2 = c2 + "-" + c1;

    return roads.find(r1) != roads.end() || roads.find(r2) != roads.end();
}
bool is_in_clique (vector<string> &clique, string &city) {
    if (clique.size() != 0 && city <= clique.back()) return false;
    for (auto s : clique)
        if (!has_road(s, city))
            return false;
    return true;
}

vector<string> mclf;
void max_clique (vector<string> &cities) {
    bool first = true;
    if (cities.size() > mclf.size())
        mclf = cities;
    for (auto c : city) {
        if (is_in_clique(cities, c)) {
            cities.push_back(c);
            max_clique(cities);
            cities.pop_back();
        }
    }
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    while (1) {
        string buffer;
        cin >> buffer;
        if (cin.fail()) break ;

        vector<string> svs = split(buffer, "-");
        roads.insert(buffer);
        city.insert(svs[0]);
        city.insert(svs[1]);
    }

    for (auto c1 : city) {
        for (auto c2 : city) {
            if (c2 <= c1) continue ;
            if (!has_road(c1, c2)) continue ;
        
            for (auto c3 : city) {
                if (c3 <= c2) continue ;
                if (!has_road(c1, c3)) continue ;
                if (!has_road(c2, c3)) continue ;

                if (c1[0] == 't' || c2[0] == 't' || c3[0] == 't')
                    res1 ++;
            }
        }
    }

    vector<string> c;
    max_clique(c);

    cout << res1 << endl;
    
    bool first = true;
    for (string s : mclf) {
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
