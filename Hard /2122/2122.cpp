#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        int n = nums.size() / 2;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++i) {
            int diff = nums[i] - nums[0];
            // diff must be positive and even (since 2*k)
            if (diff <= 0 || diff % 2 != 0) continue;
            int k = diff / 2;
            vector<int> res;
            unordered_map<int, int> count;
            for (int x : nums) count[x]++;
            for (int j = 0; j < nums.size(); ++j) {
                if (count[nums[j]] == 0) continue;
                int low = nums[j];
                int high = low + 2 * k;
                if (count[high] == 0) break;
                res.push_back(low + k);
                count[low]--;
                count[high]--;
            }
            if (res.size() == n) return res;
        }
        return {};
    }
};
