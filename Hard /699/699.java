class Solution {
    public List<Integer> fallingSquares(int[][] positions) {
        List<int[]> intervals = new ArrayList<>();
        List<Integer> res = new ArrayList<>();
        int max = 0;
        for (int[] pos : positions) {
            int left = pos[0], right = pos[0] + pos[1], height = pos[1], base = 0;
            for (int[] in : intervals) {
                if (in[1] > left && in[0] < right) base = Math.max(base, in[2]);
            }
            int h = base + height;
            intervals.add(new int[]{left, right, h});
            max = Math.max(max, h);
            res.add(max);
        }
        return res;
    }
}
