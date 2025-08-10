class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + nums[i];
        return countWhileMerge(prefix, 0, n + 1, lower, upper);
    }

    int countWhileMerge(vector<long long>& prefix, int left, int right, int lower, int upper) {
        if (right - left <= 1) return 0;
        int mid = left + (right - left) / 2;
        int count = countWhileMerge(prefix, left, mid, lower, upper)
                  + countWhileMerge(prefix, mid, right, lower, upper);
        int j = mid, k = mid, t = mid;
        vector<long long> temp;
        for (int i = left; i < mid; ++i) {
            while (k < right && prefix[k] - prefix[i] < lower) ++k;
            while (j < right && prefix[j] - prefix[i] <= upper) ++j;
            count += j - k;
        }
        // Merge step
        int p = left, q = mid;
        while (p < mid && q < right) {
            if (prefix[p] < prefix[q]) temp.push_back(prefix[p++]);
            else temp.push_back(prefix[q++]);
        }
        while (p < mid) temp.push_back(prefix[p++]);
        while (q < right) temp.push_back(prefix[q++]);
        for (int i = left; i < right; ++i)
            prefix[i] = temp[i - left];
        return count;
    }
};
