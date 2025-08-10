class Solution {
    public int numDecodings(String s) {
        int MOD = 1000000007;
        int n = s.length();
        long a = 1, b = s.charAt(0) == '*' ? 9 : (s.charAt(0) != '0' ? 1 : 0), c = b;
        for (int i = 1; i < n; i++) {
            c = 0;
            char ch1 = s.charAt(i - 1), ch2 = s.charAt(i);
            if (ch2 == '*') c = (9 * b) % MOD;
            else if (ch2 != '0') c = b;
            if (ch1 == '*' && ch2 == '*') c = (c + 15 * a) % MOD;
            else if (ch1 == '*') {
                if (ch2 <= '6') c = (c + 2 * a) % MOD;
                else c = (c + a) % MOD;
            } else if (ch2 == '*') {
                if (ch1 == '1') c = (c + 9 * a) % MOD;
                else if (ch1 == '2') c = (c + 6 * a) % MOD;
            } else {
                int num = (ch1 - '0') * 10 + (ch2 - '0');
                if (num >= 10 && num <= 26) c = (c + a) % MOD;
            }
            a = b;
            b = c;
        }
        return (int)c;
    }
}
