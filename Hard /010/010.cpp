#include <string>
#include <vector>

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        int m = s.length();
        int n = p.length();

        // dp[i][j] = true if the first i chars of s match the first j chars of p
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));

        // Base case: an empty string matches an empty pattern
        dp[0][0] = true;

        // Handle patterns like "a*", ".*", "a*b*c*" that can match an empty string
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        // Fill the rest of the DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // Case 1: The pattern character is not '*'
                if (p[j - 1] != '*') {
                    if (dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
                        dp[i][j] = true;
                    }
                }
                // Case 2: The pattern character is '*'
                else {
                    // Option A: The '*' matches zero of the preceding element.
                    // In this case, the result is the same as matching without the "x*" part.
                    if (dp[i][j - 2]) {
                        dp[i][j] = true;
                    }
                    // Option B: The '*' matches one or more of the preceding element.
                    // This is only possible if the current string char matches the char before '*'.
                    else if (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.')) {
                        dp[i][j] = true;
                    }
                }
            }
        }

        return dp[m][n];
    }
};
