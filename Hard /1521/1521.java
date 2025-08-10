import java.util.*;

class Solution {
    public int closestToTarget(int[] arr, int target) {
        Set<Integer> prev = new HashSet<>();
        int res = Integer.MAX_VALUE;
        for (int num : arr) {
            Set<Integer> curr = new HashSet<>();
            curr.add(num);
            for (int v : prev) {
                curr.add(v & num);
            }
            for (int v : curr) {
                res = Math.min(res, Math.abs(v - target));
            }
            prev = curr;
        }
        return res;
    }
}
