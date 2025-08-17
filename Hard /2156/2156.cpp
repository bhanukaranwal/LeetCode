#include <string>
#include <vector>
#include <cmath>

class Solution {
public:
    std::string subStrHash(std::string s, int power, int modulo, int k, int hashValue) {
        long long current_hash_val = 0;
        long long power_k_minus_1_mod_m = 1;

        for (int i = 0; i < k - 1; ++i) {
            power_k_minus_1_mod_m = (power_k_minus_1_mod_m * power) % modulo;
        }
        
        long long p_pow_j = 1;
        for (int i = 0; i < k; ++i) {
            current_hash_val = (current_hash_val + (long long)(s[s.length() - k + i] - 'a' + 1) * p_pow_j) % modulo;
            p_pow_j = (p_pow_j * power) % modulo;
        }

        int ans_start_idx = -1;
        if (current_hash_val == hashValue) {
            ans_start_idx = s.length() - k;
        }

        for (int i = s.length() - k - 1; i >= 0; --i) {
            current_hash_val = (current_hash_val - (long long)(s[i + k] - 'a' + 1) * power_k_minus_1_mod_m % modulo + modulo) % modulo;
            current_hash_val = (current_hash_val * power) % modulo;
            current_hash_val = (current_hash_val + (long long)(s[i] - 'a' + 1)) % modulo;

            if (current_hash_val == hashValue) {
                ans_start_idx = i;
            }
        }
        
        return s.substr(ans_start_idx, k);
    }
};
