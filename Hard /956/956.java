import java.util.*;

class Solution {
    public int tallestBillboard(int[] rods) {
        // dp: difference -> max sum of the shorter side
        Map<Integer, Integer> dp = new HashMap<>();
        dp.put(0, 0);

        for (int rod : rods) {
            Map<Integer, Integer> cur = new HashMap<>(dp);
            for (Map.Entry<Integer, Integer> entry : cur.entrySet()) {
                int diff = entry.getKey();
                int shorter = entry.getValue();

                // Add rod to one side
                int d1 = diff + rod;
                dp.put(d1, Math.max(dp.getOrDefault(d1, 0), shorter));

                // Add rod to the other side
                int d2 = Math.abs(diff - rod);
                int newShorter = shorter + Math.min(rod, diff);
                dp.put(d2, Math.max(dp.getOrDefault(d2, 0), newShorter));
            }
        }
        return dp.getOrDefault(0, 0);
    }
}
