class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);
        int m = s.size(), d = digits.size(), res = 0;
        for (int i = 1; i < m; ++i)
            res += pow(d, i);
        for (int i = 0; i < m; ++i) {
            bool prefix = false;
            for (string& digit : digits) {
                if (digit[0] < s[i])
                    res += pow(d, m - i - 1);
                else if (digit[0] == s[i])
                    prefix = true;
            }
            if (!prefix) return res;
        }
        return res + 1;
    }
};
