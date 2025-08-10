import java.util.*;

class MajorityChecker {
    private int[] arr;
    private Map<Integer, List<Integer>> idxMap;
    private Random rand;

    public MajorityChecker(int[] arr) {
        this.arr = arr;
        idxMap = new HashMap<>();
        for (int i = 0; i < arr.length; i++) {
            idxMap.computeIfAbsent(arr[i], k -> new ArrayList<>()).add(i);
        }
        rand = new Random();
    }

    public int query(int left, int right, int threshold) {
        int len = right - left + 1;
        // Try up to 20 random samples (probability of missing a true majority is extremely low)
        for (int t = 0; t < 20; t++) {
            int idx = left + rand.nextInt(len);
            int val = arr[idx];
            List<Integer> posList = idxMap.get(val);
            // Binary search for occurrences in [left, right]
            int l = lowerBound(posList, left);
            int r = upperBound(posList, right);
            int count = r - l;
            if (count >= threshold) return val;
        }
        return -1;
    }

    // First index >= target
    private int lowerBound(List<Integer> list, int target) {
        int l = 0, r = list.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (list.get(m) < target) l = m + 1;
            else r = m;
        }
        return l;
    }

    // First index > target
    private int upperBound(List<Integer> list, int target) {
        int l = 0, r = list.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (list.get(m) <= target) l = m + 1;
            else r = m;
        }
        return l;
    }
}
