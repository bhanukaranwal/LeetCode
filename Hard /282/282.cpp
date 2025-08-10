class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        backtrack(num, target, 0, 0, 0, "", result);
        return result;
    }
private:
    void backtrack(const string& num, int target, int pos, long curr, long prev, string expr, vector<string>& result) {
        if (pos == num.size()) {
            if (curr == target) result.push_back(expr);
            return;
        }
        for (int i = pos; i < num.size(); ++i) {
            // Avoid operands with leading zeros
            if (i != pos && num[pos] == '0') break;
            string part = num.substr(pos, i - pos + 1);
            long n = stol(part);
            if (pos == 0) {
                // First number, no operator
                backtrack(num, target, i + 1, n, n, part, result);
            } else {
                // Addition
                backtrack(num, target, i + 1, curr + n, n, expr + "+" + part, result);
                // Subtraction
                backtrack(num, target, i + 1, curr - n, -n, expr + "-" + part, result);
                // Multiplication: handle precedence
                backtrack(num, target, i + 1, curr - prev + prev * n, prev * n, expr + "*" + part, result);
            }
        }
    }
};
