import java.util.*;

class Solution {
    int i = 0, n;
    String formula;
    
    public String countOfAtoms(String formula) {
        this.formula = formula;
        this.n = formula.length();
        Map<String, Integer> count = parse();
        StringBuilder sb = new StringBuilder();
        List<String> atoms = new ArrayList<>(count.keySet());
        Collections.sort(atoms);
        for (String atom : atoms) {
            sb.append(atom);
            if (count.get(atom) > 1) sb.append(count.get(atom));
        }
        return sb.toString();
    }
    
    private Map<String, Integer> parse() {
        Map<String, Integer> map = new HashMap<>();
        while (i < n) {
            char c = formula.charAt(i);
            if (c == '(') {
                i++;
                Map<String, Integer> inner = parse();
                int count = getCount();
                for (String atom : inner.keySet()) {
                    map.put(atom, map.getOrDefault(atom, 0) + inner.get(atom) * count);
                }
            } else if (c == ')') {
                i++;
                return map;
            } else {
                String name = getName();
                int count = getCount();
                map.put(name, map.getOrDefault(name, 0) + count);
            }
        }
        return map;
    }
    
    private String getName() {
        StringBuilder sb = new StringBuilder();
        sb.append(formula.charAt(i++)); // Uppercase
        while (i < n && Character.isLowerCase(formula.charAt(i))) {
            sb.append(formula.charAt(i++));
        }
        return sb.toString();
    }
    
    private int getCount() {
        int cnt = 0;
        while (i < n && Character.isDigit(formula.charAt(i))) {
            cnt = cnt * 10 + (formula.charAt(i++) - '0');
        }
        return cnt == 0 ? 1 : cnt;
    }
}
