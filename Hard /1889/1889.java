import java.util.*;

class Solution {
    public int minWastedSpace(int[] packages, int[][] boxes) {
        int MOD = 1_000_000_007;
        Arrays.sort(packages);
        long res = Long.MAX_VALUE;
        int n = packages.length;

        // Precompute prefix sums for packages
        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + packages[i];
        }

        for (int[] box : boxes) {
            Arrays.sort(box);
            // If largest box can't fit largest package, skip this supplier
            if (box[box.length - 1] < packages[n - 1]) continue;
            long waste = 0;
            int i = 0;
            for (int b : box) {
                // Find the rightmost package that can fit in box b
                int j = upperBound(packages, b);
                // All packages in [i, j) fit in box b
                waste += (long) b * (j - i) - (prefix[j] - prefix[i]);
                i = j;
                if (i == n) break; // All packages are packed
            }
            if (i == n) res = Math.min(res, waste);
        }
        return res == Long.MAX_VALUE ? -1 : (int) (res % MOD);
    }

    // Find first index where packages[idx] > target
    private int upperBound(int[] arr, int target) {
        int l = 0, r = arr.length;
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] <= target) l = m + 1;
            else r = m;
        }
        return l;
    }
}
