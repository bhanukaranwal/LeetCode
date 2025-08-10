class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int res = INT_MIN;

        for (int left = 0; left < n; ++left) {
            vector<int> rowSum(m, 0);
            for (int right = left; right < n; ++right) {
                // Update rowSum for columns between left and right
                for (int i = 0; i < m; ++i)
                    rowSum[i] += matrix[i][right];

                // Now, find the max subarray sum no larger than k
                set<int> prefixSums;
                prefixSums.insert(0);
                int currSum = 0, currMax = INT_MIN;
                for (int sum : rowSum) {
                    currSum += sum;
                    // We want the smallest prefix >= currSum - k
                    auto it = prefixSums.lower_bound(currSum - k);
                    if (it != prefixSums.end()) {
                        currMax = max(currMax, currSum - *it);
                    }
                    prefixSums.insert(currSum);
                }
                res = max(res, currMax);
            }
        }
        return res;
    }
};
