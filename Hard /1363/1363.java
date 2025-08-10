import java.util.*;

class Solution {
    public String largestMultipleOfThree(int[] digits) {
        Arrays.sort(digits);
        List<Integer>[] mod = new List[3];
        for (int i = 0; i < 3; i++) mod[i] = new ArrayList<>();
        int sum = 0;
        for (int i = digits.length - 1; i >= 0; i--) {
            sum += digits[i];
            mod[digits[i] % 3].add(digits[i]);
        }
        int rem = sum % 3;
        if (rem != 0) {
            if (!mod[rem].isEmpty()) mod[rem].remove(mod[rem].size() - 1);
            else {
                int r = 3 - rem;
                if (mod[r].size() >= 2) {
                    mod[r].remove(mod[r].size() - 1);
                    mod[r].remove(mod[r].size() - 1);
                } else return "";
            }
        }
        List<Integer> res = new ArrayList<>();
        for (int i = 0; i < 3; i++) res.addAll(mod[i]);
        if (res.isEmpty()) return "";
        Collections.sort(res, Collections.reverseOrder());
        if (res.get(0) == 0) return "0";
        StringBuilder sb = new StringBuilder();
        for (int num : res) sb.append(num);
        return sb.toString();
    }
}
