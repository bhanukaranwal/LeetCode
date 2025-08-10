class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        long long L = stoll(left), R = stoll(right), count = 0;
        // Generate palindromic roots, then check if their squares are palindromic and in [L, R]
        // Odd and even length palindromes
        for (int k = 1; k < 100000; ++k) {
            string s = to_string(k), rs(s.rbegin(), s.rend());
            // Odd length palindrome
            string odd = s + rs.substr(1);
            long long v = stoll(odd);
            long long sq = v * v;
            if (sq > R) break;
            if (sq >= L && isPalindrome(sq)) ++count;
        }
        for (int k = 1; k < 100000; ++k) {
            string s = to_string(k), rs(s.rbegin(), s.rend());
            // Even length palindrome
            string even = s + rs;
            long long v = stoll(even);
            long long sq = v * v;
            if (sq > R) break;
            if (sq >= L && isPalindrome(sq)) ++count;
        }
        return count;
    }
    bool isPalindrome(long long x) {
        string s = to_string(x);
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }
};
