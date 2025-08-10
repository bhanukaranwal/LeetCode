#include <string>
#include <vector>
#include <algorithm>

class Solution {
private:
    // Using two bases and two moduli for robust hashing
    long long base1 = 31;
    long long mod1 = 1e9 + 7;
    long long base2 = 37;
    long long mod2 = 1e9 + 9;

public:
    int longestDecomposition(std::string text) {
        int n = text.length();
        if (n == 0) return 0;

        int ans = 0;
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            if (left == right) {
                // If only one character or an odd-length middle chunk remains
                ans += 1;
                break;
            }

            // Iterate to find the longest possible matching prefix and suffix
            // The `len` here represents the length of the current potential chunk we are checking
            bool found_match = false;
            long long current_prefix_hash1 = 0;
            long long current_prefix_hash2 = 0;
            long long current_suffix_hash1 = 0;
            long long current_suffix_hash2 = 0;

            long long power1 = 1; // base1^0
            long long power2 = 1; // base2^0

            for (int len = 1; left + len - 1 < right - len + 1; ++len) {
                // Add character from left side to prefix hash
                int char_val_left = text[left + len - 1] - 'a' + 1;
                current_prefix_hash1 = (current_prefix_hash1 * base1 + char_val_left) % mod1;
                current_prefix_hash2 = (current_prefix_hash2 * base2 + char_val_left) % mod2;

                // Add character from right side to suffix hash (building from right to left, so power increases)
                int char_val_right = text[right - len + 1] - 'a' + 1;
                current_suffix_hash1 = (char_val_right * power1 + current_suffix_hash1) % mod1;
                current_suffix_hash2 = (char_val_right * power2 + current_suffix_hash2) % mod2;

                // Update powers for the next character
                power1 = (power1 * base1) % mod1;
                power2 = (power2 * base2) % mod2;

                if (current_prefix_hash1 == current_suffix_hash1 &&
                    current_prefix_hash2 == current_suffix_hash2) {
                    
                    // Found a pair of matching chunks of length 'len'
                    ans += 2;
                    left += len; // Move left pointer past the found chunk
                    right -= len; // Move right pointer past the found chunk
                    found_match = true;
                    break; // Break from inner loop, re-evaluate with new left/right bounds
                }
            }

            if (!found_match) {
                // If no matching pair was found for the current `left` and `right` segment,
                // the remaining segment forms a single, unmatchable chunk.
                ans += 1;
                break; // All remaining characters form one chunk
            }
        }
        
        return ans;
    }
};
