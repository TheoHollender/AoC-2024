
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

vector<string> split (string buffer,  string value) {
    int last = 0;
    vector<string> res;
    for (int offset = 0; offset < buffer.size(); offset ++) {
        if (buffer.substr(offset, value.size()) == value) {
            res.push_back( buffer.substr(last, offset - last) );
            offset += value.size() - 1;
            last = offset + 1;
        }
    }
    res.push_back(buffer.substr(last));
    return res;
}
template<typename T>
int index (vector<T> &values, T value) {
    for (int i = 0; i < values.size(); i ++)
        if (values[i] == value)
        return i ;
    return -1;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<string> lines = split(readlines(), "\n");
    
    vector<int> order;

    bool has_reached_end = false;
    for (auto line : lines) {
        if (has_reached_end) {
            vector<string> nums = split(line, ",");
            vector<int> vals;
            for (auto num : nums)
                vals.push_back( atoi(num.c_str()) );
            
            bool valid = true; int resl = 0;
            for (auto line : lines) {
                if (line == "") break ;
                vector<string> nums = split(line, "|");

                int first  = atoi(nums[0].c_str());
                int second = atoi(nums[1].c_str());

                for (int i = 0; i < vals.size(); i ++)
                    for (int j = i + 1; j < vals.size(); j ++)
                        if (vals[j] == first && vals[i] == second)
                            valid = false;
            }

            if (valid) res1 += vals[vals.size() >> 1];
            else {
                vector<int> newvals;
                
                while (newvals.size() != vals.size()) {
                    for (int i = 0; i < vals.size(); i ++) {
                        if (vals[i] == -1) continue ;
                        bool valid = true;
                        for (int j = 0; j < vals.size(); j ++) {
                            if (vals[j] == -1) continue ;

                            std::string m = to_string( vals[j] ) + "|" + to_string(vals[i]);
                            if (index(lines, m) == -1) continue ;

                            valid = false;
                        }
                        if (valid) {
                            newvals.push_back(vals[i]);
                            vals[i] = -1;
                            break ;
                        }
                    }
                }
                
                res2 += newvals[newvals.size() >> 1];
            }
        }

        if (line == "") has_reached_end = true;
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
