class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int n = arr.size();
        int totalOnes = 0;
        for (int x : arr) totalOnes += x;
        if (totalOnes == 0) return {0, n - 1};
        if (totalOnes % 3 != 0) return {-1, -1};
        int onesPerPart = totalOnes / 3;
        int first = -1, second = -1, third = -1, cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] == 1) {
                ++cnt;
                if (cnt == 1) first = i;
                else if (cnt == onesPerPart + 1) second = i;
                else if (cnt == 2 * onesPerPart + 1) third = i;
            }
        }
        int len = n - third;
        if (first + len > second || second + len > third) return {-1, -1};
        for (int i = 0; i < len; ++i) {
            if (arr[first + i] != arr[second + i] || arr[first + i] != arr[third + i])
                return {-1, -1};
        }
        return {first + len - 1, second + len};
    }
};
