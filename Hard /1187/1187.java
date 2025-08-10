import java.util.*;

class Solution {
    public int makeArrayIncreasing(int[] arr1, int[] arr2) {
        // Remove duplicates and sort arr2 for binary search
        TreeSet<Integer> set = new TreeSet<>();
        for (int x : arr2) set.add(x);

        // dp: key = last value used, value = min operations to reach here
        Map<Integer, Integer> dp = new HashMap<>();
        dp.put(-1, 0); // start with -1 as "previous" value

        for (int i = 0; i < arr1.length; i++) {
            Map<Integer, Integer> next = new HashMap<>();
            for (Map.Entry<Integer, Integer> entry : dp.entrySet()) {
                int prev = entry.getKey(), ops = entry.getValue();
                // Option 1: keep arr1[i] if strictly increasing
                if (arr1[i] > prev) {
                    next.put(arr1[i], Math.min(next.getOrDefault(arr1[i], Integer.MAX_VALUE), ops));
                }
                // Option 2: replace arr1[i] with the smallest arr2[j] > prev
                Integer higher = set.higher(prev);
                if (higher != null) {
                    next.put(higher, Math.min(next.getOrDefault(higher, Integer.MAX_VALUE), ops + 1));
                }
            }
            if (next.isEmpty()) return -1;
            dp = next;
        }
        int min = Integer.MAX_VALUE;
        for (int v : dp.values()) min = Math.min(min, v);
        return min;
    }
}
