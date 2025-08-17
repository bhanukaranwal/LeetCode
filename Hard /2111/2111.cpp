#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size(), ans = 0;
        for (int i = 0; i < k; ++i) {
            vector<int> seq;
            for (int j = i; j < n; j += k) seq.push_back(arr[j]);
            // Compute LNDS (Longest Non-Decreasing Subsequence)
            vector<int> dp;
            for (int x : seq) {
                auto it = upper_bound(dp.begin(), dp.end(), x);
                if (it == dp.end()) dp.push_back(x);
                else *it = x;
            }
            ans += seq.size() - dp.size();
        }
        return ans;
    }
};
