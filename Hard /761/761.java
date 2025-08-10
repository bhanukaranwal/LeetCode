import java.util.*;

class Solution {
    public String makeLargestSpecial(String s) {
        List<String> subs = new ArrayList<>();
        int count = 0, start = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (s.charAt(i) == '1') count++;
            else count--;
            if (count == 0) {
                // s.substring(start, i+1) is a special substring
                // Recursively process the inner part
                String inner = s.substring(start + 1, i);
                subs.add("1" + makeLargestSpecial(inner) + "0");
                start = i + 1;
            }
        }
        // Sort in reverse lex order to get the largest result
        Collections.sort(subs, Collections.reverseOrder());
        StringBuilder sb = new StringBuilder();
        for (String sub : subs) sb.append(sub);
        return sb.toString();
    }
}
