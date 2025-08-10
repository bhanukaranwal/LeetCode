import java.util.*;

class Solution {
    public int countTriplets(int[] nums) {
        Map<Integer, Integer> pairCount = new HashMap<>();
        int n = nums.length;

        // Count all possible (a & b) results
        for (int a : nums) {
            for (int b : nums) {
                int ab = a & b;
                pairCount.put(ab, pairCount.getOrDefault(ab, 0) + 1);
            }
        }

        int res = 0;
        // For each c, check all (a & b) where (a & b & c) == 0
        for (int c : nums) {
            for (int ab : pairCount.keySet()) {
                if ((ab & c) == 0) {
                    res += pairCount.get(ab);
                }
            }
        }
        return res;
    }
}
