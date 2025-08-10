class Solution {
public:
    // Compute the length of a run in compressed form
    int getLength(int count) {
        if (count == 0) return 0; // No characters
        if (count == 1) return 1; // Single character, e.g., "a"
        if (count <= 9) return 2; // e.g., "a5"
        if (count <= 99) return 3; // e.g., "a10"
        return 4; // count = 100, e.g., "a100"
    }
    
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.length();
        // dp[i][j] = min length of compressed string for s[0:i] with j deletions left
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX / 2));
        dp[0][0] = 0; // Empty string, no deletions used
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                // Case 1: Delete s[i-1]
                if (j > 0) {
                    dp[i][j] = dp[i-1][j-1]; // Delete current char
                }
                
                // Case 2: Keep s[i-1]
                int deletions = 0; // Characters to delete to form a run
                int runCount = 0;  // Count of s[i-1] in the current run
                // Look back to form a run with s[i-1]
                for (int p = i; p >= 1; p--) {
                    if (s[p-1] == s[i-1]) {
                        runCount++; // Include this character in the run
                    } else {
                        deletions++; // Need to delete this character
                    }
                    if (j - deletions >= 0) {
                        // Try forming a run ending at i-1 with p-1 as start
                        dp[i][j] = min(dp[i][j], dp[p-1][j-deletions] + getLength(runCount));
                    }
                }
                
                // Case 3: Start a new run with s[i-1] (no previous same char)
                if (j >= i - 1) {
                    dp[i][j] = min(dp[i][j], getLength(1)); // Keep only s[i-1]
                }
            }
        }
        
        int result = INT_MAX;
        for (int j = 0; j <= k; j++) {
            result = min(result, dp[n][j]);
        }
        return result;
    }
};
