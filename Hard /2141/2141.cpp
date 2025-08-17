class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long left = 0, right = 0;
        for (int b : batteries) right += b;
        while (left < right) {
            long long mid = (left + right + 1) >> 1;
            long long total = 0;
            for (int b : batteries) total += min((long long)b, mid);
            if (total >= n * mid) left = mid;
            else right = mid - 1;
        }
        return left;
    }
};
