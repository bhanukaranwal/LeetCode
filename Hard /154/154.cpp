#include <vector>
#include <algorithm>

class Solution {
public:
    int findMin(std::vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int min_val = nums[0]; 

        while (left <= right) {
            int mid = left + (right - left) / 2;
            min_val = std::min(min_val, nums[mid]);

            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else if (nums[mid] < nums[right]) {
                right = mid - 1;
            } else { 
                right--; 
            }
        }
        return min_val;
    }
};
