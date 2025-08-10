import java.util.*;

class Solution {
    public int maxSatisfaction(int[] satisfaction) {
        Arrays.sort(satisfaction);
        int n = satisfaction.length, res = 0, suffix = 0;
        for (int i = n - 1; i >= 0; i--) {
            suffix += satisfaction[i];
            if (suffix > 0) res += suffix;
            else break;
        }
        return res;
    }
}
