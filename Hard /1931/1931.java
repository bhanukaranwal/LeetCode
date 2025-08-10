import java.util.*;

class Solution {
    public int colorTheGrid(int m, int n) {
        final int MOD = 1_000_000_007;
        int maxState = (int) Math.pow(3, m);

        // 1. Collect all valid states for a column (no two adjacent cells same color)
        List<Integer> validStates = new ArrayList<>();
        for (int state = 0; state < maxState; ++state) {
            if (isValid(state, m)) validStates.add(state);
        }

        // 2. For each state, collect all valid next states (no cell in same row same color)
        Map<Integer, List<Integer>> transitions = new HashMap<>();
        for (int s1 : validStates) {
            for (int s2 : validStates) {
                if (isCompatible(s1, s2, m)) {
                    transitions.computeIfAbsent(s1, k -> new ArrayList<>()).add(s2);
                }
            }
        }

        // 3. DP: dp[col][state] = #ways to fill up to col-th column ending with state
        Map<Integer, Integer> dp = new HashMap<>();
        for (int state : validStates) dp.put(state, 1);

        for (int col = 1; col < n; ++col) {
            Map<Integer, Integer> newDp = new HashMap<>();
            for (int state : validStates) {
                int sum = 0;
                for (int prev : transitions.get(state)) {
                    sum = (sum + dp.get(prev)) % MOD;
                }
                newDp.put(state, sum);
            }
            dp = newDp;
        }

        int res = 0;
        for (int val : dp.values()) res = (res + val) % MOD;
        return res;
    }

    // Check if a column state is valid (no two adjacent cells same color)
    private boolean isValid(int state, int m) {
        int prev = -1;
        for (int i = 0; i < m; ++i) {
            int color = state % 3;
            if (color == prev) return false;
            prev = color;
            state /= 3;
        }
        return true;
    }

    // Check if two columns are compatible (no cell in same row same color)
    private boolean isCompatible(int s1, int s2, int m) {
        for (int i = 0; i < m; ++i) {
            if ((s1 % 3) == (s2 % 3)) return false;
            s1 /= 3;
            s2 /= 3;
        }
        return true;
    }
}
