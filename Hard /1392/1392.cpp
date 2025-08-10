#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string longestPrefix(std::string s) { // Renamed from longestHappyPrefix
        int n = s.length();
        if (n <= 1) {
            return "";
        }

        long long base1 = 31;
        long long mod1 = 1e9 + 7;
        long long base2 = 37;
        long long mod2 = 1e9 + 9;

        long long prefix_hash1 = 0;
        long long prefix_hash2 = 0;
        long long suffix_hash1 = 0;
        long long suffix_hash2 = 0;

        long long power1 = 1; // base1^0, base1^1, ... (for suffix hash)
        long long power2 = 1; // base2^0, base2^1, ... (for suffix hash)

        int longest_len = 0;

        for (int i = 0; i < n - 1; ++i) { // Iterate from length 1 up to n-1
            int char_val_prefix = s[i] - 'a' + 1;
            int char_val_suffix = s[n - 1 - i] - 'a' + 1; // Character from the end, moving left

            // Update prefix hash for s[0...i]
            prefix_hash1 = (prefix_hash1 * base1 + char_val_prefix) % mod1;
            prefix_hash2 = (prefix_hash2 * base2 + char_val_prefix) % mod2;

            // Update suffix hash for s[n-1-i ... n-1]
            // The power term correctly places char_val_suffix at its positional value in the hash
            suffix_hash1 = (char_val_suffix * power1 + suffix_hash1) % mod1;
            suffix_hash2 = (char_val_suffix * power2 + suffix_hash2) % mod2;

            // Update powers for the next iteration (for length i+2)
            power1 = (power1 * base1) % mod1;
            power2 = (power2 * base2) % mod2;

            // If current prefix hash matches current suffix hash
            if (prefix_hash1 == suffix_hash1 && prefix_hash2 == suffix_hash2) {
                longest_len = i + 1; // i+1 is the current length of the prefix/suffix
            }
        }

        return s.substr(0, longest_len);
    }
};
