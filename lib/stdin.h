
#include <bits/stdc++.h>
#define int long long

using namespace std;

vector<int> readline () {
    vector<int> res;
    int x; cin >> x;
    res.push_back(x);
    if (cin.fail()) return { };

    while (cin.get() != '\n') {
        if (cin.fail()) break ;
        int x; cin >> x;
        res.push_back(x);
    }

    return res;
}
vector<vector<int>> read_grid () {
    vector<vector<int>> grid;
    while (!cin.fail()) {
        grid.push_back(readline());
    }
    while (grid.size() != 0 && grid.back().size() == 0) grid.pop_back();
    return grid;
}
string readlines () {
    string buffer;
    
    char c; c = cin.get();
    while (!cin.fail()) {
        buffer += c;
        c = cin.get();
    }

    return buffer;
}
