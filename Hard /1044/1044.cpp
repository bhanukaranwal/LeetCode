#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm> // For std::min and std::max (though not directly used in the final version)

class Solution {
private:
    // Using two bases and two moduli for robust hashing to minimize collisions
    long long base1 = 31; // A prime base, suitable for lowercase English letters ('a' to 'z')
    long long mod1 = 1e9 + 7;
    long long base2 = 37; // Another prime base
    long long mod2 = 1e9 + 9;

    // Custom hash for std::pair<long long, long long>
    // This struct must be declared outside the function where it's used,
    // or as a static member of the class.
    struct PairHash {
        template <class T1, class T2>
        std::size_t operator () (const std::pair<T1, T2> &p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            // Simple combination, a bit-shift and XOR often provides a good distribution
            return h1 ^ (h2 << 1);
        }
    };

    // Helper function to check if there is a duplicate substring of given length
    // Returns the starting index of *any* duplicate substring if found, -1 otherwise.
    int check(int len, const std::string& s) {
        if (len == 0) return -1;
        if (len > s.length()) return -1;

        // Use a set to store combined hashes for quick lookups
        // Now using our custom PairHash struct
        std::unordered_set<std::pair<long long, long long>, PairHash> seen_hash_pairs;

        long long power1 = 1;
        long long power2 = 1;
        for (int i = 0; i < len - 1; ++i) {
            power1 = (power1 * base1) % mod1;
            power2 = (power2 * base2) % mod2;
        }

        long long current_hash1 = 0;
        long long current_hash2 = 0;

        // Calculate hash for the first substring of length 'len'
        for (int i = 0; i < len; ++i) {
            int char_val = s[i] - 'a' + 1; // Map 'a' to 1, 'b' to 2, etc.
            current_hash1 = (current_hash1 * base1 + char_val) % mod1;
            current_hash2 = (current_hash2 * base2 + char_val) % mod2;
        }

        if (seen_hash_pairs.count({current_hash1, current_hash2})) {
             return 0; // Found a duplicate at index 0 (first substring)
        }
        seen_hash_pairs.insert({current_hash1, current_hash2});

        // Roll the hash for the remaining substrings
        for (int i = len; i < s.length(); ++i) {
            int old_char_val = s[i - len] - 'a' + 1;
            int new_char_val = s[i] - 'a' + 1;

            // Remove old char contribution
            current_hash1 = (current_hash1 - (old_char_val * power1) % mod1 + mod1) % mod1;
            current_hash2 = (current_hash2 - (old_char_val * power2) % mod2 + mod2) % mod2;

            // Add new char contribution
            current_hash1 = (current_hash1 * base1 + new_char_val) % mod1;
            current_hash2 = (current_hash2 * base2 + new_char_val) % mod2;

            if (seen_hash_pairs.count({current_hash1, current_hash2})) {
                // Assuming no collisions after double hashing, return the starting index
                return i - len + 1;
            }
            seen_hash_pairs.insert({current_hash1, current_hash2});
        }

        return -1; // No duplicate found for this length
    }

public:
    std::string longestDupSubstring(std::string s) {
        int n = s.length();
        std::string longest_dup = "";
        int longest_dup_start_idx = -1;
        int longest_dup_len = 0;

        int low = 1;
        int high = n - 1; // Maximum possible length of a duplicate substring
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int current_dup_start_idx = check(mid, s);
            if (current_dup_start_idx != -1) {
                // Found a duplicate of length 'mid', try for longer ones
                longest_dup_len = mid;
                longest_dup_start_idx = current_dup_start_idx;
                low = mid + 1;
            } else {
                // No duplicate of length 'mid', try shorter ones
                high = mid - 1;
            }
        }

        if (longest_dup_start_idx != -1) {
            return s.substr(longest_dup_start_idx, longest_dup_len);
        }
        return "";
    }
};
