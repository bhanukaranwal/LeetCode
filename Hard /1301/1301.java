import java.util.*;

class Solution {
    public int[] pathsWithMaxScore(List<String> board) {
        int n = board.size(), mod = 1000000007;
        int[][] maxSum = new int[n][n];
        int[][] ways = new int[n][n];
        maxSum[n-1][n-1] = 0;
        ways[n-1][n-1] = 1;
        for (int i = n-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (board.get(i).charAt(j) == 'X' || (i == n-1 && j == n-1)) continue;
                int curMax = -1, cnt = 0;
                for (int[] d : new int[][]{{1,0},{0,1},{1,1}}) {
                    int ni = i + d[0], nj = j + d[1];
                    if (ni < n && nj < n && ways[ni][nj] > 0) {
                        if (maxSum[ni][nj] > curMax) {
                            curMax = maxSum[ni][nj];
                            cnt = ways[ni][nj];
                        } else if (maxSum[ni][nj] == curMax) {
                            cnt = (cnt + ways[ni][nj]) % mod;
                        }
                    }
                }
                if (curMax == -1) continue;
                int val = board.get(i).charAt(j) == 'E' ? 0 : board.get(i).charAt(j) - '0';
                maxSum[i][j] = curMax + val;
                ways[i][j] = cnt;
            }
        }
        if (ways[0][0] == 0) return new int[]{0,0};
        return new int[]{maxSum[0][0], ways[0][0]};
    }
}
