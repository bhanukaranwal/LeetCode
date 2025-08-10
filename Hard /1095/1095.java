/**
 * // This is MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface MountainArray {
 *     public int get(int index) {}
 *     public int length() {}
 * }
 */
class Solution {
    public int findInMountainArray(int target, MountainArray mountainArr) {
        int n = mountainArr.length();
        // 1. Find peak index
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1))
                left = mid + 1;
            else
                right = mid;
        }
        int peak = left;

        // 2. Binary search on ascending part
        int res = binarySearch(mountainArr, 0, peak, target, true);
        if (res != -1) return res;
        // 3. Binary search on descending part
        return binarySearch(mountainArr, peak + 1, n - 1, target, false);
    }

    private int binarySearch(MountainArray arr, int l, int r, int target, boolean asc) {
        while (l <= r) {
            int mid = (l + r) / 2;
            int val = arr.get(mid);
            if (val == target) return mid;
            if (asc) {
                if (val < target) l = mid + 1;
                else r = mid - 1;
            } else {
                if (val > target) l = mid + 1;
                else r = mid - 1;
            }
        }
        return -1;
    }
}
