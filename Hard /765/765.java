class Solution {
    public int minSwapsCouples(int[] row) {
        int n = row.length;
        int[] pos = new int[n];
        // Map each person to their current seat index
        for (int i = 0; i < n; ++i) {
            pos[row[i]] = i;
        }
        int swaps = 0;
        for (int i = 0; i < n; i += 2) {
            int first = row[i];
            int partner = first ^ 1; // partner of x is x^1 (0<->1, 2<->3, ...)
            if (row[i + 1] != partner) {
                swaps++;
                int partnerIdx = pos[partner];
                // Swap row[i+1] and row[partnerIdx]
                pos[row[i + 1]] = partnerIdx;
                pos[partner] = i + 1;
                int tmp = row[i + 1];
                row[i + 1] = partner;
                row[partnerIdx] = tmp;
            }
        }
        return swaps;
    }
}
