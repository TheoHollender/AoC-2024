
#include <bits/stdc++.h>
#include "lib/stdin.h"
#include "lib/matches.h"
#include "lib/counter.h"
#include "lib/array.h"
#define int long long

#define MULTITEST false

using namespace std;

struct Claw {
    int dx, dy;
};
struct Machine {
    Claw c1, c2;
    int x, y;
};
int _quickest (Machine machine, int c1, int c2, int depth) {
    int res = 1e18;
      
    if (machine.x < 0 || machine.y < 0) return res;
    int rx = machine.x % machine.c2.dx;
    int ry = machine.y % machine.c2.dy;
    int vx = machine.x / machine.c2.dx;
    int vy = machine.y / machine.c2.dy;

    if (rx == 0 && ry == 0 && vx == vy) {
        cout << "Found for " << vx << "  " << c2 << " at " << depth << " " << c1 << endl;
        return c2 * vx;
    }
    
    machine.x -= machine.c1.dx;
    machine.y -= machine.c1.dy;
    res = min(res, c1 + _quickest(machine, c1, c2, depth + 1));
    return res;
}
int _quickest (Machine m) {
    int res1 = _quickest(m, 3, 1, 0);
    swap(m.c1, m.c2);
    int res2 = _quickest(m, 1, 3, 0);
    cout << res1 << " " << res2 << endl;
    int res  = min(res1, res2);
    return res;
}
int quickest (Machine machine, int c1, int c2) {
    int res = 1e18;
    int del = 0;

    int c1gcd = gcd(machine.c1.dx, machine.c1.dy);

    set<pair<int, int>> state;

    bool found00 = false;

    vector<pair<pair<int, int>, int>> dvd;
    bool use_dvd = false;

    while (1) {
        if (machine.x < 0 || machine.y < 0) return res;
        int rx = machine.x % machine.c2.dx;
        int ry = machine.y % machine.c2.dy;
        int vx = machine.x / machine.c2.dx;
        int vy = machine.y / machine.c2.dy;
        // cout << del << ": " << rx << " " << ry << " " << vx << " " << vy << endl;

        if (rx == 0 && ry == 0 && vx == vy) {
            return del + c2 * vx;
        }
        if (rx == 0 && ry == 0) {
            found00 = true;
            //cout << rx << " " << ry << " " << vx << " " << vy << ": " << machine.c1.dx * machine.c2.dy << " " << machine.c1.dy * machine.c2.dx << endl;

            dvd.push_back({ { vx, vy }, del });

            if (vx < vy && machine.c1.dx * machine.c2.dy > machine.c1.dy * machine.c2.dx) return res;
            if (vx > vy && machine.c1.dx * machine.c2.dy < machine.c1.dy * machine.c2.dx) return res;
            if (dvd.size() == 2) {
                use_dvd = true;
                break ;
            }
        }
        if (!found00) {
            if (state.find({ rx, ry }) != state.end()) return res;
            state.insert({ rx, ry });
        }

        machine.x -= machine.c1.dx;
        machine.y -= machine.c1.dy;
        del += c1;
    }

    if (use_dvd) {
        //cout << "USE DVD" << endl;
        if (machine.x < 0 || machine.y < 0) return res;
        int dvx = dvd[1].first.first - dvd[0].first.first;
        int dvy = dvd[1].first.second - dvd[0].first.second;
        int dvdel = dvd[1].second - dvd[0].second;

        int vx = machine.x / machine.c2.dx;
        int vy = machine.y / machine.c2.dy;
        if (vx < vy && machine.c1.dx * machine.c2.dy > machine.c1.dy * machine.c2.dx) return res;
        if (vx > vy && machine.c1.dx * machine.c2.dy < machine.c1.dy * machine.c2.dx) return res;

        if (vx > vy) {
            swap(vx, vy);
            swap(dvx, dvy);
        }

        int l = 0;
        int r = 1e12;
        while (r - l > 1) {
            int m = (l + r) >> 1;
            int mvx = vx + dvx * m;
            int mvy = vy + dvy * m;
            //cout << "AT " << m << " " << mvx << " " << mvy << endl;

            if (mvx > mvy) r = m;
            else if (mvx == mvy) {
                return del + c1 * m * dvdel + c2 * mvx;
            } else l = m;
        }
    }

    return res;
}
int quickest (Machine m) {
    int res1 = quickest(m, 3, 1);
    swap(m.c1, m.c2);
    int res2 = quickest(m, 1, 3);
    int res  = min(res1, res2);
    
    //swap(m.c1, m.c2);
    //int o = _quickest(m);
    //if (o != res) {
    //    cout << "Delta : " << o << " " << res << endl;
    //    cout << "Machine " << m.x << " " << m.y << ": " << m.c1.dx << " " << m.c1.dy << " " << m.c2.dx << " " << m.c2.dy << endl;
    //}
    if (res == 1e18) res = 0;
    return res;
}
int fquickest (Machine m) {
    m.x += 10000000000000LL;
    m.y += 10000000000000LL;
    return quickest(m);
}

optional<Claw> read_claw () {
    string buffer;
    getline(cin, buffer);
    if (cin.fail()) return {};

    for (int i = 0; i < buffer.size(); i ++) {
        if (buffer[i] == ',' || buffer[i] == '\n') {
            buffer[i] = '+';
        }
    }

    vector<string> strs = split(buffer, "+");

    return { {
        atoll( strs[1].c_str() ), atoll( strs[3].c_str() )
    } };
}
optional<Machine> read_machine () {
    optional<Claw> c1, c2;
    c1 = read_claw();
    c2 = read_claw();
    if (!(c1.has_value() && c2.has_value())) return {};

    string buffer;
    getline(cin, buffer);
    if (cin.fail()) return {};

    for (int i = 0; i < buffer.size(); i ++) {
        if (buffer[i] == ',' || buffer[i] == '\n') {
            buffer[i] = '=';
        }
    }

    vector<string> strs = split(buffer, "=");
    getline(cin, buffer);

    return { {
        c1.value(), c2.value(),
        atoll( strs[1].c_str() ), atoll( strs[3].c_str() )
    } };
}

void solve () {
    int res1 = 0;
    int res2 = 0;

    vector<Machine> machines;
    while (1) {
        optional<Machine> m = read_machine();
        if (!m.has_value()) break ;

        Machine ma = m.value();

        machines.push_back(ma);
    }

    for (Machine m : machines) {
        res1 += quickest(m);
        cout << fquickest(m) << endl;
        res2 += fquickest(m);
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
