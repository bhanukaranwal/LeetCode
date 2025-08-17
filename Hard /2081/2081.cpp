#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Convert a number to base k as a string
    string toBaseK(long long num, int k) {
        string s;
        while (num > 0) {
            s += '0' + (num % k);
            num /= k;
        }
        reverse(s.begin(), s.end());
        return s;
    }
    
    // Check if a string is a palindrome
    bool isPalindrome(const string& s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }
    
    // Generate palindromic numbers in base 10
    vector<long long> generatePalindromes(int len) {
        vector<long long> res;
        int half = (len + 1) / 2;
        long long start = pow(10, half - 1);
        long long end = pow(10, half);
        for (long long i = start; i < end; ++i) {
            string left = to_string(i);
            string right = left;
            if (len % 2 == 1) right.pop_back();
            reverse(right.begin(), right.end());
            string pal = left + right;
            res.push_back(stoll(pal));
        }
        return res;
    }
    
    long long kMirror(int k, int n) {
        long long ans = 0;
        int found = 0;
        for (int len = 1; found < n; ++len) {
            auto pals = generatePalindromes(len);
            for (auto num : pals) {
                string basek = toBaseK(num, k);
                if (isPalindrome(basek)) {
                    ans += num;
                    if (++found == n) return ans;
                }
            }
        }
        return ans;
    }
};
