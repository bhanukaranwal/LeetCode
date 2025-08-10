class Solution {
public:
    string nearestPalindromic(string n) {
        long long num = stoll(n), ans = -1, diff = LLONG_MAX;
        vector<long long> candidates;
        int len = n.size();
        candidates.push_back((long long)pow(10, len) + 1);
        candidates.push_back((long long)pow(10, len - 1) - 1);
        long long prefix = stoll(n.substr(0, (len + 1) / 2));
        for (int i = -1; i <= 1; ++i) {
            string p = to_string(prefix + i);
            string pal = p + string(p.rbegin() + (len % 2), p.rend());
            candidates.push_back(stoll(pal));
        }
        for (long long cand : candidates) {
            if (cand == num) continue;
            long long d = abs(cand - num);
            if (d < diff || (d == diff && cand < ans)) {
                diff = d;
                ans = cand;
            }
        }
        return to_string(ans);
    }
};
