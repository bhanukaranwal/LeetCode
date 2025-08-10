#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        multiset<int> lo, hi; // lo: max-heap (lower half), hi: min-heap (upper half)

        auto add = [&](int num) {
            if (lo.empty() || num <= *lo.rbegin())
                lo.insert(num);
            else
                hi.insert(num);
            // Balance sizes
            if (lo.size() > hi.size() + 1) {
                hi.insert(*lo.rbegin());
                lo.erase(prev(lo.end()));
            } else if (hi.size() > lo.size()) {
                lo.insert(*hi.begin());
                hi.erase(hi.begin());
            }
        };

        auto remove = [&](int num) {
            if (num <= *lo.rbegin())
                lo.erase(lo.find(num));
            else
                hi.erase(hi.find(num));
            // Rebalance
            if (lo.size() > hi.size() + 1) {
                hi.insert(*lo.rbegin());
                lo.erase(prev(lo.end()));
            } else if (hi.size() > lo.size()) {
                lo.insert(*hi.begin());
                hi.erase(hi.begin());
            }
        };

        for (int i = 0; i < nums.size(); ++i) {
            add(nums[i]);
            if (i >= k - 1) {
                // Get median
                if (k % 2)
                    res.push_back(*lo.rbegin());
                else
                    res.push_back(((double)*lo.rbegin() + *hi.begin()) / 2.0);
                // Remove the element going out of the window
                remove(nums[i - k + 1]);
            }
        }
        return res;
    }
};
