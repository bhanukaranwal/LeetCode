class Solution {
public:
    int minMovesToMakePalindrome(string s) {
        int res = 0, l = 0, r = s.size() - 1;
        while (l < r) {
            int i = r;
            while (i > l && s[i] != s[l]) --i;
            if (i == l) {
                swap(s[l], s[l + 1]);
                res++;
            } else {
                for (int j = i; j < r; ++j) {
                    swap(s[j], s[j + 1]);
                    res++;
                }
                l++;
                r--;
            }
        }
        return res;
    }
};
