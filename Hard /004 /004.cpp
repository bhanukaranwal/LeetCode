#include <vector>
#include <algorithm>
#include <limits>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Ensure nums1 is the smaller array to optimize the binary search.
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();
        int low = 0;
        int high = m;

        while (low <= high) {
            // Partition nums1 and nums2.
            int partitionX = (low + high) / 2;
            int partitionY = (m + n + 1) / 2 - partitionX;

            // Get the four boundary elements.
            // maxLeft is the largest element on the left partition.
            // minRight is the smallest element on the right partition.
            int maxLeftX = (partitionX == 0) ? std::numeric_limits<int>::min() : nums1[partitionX - 1];
            int minRightX = (partitionX == m) ? std::numeric_limits<int>::max() : nums1[partitionX];

            int maxLeftY = (partitionY == 0) ? std::numeric_limits<int>::min() : nums2[partitionY - 1];
            int minRightY = (partitionY == n) ? std::numeric_limits<int>::max() : nums2[partitionY];

            // Check if we found the correct partition.
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                // If the total number of elements is even.
                if ((m + n) % 2 == 0) {
                    return (double)(std::max(maxLeftX, maxLeftY) + std::min(minRightX, minRightY)) / 2.0;
                } else { // If the total number of elements is odd.
                    return (double)std::max(maxLeftX, maxLeftY);
                }
            } else if (maxLeftX > minRightY) {
                // The partition in nums1 is too far to the right. Move left.
                high = partitionX - 1;
            } else {
                // The partition in nums1 is too far to the left. Move right.
                low = partitionX + 1;
            }
        }

        // Should not happen if inputs are sorted arrays.
        throw std::invalid_argument("Input arrays are not sorted.");
    }
};
