
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

struct Match {
    int type = 0;
    int offset;
    std::vector<int> revpath; // reversed args

    bool operator< (const Match &other) const {
        if (offset == other.offset) return type < other.type;
        return offset < other.offset;
    }
};

// custom regular expression language
// 
// mul(%n,%n)

std::pair<int, int> parse_int (std::string &buffer, int offset, int value = 0) {
    if (offset >= buffer.size()) return { buffer.size(), value };

    char c = buffer[offset];
    if (c == '-') {
        pair<int, int> e = parse_int(buffer, offset + 1);

        return { e.first, - e.second };
    }
    if (c < '0' || c > '9') return { offset, value };
    return parse_int(buffer, offset + 1, value * 10 + c - '0');
}

std::optional<Match> get_match (std::string &buffer, int offset, std::string &expr, int expr_off) {
    if (expr_off == expr.size()) {
        return { Match({ 0, offset, {} }) };
    }

    if (expr[expr_off] == '\\' || expr[expr_off] != '%') {
        char cchar = expr[expr_off] == '\\' ? expr[expr_off + 1] : expr[expr_off];
        int  cnext = expr[expr_off] == '\\' ? expr_off + 2 : expr_off + 1;

        if (cchar == buffer[offset]) {
            return get_match(buffer, offset + 1, expr, cnext);
        } else return {};
    }

    if (expr[expr_off] == '%') {
        if (expr[expr_off + 1] == 'n') {
            const auto iid = parse_int(buffer, offset);
            if (iid.first == offset) return {};

            std::optional<Match> mtch = get_match(buffer, iid.first, expr, expr_off + 2);
            
            if (mtch.has_value()) {
                Match v = mtch.value();
                v.revpath.push_back(iid.second);
                return v;
            } else return {};
        }
    }

    // did not recognize sequence
    return {};
}

std::vector<Match> matches (std::string &buffer, std::string &expr) {
    std::vector<Match> results;
    for (int i = 0; i < buffer.size(); i ++) {
        std::optional<Match> m = get_match(buffer, i, expr, 0);

        if (m.has_value())
            results.push_back(m.value());
    }

    return results;
}

std::vector<Match> matches (std::string &buffer, std::vector<std::string> expressions) {
    std::vector<Match> aresults;

    for (int eid = 0; eid < expressions.size(); eid ++) {
        std::vector<Match> eidms = matches(buffer, expressions[eid]);

        for (int i = 0; i < eidms.size(); i ++)
            eidms[i].type = eid;

        for (auto h : eidms) aresults.push_back(h);
    }

    sort(aresults.begin(), aresults.end());

    return aresults;
}