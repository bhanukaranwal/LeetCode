#include <string>
#include <vector>
#include <numeric> // For std::accumulate

class Solution {
public:
    std::vector<int> calculateZArray(const std::string& s) {
        int n = s.length();
        std::vector<int> z(n);
        z[0] = n; // Z[0] is typically the length of the string itself

        int L = 0, R = 0; // Z-box [L, R]
        for (int i = 1; i < n; ++i) {
            if (i <= R) {
                z[i] = std::min(R - i + 1, z[i - L]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] - 1 > R) {
                L = i;
                R = i + z[i] - 1;
            }
        }
        return z;
    }

    long long sumScores(std::string s) {
        std::vector<int> z_array = calculateZArray(s);
        long long total_score = 0;
        for (int score : z_array) {
            total_score += score;
        }
        return total_score;
    }
};
