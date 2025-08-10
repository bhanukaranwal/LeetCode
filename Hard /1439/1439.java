import java.util.*;

class Solution {
    public int kthSmallest(int[][] mat, int k) {
        int[] sums = mat[0];
        for (int i = 1; i < mat.length; i++) {
            sums = merge(sums, mat[i], k);
        }
        return sums[k - 1];
    }

    // Merge two sorted arrays, always keeping only the k smallest sums
    private int[] merge(int[] arr1, int[] arr2, int k) {
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        int n1 = arr1.length, n2 = arr2.length;
        int[] res = new int[Math.min(k, n1 * n2)];
        // Initial: pair each arr1[i] with arr2[0]
        for (int i = 0; i < n1; i++) {
            pq.offer(new int[]{arr1[i] + arr2[0], i, 0});
        }
        for (int idx = 0; idx < res.length; idx++) {
            int[] curr = pq.poll();
            res[idx] = curr[0];
            int i = curr[1], j = curr[2];
            if (j + 1 < n2) {
                pq.offer(new int[]{arr1[i] + arr2[j + 1], i, j + 1});
            }
        }
        return res;
    }
}
