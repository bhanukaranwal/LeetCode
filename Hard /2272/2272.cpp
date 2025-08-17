class Solution {
public:
    int largestVariance(string s) {
        int res = 0;
        for (char a = 'a'; a <= 'z'; ++a) {
            for (char b = 'a'; b <= 'z'; ++b) {
                if (a == b) continue;
                for (int rev = 0; rev < 2; ++rev) {
                    int diff = 0, has_b = 0;
                    int remain_b = count(s.begin(), s.end(), b);
                    string t = s;
                    if (rev) reverse(t.begin(), t.end());
                    for (char c : t) {
                        if (c != a && c != b) continue;
                        if (c == a) diff++;
                        if (c == b) {
                            diff--;
                            has_b = 1;
                            remain_b--;
                        }
                        // Only update result if at least one b has been seen
                        if (has_b) res = max(res, diff);
                        // If diff < 0 and there are more b's ahead, reset
                        if (diff < 0 && remain_b > 0) {
                            diff = 0;
                            has_b = 0;
                        }
                    }
                }
            }
        }
        return res;
    }
};
