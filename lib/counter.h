
#include <bits/stdc++.h>

template<typename Container>
struct _Counter {
    Container cont;

    int get (int x) {
        if (cont.find(x) == cont.end()) return 0;
        return cont[x];
    }
    void pop (int x) {
        cont.erase(x);
    }
    void insert (int x) {
        cont[x] = get(x) + 1;
    }
    void remove (int x) {
        int f = get(x);
        if (f <= 1) pop(x);
        else cont[x] = get(x) - 1;
    }
};

template<typename T>
using Counter = _Counter<std::unordered_map<T, int>>;
