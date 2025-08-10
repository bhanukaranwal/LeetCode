import java.util.*;

class Solution {
    public int maxCandies(int[] status, int[] candies, int[][] keys, int[][] containedBoxes, int[] initialBoxes) {
        int n = status.length, res = 0;
        boolean[] boxOwned = new boolean[n], boxOpened = new boolean[n], keyOwned = new boolean[n];
        Queue<Integer> q = new LinkedList<>();
        for (int b : initialBoxes) {
            boxOwned[b] = true;
            if (status[b] == 1) q.offer(b);
        }
        while (!q.isEmpty()) {
            int b = q.poll();
            if (boxOpened[b]) continue;
            boxOpened[b] = true;
            res += candies[b];
            for (int k : keys[b]) {
                keyOwned[k] = true;
                if (boxOwned[k] && !boxOpened[k] && status[k] == 0) {
                    status[k] = 1;
                    q.offer(k);
                }
            }
            for (int cb : containedBoxes[b]) {
                boxOwned[cb] = true;
                if (status[cb] == 1 && !boxOpened[cb]) q.offer(cb);
                else if (keyOwned[cb] && !boxOpened[cb]) {
                    status[cb] = 1;
                    q.offer(cb);
                }
            }
        }
        return res;
    }
}
