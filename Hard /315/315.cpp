class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> counts(n, 0);
        vector<pair<int, int>> arr; // {value, original index}
        for (int i = 0; i < n; ++i)
            arr.emplace_back(nums[i], i);
        mergeSort(arr, 0, n, counts);
        return counts;
    }

    void mergeSort(vector<pair<int, int>>& arr, int left, int right, vector<int>& counts) {
        if (right - left <= 1) return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, counts);
        mergeSort(arr, mid, right, counts);
        vector<pair<int, int>> temp;
        int j = mid, cnt = 0;
        for (int i = left; i < mid; ++i) {
            while (j < right && arr[j].first < arr[i].first) {
                temp.push_back(arr[j++]);
                ++cnt;
            }
            temp.push_back(arr[i]);
            counts[arr[i].second] += cnt;
        }
        for (int k = j; k < right; ++k)
            temp.push_back(arr[k]);
        for (int i = left; i < right; ++i)
            arr[i] = temp[i - left];
    }
};
