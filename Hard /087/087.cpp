class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        if (s1.size() != s2.size()) return false;
        
        int n = s1.size();
        vector<int> count(26, 0);
        for (int i = 0; i < n; ++i) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        for (int i = 0; i < 26; ++i) {
            if (count[i] != 0) return false;
        }
        
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                for (int j = 0; j <= n - len; ++j) {
                    if (len == 1) {
                        dp[i][j][len] = s1[i] == s2[j];
                    } else {
                        for (int k = 1; k < len; ++k) {
                            if ((dp[i][j][k] && dp[i + k][j + k][len - k]) || 
                                (dp[i][j + len - k][k] && dp[i + k][j][len - k])) {
                                dp[i][j][len] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return dp[0][0][n];
    }
};
