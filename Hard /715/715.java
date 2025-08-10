import java.util.*;

class RangeModule {
    private TreeMap<Integer, Integer> intervals;

    public RangeModule() {
        intervals = new TreeMap<>();
    }
    
    public void addRange(int left, int right) {
        if (left >= right) return;
        Integer start = intervals.floorKey(left);
        Integer end = intervals.floorKey(right);
        if (start != null && intervals.get(start) >= left) {
            left = start;
        }
        if (end != null && intervals.get(end) > right) {
            right = intervals.get(end);
        }
        intervals.subMap(left, true, right, false).clear();
        intervals.put(left, right);
    }
    
    public boolean queryRange(int left, int right) {
        Integer start = intervals.floorKey(left);
        if (start == null) return false;
        Integer end = intervals.get(start);
        return end != null && end >= right;
    }
    
    public void removeRange(int left, int right) {
        if (left >= right) return;
        Integer start = intervals.floorKey(left);
        Integer end = intervals.floorKey(right);

        // Save the right end of the interval that covers 'right', if any
        Integer endVal = (end != null) ? intervals.get(end) : null;
        if (endVal != null && endVal > right) {
            intervals.put(right, endVal);
        }

        // Save the left interval if it overlaps with [left, right)
        Integer startVal = (start != null) ? intervals.get(start) : null;
        if (startVal != null && startVal > left) {
            intervals.put(start, left);
        }

        // Remove all intervals fully covered by [left, right)
        intervals.subMap(left, true, right, false).clear();
    }
}
