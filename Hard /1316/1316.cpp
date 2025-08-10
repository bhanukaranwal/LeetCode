#include <string>
#include <unordered_set>
#include <vector>

class Solution {
private:
    long long base1 = 31;
    long long mod1 = 1e9 + 7;
    long long base2 = 37;
    long long mod2 = 1e9 + 9;

    // A simple custom hash for std::pair since it's not provided by default for unordered_set
    struct PairHash {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& p) const {
            auto h1 = std::hash<T1>{}(p.first);
            auto h2 = std::hash<T2>{}(p.second);
            // Combine hashes using a simple bit shift and XOR
            return h1 ^ (h2 << 1);
        }
    };

public:
    int distinctEchoSubstrings(std::string text) {
        int n = text.length();
        if (n < 2) {
            return 0;
        }

        std::unordered_set<std::pair<long long, long long>, PairHash> distinct_echoes;

        // Precompute powers for rolling hash
        // powers1[k] = base1^k % mod1
        // powers2[k] = base2^k % mod2
        std::vector<long long> powers1(n + 1);
        std::vector<long long> powers2(n + 1);
        powers1[0] = 1;
        powers2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            powers1[i] = (powers1[i - 1] * base1) % mod1;
            powers2[i] = (powers2[i - 1] * base2) % mod2;
        }

        // Precompute prefix hashes
        // P[k] = hash of text[0...k-1]
        std::vector<long long> prefix_hash1(n + 1, 0);
        std::vector<long long> prefix_hash2(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_hash1[i + 1] = (prefix_hash1[i] * base1 + (text[i] - 'a' + 1)) % mod1;
            prefix_hash2[i + 1] = (prefix_hash2[i] * base2 + (text[i] - 'a' + 1)) % mod2;
        }

        // Helper function to get hash of substring text[i...j]
        auto get_hash = [&](int i, int j) -> std::pair<long long, long long> {
            long long h1 = (prefix_hash1[j + 1] - (prefix_hash1[i] * powers1[j - i + 1]) % mod1 + mod1) % mod1;
            long long h2 = (prefix_hash2[j + 1] - (prefix_hash2[i] * powers2[j - i + 1]) % mod2 + mod2) % mod2;
            return {h1, h2};
        };

        // Iterate through all possible starting positions 'i'
        for (int i = 0; i < n; ++i) {
            // Iterate through all possible lengths of 'a'
            // The length of 'a' can be from 1 up to (n - i) / 2
            for (int len_a = 1; i + 2 * len_a <= n; ++len_a) {
                int mid_point = i + len_a - 1;
                int end_point = i + 2 * len_a - 1;

                // Calculate hash for the first 'a' part (text[i ... mid_point])
                std::pair<long long, long long> hash_a1 = get_hash(i, mid_point);

                // Calculate hash for the second 'a' part (text[mid_point + 1 ... end_point])
                std::pair<long long, long long> hash_a2 = get_hash(mid_point + 1, end_point);

                if (hash_a1.first == hash_a2.first && hash_a1.second == hash_a2.second) {
                    // If hashes match, it's an echo substring (a+a)
                    // Add the hash of the full echo string (a+a) to the set of distinct echoes
                    // We can reuse hash_a1 as the representative for 'a' to store the full 'a+a' hash.
                    distinct_echoes.insert(hash_a1); // Store the hash of 'a' itself
                }
            }
        }

        return distinct_echoes.size();
    }
};
