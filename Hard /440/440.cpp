class Solution {
public:
    int findKthNumber(int n, int k) {
        int curr = 1;
        --k; // We already have '1' as the first number
        while (k > 0) {
            long long steps = calcSteps(n, curr, curr + 1);
            if (steps <= k) {
                // Move to next sibling
                curr += 1;
                k -= steps;
            } else {
                // Move to next child
                curr *= 10;
                k -= 1;
            }
        }
        return curr;
    }

    long long calcSteps(int n, long long curr, long long next) {
        long long steps = 0;
        while (curr <= n) {
            steps += min((long long)n + 1, next) - curr;
            curr *= 10;
            next *= 10;
        }
        return steps;
    }
};
