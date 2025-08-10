#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string shortestPalindrome(std::string s) {
        int n = s.length();
        if (n <= 1) {
            return s;
        }

        long long base = 31; // Radix
        long long mod = 1e9 + 7; // Modulus

        long long hash_forward = 0;
        long long hash_backward = 0;
        long long power = 1; // base^0, base^1, base^2, ...

        int longest_pal_prefix_len = 0;

        for (int i = 0; i < n; ++i) {
            int char_val = s[i] - 'a' + 1; // Map 'a' to 1, 'b' to 2, etc.

            hash_forward = (hash_forward * base + char_val) % mod;
            hash_backward = (char_val * power + hash_backward) % mod;
            power = (power * base) % mod;

            if (hash_forward == hash_backward) {
                // Potential palindromic prefix.
                // We need to store the length 'i + 1'
                longest_pal_prefix_len = i + 1;
            }
        }

        // The characters that are not part of the longest palindromic prefix
        // need to be reversed and prepended.
        std::string suffix_to_prepend = s.substr(longest_pal_prefix_len);
        std::reverse(suffix_to_prepend.begin(), suffix_to_prepend.end());

        return suffix_to_prepend + s;
    }
};
