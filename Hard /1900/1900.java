import java.util.*;

class Solution {
    int earliest = Integer.MAX_VALUE;
    int latest = Integer.MIN_VALUE;

    public int[] earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        List<Integer> players = new ArrayList<>();
        for (int i = 1; i <= n; ++i) players.add(i);
        dfs(players, firstPlayer, secondPlayer, 1);
        return new int[]{earliest, latest};
    }

    private void dfs(List<Integer> players, int fp, int sp, int round) {
        int l = 0, r = players.size() - 1;
        while (l < r) {
            int a = players.get(l), b = players.get(r);
            if ((a == fp && b == sp) || (a == sp && b == fp)) {
                earliest = Math.min(earliest, round);
                latest = Math.max(latest, round);
                return;
            }
            l++; r--;
        }
        // Generate all possible next rounds
        List<List<Integer>> nextRounds = new ArrayList<>();
        backtrack(players, fp, sp, 0, players.size() - 1, new ArrayList<>(), nextRounds);

        for (List<Integer> next : nextRounds) {
            Collections.sort(next); // Winners are lined up in ascending order
            dfs(next, fp, sp, round + 1);
        }
    }

    // Generate all possible winners for the next round
    private void backtrack(List<Integer> players, int fp, int sp, int l, int r, List<Integer> curr, List<List<Integer>> res) {
        if (l > r) {
            res.add(new ArrayList<>(curr));
            return;
        }
        if (l == r) { // Odd number, middle advances
            curr.add(players.get(l));
            backtrack(players, fp, sp, l + 1, r, curr, res);
            curr.remove(curr.size() - 1);
            return;
        }
        int a = players.get(l), b = players.get(r);
        if (a == fp || a == sp) {
            curr.add(a);
            backtrack(players, fp, sp, l + 1, r - 1, curr, res);
            curr.remove(curr.size() - 1);
        } else if (b == fp || b == sp) {
            curr.add(b);
            backtrack(players, fp, sp, l + 1, r - 1, curr, res);
            curr.remove(curr.size() - 1);
        } else {
            // Try both possible winners
            curr.add(a);
            backtrack(players, fp, sp, l + 1, r - 1, curr, res);
            curr.remove(curr.size() - 1);
            curr.add(b);
            backtrack(players, fp, sp, l + 1, r - 1, curr, res);
            curr.remove(curr.size() - 1);
        }
    }
}
