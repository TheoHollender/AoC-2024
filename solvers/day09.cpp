
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

vector<int> result1 (string &buffer) {

    vector<int> result;
    for (int i = 0; i < buffer.size(); i ++) {
        int cnt = buffer[i] - '0';
        for (int j = 0; j < cnt; j ++)
            result.push_back( i % 2 == 0 ? i >> 1 : -1 );
    }

    int left = 0;
    for (int right = result.size() - 1; right > left; right --) {
        while (left < right && result[left] != -1) left ++;
        if (left < right || result[right] == -1) {
            result[left] = result[right];
            result.pop_back();
        }
    }

    return result;
}
vector<int> result2 (string &buffer) {

    vector<pair<int, int>> blocks;
    for (int i = 0; i < buffer.size(); i ++)
        blocks.push_back({ buffer[i] - '0', i % 2 == 0 ? i >> 1 : -1 });

    for (int right = blocks.size() - 1; right >= 0; right --) {
        if (blocks[right].second == -1) continue ;
        for (int left = 0; left < right; left ++) {
            if (blocks[left].second != -1) continue ;
            if (left < right) {
                if (blocks[left].first >= blocks[right].first) {
                    blocks[left].first -= blocks[right].first;
                    auto bright = blocks[right];
                    blocks.insert( blocks.begin() + left, bright );
                    right ++;
                    blocks[right].second = -1;

                    break ;
                }
            }
        }

        for (int left = 0; left + 1 < blocks.size(); left ++) {
            if (blocks[left].second == blocks[left + 1].second) {
                blocks[left].first += blocks[left + 1].first;
                blocks.erase( blocks.begin() + (left + 1) );
                left --;
            }
        }
    }

    vector<int> result;
    for (auto u : blocks)
        for (int j = 0; j < u.first; j ++)
            result.push_back(u.second);
    for (int u : result) cout << u << " ";
    cout << endl;
    return result;
}
int checksum (vector<int> &result) {
    int res = 0;
    int i = 0;
    for (int u : result) {
        if (u != -1) {
            res += i * u;
        }
        i ++;
    }

    return res;
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    string buffer;
    cin >> buffer;

    vector<int> result_1 = result1(buffer);
    vector<int> result_2 = result2(buffer);

    cout << checksum(result_1) << endl;
    cout << checksum(result_2) << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
