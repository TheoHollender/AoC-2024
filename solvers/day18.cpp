
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

const int WIDTH = 71;
const int HEIGHT = 71;
const int NBYTES = 1024;

vector<vector<bool>> reachable(WIDTH, vector<bool>(HEIGHT, true));
int bfs () {
    vector<vector<int>> distances(WIDTH, vector<int>(HEIGHT, -1));
    queue<pair<int, int>> points;

    distances[0][0] = 0;
    points.push({ 0, 0 });

    #define F(nx, ny) if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && distances[nx][ny] == -1 && reachable[nx][ny]) { distances[nx][ny] = distances[x][y] + 1; points.push({ nx, ny }); }

    while (points.size() != 0) {
        int x = points.front().first;
        int y = points.front().second;
        points.pop();

        F(x + 1, y);
        F(x - 1, y);
        F(x, y + 1);
        F(x, y - 1);
    }

    return distances[WIDTH - 1][HEIGHT - 1];
}

int solve (int nbytes, vector<string> &lines) {
    reachable.clear();
    reachable.resize(WIDTH, vector<bool>(HEIGHT, true));
    for (int i = 0; i < nbytes; i ++) {
        string line = lines[i];
        vector<string> words = split(line, ",");
        int x = atoll(words[0].c_str());
        int y = atoll(words[1].c_str());

        reachable[x][y] = false;
    }
    return bfs();
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    string buffer = readlines();
    vector<string> lines = split(buffer, "\n");

    res1 = solve(NBYTES, lines);

    int a = 0;
    int b = lines.size();

    while (b -a > 1) {
        int m = (b + a) >> 1;

        if (solve(m, lines) == -1) b = m;
        else a = m;
    }

    cout << res1 << endl;
    cout << lines[a] << endl;
}

signed main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T = 1;
    if (MULTITEST) cin >> T;

    for (int t = 0; t < T; t ++) solve();
}
