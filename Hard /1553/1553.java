import java.util.*;

class Solution {
    private Map<Integer, Integer> dp = new HashMap<>();
    public int minDays(int n) {
        if (n <= 1) return n;
        if (dp.containsKey(n)) return dp.get(n);
        // Option 1: Eat 1 orange, then solve for n-1
        // Option 2: Eat n/2 oranges (if possible), but may need to eat (n%2) oranges first to make n divisible by 2
        // Option 3: Eat 2*(n/3) oranges (if possible), but may need to eat (n%3) oranges first to make n divisible by 3
        int days = 1 + Math.min(
            minDays(n / 2) + n % 2,
            minDays(n / 3) + n % 3
        );
        dp.put(n, days);
        return days;
    }
}
