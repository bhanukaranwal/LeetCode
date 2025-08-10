#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    int minCut(std::string s) {
        int n = s.length();

        std::vector<std::vector<bool>> isPalindrome(n, std::vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            isPalindrome[i][i] = true;
        }

        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i+1]) {
                isPalindrome[i][i+1] = true;
            }
        }

        for (int length = 3; length <= n; ++length) {
            for (int i = 0; i <= n - length; ++i) {
                int j = i + length - 1;
                if (s[i] == s[j] && isPalindrome[i+1][j-1]) {
                    isPalindrome[i][j] = true;
                }
            }
        }

        std::vector<int> dp(n + 1);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            dp[i] = i - 1; 
            for (int j = 0; j < i; ++j) {
                if (isPalindrome[j][i-1]) {
                    if (j == 0) {
                        dp[i] = 0;
                    } else {
                        dp[i] = std::min(dp[i], dp[j] + 1);
                    }
                }
            }
        }

        return dp[n];
    }
};
