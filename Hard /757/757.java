import java.util.*;

class Solution {
    public int intersectionSizeTwo(int[][] intervals) {
        // Sort by end ascending, then start descending
        Arrays.sort(intervals, (a, b) -> a[1] != b[1] ? 
            Integer.compare(a[1], b[1]) : Integer.compare(b[0], a[0]));
        
        List<Integer> res = new ArrayList<>();
        int n = intervals.length;
        int a = -1, b = -1; // last two added to the set
        
        for (int[] interval : intervals) {
            int start = interval[0], end = interval[1];
            // Count how many of the last two are in the current interval
            int count = 0;
            if (a >= start) count++;
            if (b >= start) count++;
            // If both are present, do nothing
            if (count == 2) continue;
            // If only one is present, add end
            if (count == 1) {
                res.add(end);
                if (a < b) a = b;
                b = end;
            } 
            // If none are present, add end-1 and end
            if (count == 0) {
                res.add(end - 1);
                res.add(end);
                a = end - 1;
                b = end;
            }
        }
        return res.size();
    }
}
