class Solution {
    public boolean parseBoolExpr(String expression) {
        return eval(expression, 0, expression.length() - 1);
    }

    // Helper to evaluate expression from index l to r (inclusive)
    private boolean eval(String expr, int l, int r) {
        char first = expr.charAt(l);
        if (first == 't') return true;
        if (first == 'f') return false;
        if (first == '!') {
            // !(subExpr)
            return !eval(expr, l + 2, r - 1);
        }
        // &(...) or |(...)
        boolean isAnd = first == '&';
        int i = l + 2, start = l + 2, level = 0;
        boolean res = isAnd;
        while (i < r) {
            if (expr.charAt(i) == '(') level++;
            if (expr.charAt(i) == ')') level--;
            // Split at commas not in nested parentheses
            if ((expr.charAt(i) == ',' && level == 0) || i == r - 1) {
                boolean sub = eval(expr, start, i == r - 1 ? i : i - 1);
                if (isAnd) res &= sub;
                else res |= sub;
                start = i + 1;
            }
            i++;
        }
        return res;
    }
}
