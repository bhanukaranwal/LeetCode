class Solution {
public:
    int minimumTime(string s) {
        int n = s.size();
        vector<int> left(n + 1), right(n + 1);
        for (int i = 0; i < n; ++i)
            left[i + 1] = min(left[i] + (s[i] == '1' ? 2 : 0), i + 1);
        for (int i = n - 1; i >= 0; --i)
            right[i] = min(right[i + 1] + (s[i] == '1' ? 2 : 0), n - i);
        int res = n;
        for (int i = 0; i <= n; ++i)
            res = min(res, left[i] + right[i]);
        return res;
    }
};
