class Solution {
public:
    bool isSolvable(vector<string>& words, string result) {
        // 1. Collect all unique characters
        set<char> charset;
        for (const string& w : words) for (char c : w) charset.insert(c);
        for (char c : result) charset.insert(c);
        if (charset.size() > 10) return false; // Can't map more than 10 letters to 0-9

        // 2. Map chars to indices for easier handling
        vector<char> chars(charset.begin(), charset.end());
        unordered_map<char, int> charIdx;
        for (int i = 0; i < chars.size(); ++i) charIdx[chars[i]] = i;

        // 3. Precompute coefficients for each letter (column-wise)
        vector<int> coeff(10, 0);
        for (const string& w : words) {
            int p = 1;
            for (int i = w.size() - 1; i >= 0; --i) {
                coeff[charIdx[w[i]]] += p;
                p *= 10;
            }
        }
        int p = 1;
        for (int i = result.size() - 1; i >= 0; --i) {
            coeff[charIdx[result[i]]] -= p;
            p *= 10;
        }

        // 4. Mark leading letters (cannot be zero)
        vector<bool> leading(10, false);
        for (const string& w : words) if (w.size() > 1) leading[charIdx[w[0]]] = true;
        if (result.size() > 1) leading[charIdx[result[0]]] = true;

        // 5. Backtracking
        vector<int> assign(10, -1); // char index -> digit
        vector<bool> used(10, false); // digit used or not

        function<bool(int, long long)> dfs = [&](int idx, long long sum) {
            if (idx == chars.size()) return sum == 0;
            for (int d = 0; d <= 9; ++d) {
                if (used[d]) continue;
                if (d == 0 && leading[idx]) continue;
                assign[idx] = d;
                used[d] = true;
                long long nextSum = sum + coeff[idx] * d;
                if (dfs(idx + 1, nextSum)) return true;
                assign[idx] = -1;
                used[d] = false;
            }
            return false;
        };

        return dfs(0, 0);
    }
};
