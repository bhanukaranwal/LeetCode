#include <vector>
#include <numeric>

class Solution {
public:
    int splitArray(std::vector<int>& nums, int k) {
        // Initialize binary search boundaries
        long left = 0, right = 0;
        for (int num : nums) {
            left = std::max(left, (long)num); // Max single element
            right += num; // Sum of all elements
        }
        
        // Binary search for the minimum largest sum
        while (left < right) {
            long mid = left + (right - left) / 2;
            
            // Check if we can split into k subarrays with max sum <= mid
            int count = 1;
            long curr_sum = 0;
            for (int num : nums) {
                if (curr_sum + num > mid) {
                    count++;
                    curr_sum = num;
                } else {
                    curr_sum += num;
                }
            }
            
            // Adjust binary search boundaries
            if (count <= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};
