class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) return 9;
        int maxNum = pow(10, n) - 1;
        for (int left = maxNum; left > maxNum / 10; --left) {
            long p = left;
            int x = left;
            while (x) {
                p = p * 10 + x % 10;
                x /= 10;
            }
            for (long a = maxNum; a * a >= p; --a) {
                if (p % a == 0) return p % 1337;
            }
        }
        return 9;
    }
};
