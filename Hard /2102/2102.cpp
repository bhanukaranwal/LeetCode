#include <queue>
#include <string>
#include <vector>
using namespace std;

// For left: min-heap (i best, i-th best at top)
struct Loc {
    int score;
    string name;
    Loc(int s, string n) : score(s), name(n) {}
    // Lower score first, then lex greater name first
    bool operator<(const Loc& o) const {
        if (score != o.score) return score > o.score;
        return name < o.name;
    }
};

// For right: max-heap (rest, best at top)
struct MaxLoc {
    int score;
    string name;
    MaxLoc(int s, string n) : score(s), name(n) {}
    // Higher score first, then lex smaller name first
    bool operator<(const MaxLoc& o) const {
        if (score != o.score) return score < o.score;
        return name > o.name;
    }
};

class SORTracker {
    priority_queue<Loc> left; // i best locations, i-th best at top
    priority_queue<MaxLoc> right; // rest
    int cnt = 0;
public:
    SORTracker() {}

    void add(string name, int score) {
        // Always push to left
        left.emplace(score, name);
        // If left's top is worse than right's top, swap them
        if (!right.empty() && (right.top().score > left.top().score ||
            (right.top().score == left.top().score && right.top().name < left.top().name))) {
            auto l = left.top(); left.pop();
            auto r = right.top(); right.pop();
            left.emplace(r.score, r.name);
            right.emplace(l.score, l.name);
        }
        // Maintain: left.size() == cnt
        if ((int)left.size() > cnt + 1) {
            auto top = left.top(); left.pop();
            right.emplace(top.score, top.name);
        }
    }

    string get() {
        cnt++;
        // After incrementing cnt, left may need to have one more element
        if ((int)left.size() < cnt) {
            auto top = right.top(); right.pop();
            left.emplace(top.score, top.name);
        }
        return left.top().name;
    }
};
