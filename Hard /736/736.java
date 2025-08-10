import java.util.*;

class Solution {
    public int evaluate(String expression) {
        List<String> tokens = tokenize(expression);
        return eval(tokens, new HashMap<>(), 0, tokens.size() - 1);
    }

    // Tokenizes the input string into a list of tokens
    private List<String> tokenize(String s) {
        List<String> tokens = new ArrayList<>();
        int n = s.length(), i = 0;
        while (i < n) {
            char c = s.charAt(i);
            if (c == ' ') {
                i++;
            } else if (c == '(' || c == ')') {
                tokens.add(String.valueOf(c));
                i++;
            } else {
                int j = i;
                while (j < n && s.charAt(j) != ' ' && s.charAt(j) != '(' && s.charAt(j) != ')') j++;
                tokens.add(s.substring(i, j));
                i = j;
            }
        }
        return tokens;
    }

    // Evaluates tokens from l to r (inclusive)
    private int eval(List<String> tokens, Map<String, Deque<Integer>> scope, int l, int r) {
        if (tokens.get(l).equals("(")) {
            String op = tokens.get(l + 1);
            if (op.equals("let")) {
                // Copy scope for this block
                Map<String, Deque<Integer>> newScope = new HashMap<>();
                for (String key : scope.keySet())
                    newScope.put(key, new ArrayDeque<>(scope.get(key)));
                int i = l + 2;
                while (i < r) {
                    // If next is the last expression, evaluate and return
                    if (i + 1 >= r) return eval(tokens, newScope, i, r - 1);
                    String var = tokens.get(i);
                    // If next token is "(", parse as expression, not assignment
                    if (var.equals("(") || isNumber(var)) {
                        return eval(tokens, newScope, i, r - 1);
                    }
                    // Assignment: var = expr
                    int j = i + 1;
                    int val;
                    if (tokens.get(j).equals("(")) {
                        int close = findClosing(tokens, j, r - 1);
                        val = eval(tokens, newScope, j, close);
                        i = close + 1;
                    } else {
                        val = eval(tokens, newScope, j, j);
                        i = j + 1;
                    }
                    newScope.putIfAbsent(var, new ArrayDeque<>());
                    newScope.get(var).push(val);
                }
                // Should not reach here
                return 0;
            } else if (op.equals("add") || op.equals("mult")) {
                int i1 = l + 2, i2;
                int v1, v2;
                if (tokens.get(i1).equals("(")) {
                    int close = findClosing(tokens, i1, r - 1);
                    v1 = eval(tokens, scope, i1, close);
                    i2 = close + 1;
                } else {
                    v1 = eval(tokens, scope, i1, i1);
                    i2 = i1 + 1;
                }
                if (tokens.get(i2).equals("(")) {
                    int close = findClosing(tokens, i2, r - 1);
                    v2 = eval(tokens, scope, i2, close);
                } else {
                    v2 = eval(tokens, scope, i2, i2);
                }
                return op.equals("add") ? v1 + v2 : v1 * v2;
            }
        } else {
            String token = tokens.get(l);
            if (isNumber(token)) {
                return Integer.parseInt(token);
            } else {
                // variable lookup
                for (int i = l; i >= 0; --i) {
                    if (scope.containsKey(token) && !scope.get(token).isEmpty())
                        return scope.get(token).peek();
                }
                // Should not happen per problem statement
                return 0;
            }
        }
        // Should not reach here
        return 0;
    }

    // Finds the index of the closing parenthesis for the opening at pos
    private int findClosing(List<String> tokens, int pos, int r) {
        int count = 0;
        for (int i = pos; i <= r; ++i) {
            if (tokens.get(i).equals("(")) count++;
            if (tokens.get(i).equals(")")) count--;
            if (count == 0) return i;
        }
        return r;
    }

    private boolean isNumber(String s) {
        return s.length() > 0 && (Character.isDigit(s.charAt(0)) || s.charAt(0) == '-');
    }
}
