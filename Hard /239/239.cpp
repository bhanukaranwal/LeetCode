#include <vector>
#include <deque>
#include <algorithm> // For std::max (though not directly used in the final loop for `max`)

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        std::vector<int> result;
        std::deque<int> dq; // Stores indices of elements

        int n = nums.size();
        if (n == 0 || k == 0) {
            return {};
        }

        // Process the first window (initial k elements)
        for (int i = 0; i < k; ++i) {
            // Remove elements from the back of the deque that are smaller than or equal to nums[i].
            // These elements can no longer be the maximum in any future window that includes nums[i],
            // because nums[i] is larger and to their right.
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            // Add the current element's index to the back of the deque.
            dq.push_back(i);
        }

        // The front of the deque now holds the index of the maximum element in the first window.
        result.push_back(nums[dq.front()]);

        // Process the rest of the windows
        for (int i = k; i < n; ++i) {
            // Remove elements from the front of the deque that are outside the current window.
            // An index `j` is outside if `j <= i - k`.
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // Remove elements from the back of the deque that are smaller than or equal to nums[i].
            // Same logic as in the first window processing.
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            // Add the current element's index to the back of the deque.
            dq.push_back(i);

            // The front of the deque now holds the index of the maximum element in the current window.
            result.push_back(nums[dq.front()]);
        }

        return result;
    }
};
