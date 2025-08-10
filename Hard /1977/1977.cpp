#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

class Solution {
public:
    // If the test environment is indeed calling 'numberOfCombinations',
    // then rename the function accordingly.
    // However, for LeetCode problem 1977, the correct name is numberOfWays.
    int numberOfCombinations(std::string num) { // RENAMED for your specific error
        int n = num.length();
        long long MOD = 1e9 + 7;

        if (n == 0 || num[0] == '0') {
            return 0;
        }

        std::vector<std::vector<int>> lcp(n + 1, std::vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (num[i] == num[j]) {
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
                }
            }
        }

        std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(n + 1, 0));
        std::vector<std::vector<long long>> prefix_sum_dp(n + 1, std::vector<long long>(n + 1, 0));

        // Initialize for the first number (prefix of num)
        for (int i = 1; i <= n; ++i) { // i is the length of the first number (num[0...i-1])
            if (num[0] == '0' && i > 1) { // Leading zero for multi-digit first number
                continue;
            }
            if (num[0] != '0') { // Valid first number, starting at index 0.
                dp[i][0] = 1; 
            }
        }

        // Calculate prefix sums for base cases where the previous number started at index 0
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                prefix_sum_dp[i][j] = dp[i][j];
                if (j > 0) {
                    prefix_sum_dp[i][j] = (prefix_sum_dp[i][j] + prefix_sum_dp[i][j-1]) % MOD;
                }
            }
        }

        // Main DP loop
        for (int i = 1; i <= n; ++i) { // `i` is the current end index + 1 (length of prefix processed)
            for (int j = 0; j < i; ++j) { // `j` is the start index of the current (last) number `num[j...i-1]`
                
                // If `num[j]` is '0' and it's not a single digit '0'
                if (num[j] == '0' && (i - j) > 1) { 
                    // This segment `num[j...i-1]` has a leading zero and is multi-digit. Invalid.
                    dp[i][j] = 0; // Ensure it's explicitly 0
                    // Its prefix sum will be handled below.
                } else if (num[j] == '0' && (i - j) == 1) {
                    // Single digit '0' is not a positive integer as per problem.
                    dp[i][j] = 0;
                } else {
                    // If this is the very first number (j == 0), it's already set from base cases or continues as 0 if invalid
                    // If j > 0, this number is not the very first. We need to consider previous numbers.

                    long long current_segment_len = i - j;

                    // Sum contributions from previous numbers shorter than current_segment_len
                    // Previous number `num[k...j-1]` has length `prev_len = j - k`.
                    // We need `prev_len < current_segment_len`.
                    // So `j - k < i - j => k > 2j - i`.
                    
                    int min_k_for_shorter_prev = std::max(0, j - (int)current_segment_len + 1);
                    int max_k_for_shorter_prev = j - 1;

                    if (min_k_for_shorter_prev <= max_k_for_shorter_prev) {
                        long long ways = prefix_sum_dp[j][max_k_for_shorter_prev];
                        if (min_k_for_shorter_prev > 0) {
                            ways = (ways - prefix_sum_dp[j][min_k_for_shorter_prev - 1] + MOD) % MOD;
                        }
                        dp[i][j] = (dp[i][j] + ways) % MOD;
                    }

                    // Sum contributions from previous numbers with same length as current_segment_len
                    // Previous number `num[k...j-1]` has length `prev_len = current_segment_len`.
                    // So `j - k = i - j => k = 2j - i`.
                    int k_for_same_len_prev = j - (int)current_segment_len;
                    
                    if (k_for_same_len_prev >= 0) { // Check if such k is a valid start index for a previous number
                        if (!(num[k_for_same_len_prev] == '0' && current_segment_len > 1)) { // No leading zero for previous number
                            // Compare num[j...i-1] with num[k_for_same_len_prev...j-1]
                            int l = lcp[j][k_for_same_len_prev];
                            
                            // If current is greater OR equal to previous
                            if (l >= current_segment_len || num[j + l] > num[k_for_same_len_prev + l]) {
                                dp[i][j] = (dp[i][j] + dp[j][k_for_same_len_prev]) % MOD;
                            }
                        }
                    }
                }
            }
            // Update prefix sums for current 'i'
            for (int j_idx = 0; j_idx < i; ++j_idx) { // `j_idx` is the start index of the current segment
                prefix_sum_dp[i][j_idx] = dp[i][j_idx];
                if (j_idx > 0) {
                    prefix_sum_dp[i][j_idx] = (prefix_sum_dp[i][j_idx] + prefix_sum_dp[i][j_idx-1]) % MOD;
                }
            }
        }

        long long total_ways = 0;
        // Sum up all dp[n][j] values, where n is the total length
        for (int j = 0; j < n; ++j) {
            total_ways = (total_ways + dp[n][j]) % MOD;
        }

        return total_ways;
    }
};
