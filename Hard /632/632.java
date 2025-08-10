class Solution {
    public int[] smallestRange(List<List<Integer>> nums) {
        int k = nums.size();
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> nums.get(a[0]).get(a[1]) - nums.get(b[0]).get(b[1]));
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < k; i++) {
            pq.offer(new int[]{i, 0});
            max = Math.max(max, nums.get(i).get(0));
        }
        int start = 0, end = Integer.MAX_VALUE;
        while (pq.size() == k) {
            int[] curr = pq.poll();
            int min = nums.get(curr[0]).get(curr[1]);
            if (max - min < end - start || (max - min == end - start && min < start)) {
                start = min;
                end = max;
            }
            if (curr[1] + 1 < nums.get(curr[0]).size()) {
                pq.offer(new int[]{curr[0], curr[1] + 1});
                max = Math.max(max, nums.get(curr[0]).get(curr[1] + 1));
            }
        }
        return new int[]{start, end};
    }
}
