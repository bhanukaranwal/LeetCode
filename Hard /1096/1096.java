import java.util.*;

class Solution {
    public List<String> braceExpansionII(String expression) {
        Set<String> result = dfs(expression, 0, expression.length() - 1);
        List<String> list = new ArrayList<>(result);
        Collections.sort(list);
        return list;
    }

    // Recursive DFS to parse and expand the expression from index l to r (inclusive)
    private Set<String> dfs(String expr, int l, int r) {
        List<Set<String>> parts = new ArrayList<>();
        int brace = 0, last = l;
        for (int i = l; i <= r; i++) {
            char c = expr.charAt(i);
            if (c == '{') brace++;
            if (c == '}') brace--;
            if ((c == ',' && brace == 0) || i == r) {
                parts.add(product(expr, last, i == r ? i : i - 1));
                last = i + 1;
            }
        }
        // Union all parts
        Set<String> res = new HashSet<>();
        for (Set<String> part : parts) res.addAll(part);
        return res;
    }

    // Handles concatenation (cartesian product) for a segment of the expression
    private Set<String> product(String expr, int l, int r) {
        List<Set<String>> blocks = new ArrayList<>();
        int i = l;
        while (i <= r) {
            if (expr.charAt(i) == '{') {
                int j = i, brace = 0;
                while (j <= r) {
                    if (expr.charAt(j) == '{') brace++;
                    if (expr.charAt(j) == '}') brace--;
                    if (brace == 0) break;
                    j++;
                }
                blocks.add(dfs(expr, i + 1, j - 1));
                i = j + 1;
            } else if (Character.isLetter(expr.charAt(i))) {
                blocks.add(new HashSet<>(Arrays.asList("" + expr.charAt(i))));
                i++;
            } else {
                i++; // skip commas
            }
        }
        Set<String> res = new HashSet<>();
        res.add("");
        for (Set<String> block : blocks) {
            Set<String> next = new HashSet<>();
            for (String a : res)
                for (String b : block)
                    next.add(a + b);
            res = next;
        }
        return res;
    }
}
