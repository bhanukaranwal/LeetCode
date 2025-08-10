import java.util.*;

class WordFilter {
    private Map<String, Integer> map;

    public WordFilter(String[] words) {
        map = new HashMap<>();
        for (int index = 0; index < words.length; ++index) {
            String word = words[index];
            int n = word.length();
            // For all possible prefix and suffix combinations
            for (int i = 0; i <= n; ++i) { // prefix: 0 to n
                String pref = word.substring(0, i);
                for (int j = 0; j <= n; ++j) { // suffix: 0 to n
                    String suff = word.substring(n - j);
                    map.put(pref + "#" + suff, index);
                }
            }
        }
    }
    
    public int f(String pref, String suff) {
        return map.getOrDefault(pref + "#" + suff, -1);
    }
}
