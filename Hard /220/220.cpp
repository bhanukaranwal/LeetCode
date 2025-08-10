#include <vector>
#include <cmath>     // For std::abs
#include <unordered_map> // For efficient bucket storage

class Solution {
public:
    // Helper function to get the bucket ID for a given number.
    // This handles both positive and negative numbers correctly,
    // ensuring that numbers within `valueDiff` distance fall into the same or adjacent buckets.
    long long getBucketId(long long num, long long bucket_size) {
        // For positive numbers: num / bucket_size
        // For negative numbers: adjusted to ensure floor division behavior for buckets.
        // Example: if bucket_size = 4, valueDiff = 3
        // [0,3] -> bucket 0
        // [4,7] -> bucket 1
        // [-4,-1] -> bucket -1
        // [-8,-5] -> bucket -2
        // This formula effectively shifts negative numbers to align with bucket boundaries.
        return num < 0 ? (num + 1) / bucket_size - 1 : num / bucket_size;
    }

    bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int indexDiff, int valueDiff) {
        if (indexDiff < 0 || valueDiff < 0) {
            return false; // Constraints state indexDiff >= 1 and valueDiff >= 0, but good to be robust.
        }
        if (nums.empty() || indexDiff == 0) { // If indexDiff is 0, abs(i-j) <= 0 means i=j, but i!=j, so no solution.
            return false;
        }

        // The size of each bucket. If valueDiff is 0, bucket_size is 1.
        long long bucket_size = (long long)valueDiff + 1;

        // Use an unordered_map to store the numbers present in the current sliding window.
        // Key: bucket ID, Value: the number stored in that bucket.
        // We only need to store one number per bucket, as any two numbers in the same bucket
        // (with size valueDiff + 1) are guaranteed to satisfy the valueDiff condition.
        std::unordered_map<long long, long long> buckets;

        for (int i = 0; i < nums.size(); ++i) {
            long long num = nums[i];
            long long bucket_id = getBucketId(num, bucket_size);

            // 1. Check the current bucket:
            // If this bucket already contains a number, it means we found a pair (nums[i], stored_num)
            // such that abs(nums[i] - stored_num) <= valueDiff (guaranteed by bucket size).
            // The indexDiff is handled by the sliding window.
            if (buckets.count(bucket_id)) {
                return true;
            }

            // 2. Check adjacent buckets:
            // Numbers in adjacent buckets might also satisfy the valueDiff condition.
            // Check bucket_id - 1:
            if (buckets.count(bucket_id - 1)) {
                long long prev_num = buckets[bucket_id - 1];
                if (std::abs(num - prev_num) <= valueDiff) {
                    return true;
                }
            }
            // Check bucket_id + 1:
            if (buckets.count(bucket_id + 1)) {
                long long next_num = buckets[bucket_id + 1];
                if (std::abs(num - next_num) <= valueDiff) {
                    return true;
                }
            }

            // Add the current number to its bucket.
            buckets[bucket_id] = num;

            // Maintain the sliding window:
            // If the window size exceeds indexDiff, remove the element that falls out of the window.
            // The element to remove is at index `i - indexDiff`.
            if (i >= indexDiff) {
                long long old_num = nums[i - indexDiff];
                long long old_bucket_id = getBucketId(old_num, bucket_size);
                // Remove the old number from its bucket.
                // It's important to only erase if the stored value matches, in case a new number
                // overwrote the old_num in the same bucket. However, since we return true if a bucket
                // is already occupied, this shouldn't be an issue for correctness.
                // For robustness, ensure you only erase if the element is actually the one you expect.
                // For this problem, since we only store one element per bucket, a simple erase is fine.
                buckets.erase(old_bucket_id);
            }
        }

        // If no such pair is found after checking all elements, return false.
        return false;
    }
};
