class Solution {
    public int uniqueLetterString(String s) {
        int n = s.length();
        int[][] idx = new int[26][2]; // [prev, last]
        for (int[] arr : idx) {
            arr[0] = -1;
            arr[1] = -1;
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            int c = s.charAt(i) - 'A';
            // For previous occurrence
            res += (i - idx[c][1]) * (idx[c][1] - idx[c][0]);
            idx[c][0] = idx[c][1];
            idx[c][1] = i;
        }
        // For the tail (after last occurrence)
        for (int c = 0; c < 26; ++c) {
            res += (n - idx[c][1]) * (idx[c][1] - idx[c][0]);
        }
        return res;
    }
}
