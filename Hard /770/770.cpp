class Solution {
public:
    using Term = pair<int, vector<string>>;
    unordered_map<string, int> eval;
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        for (int i = 0; i < evalvars.size(); ++i) eval[evalvars[i]] = evalints[i];
        vector<Term> res = parse(expression);
        sort(res.begin(), res.end(), [](const Term& a, const Term& b) {
            if (a.second.size() != b.second.size()) return a.second.size() > b.second.size();
            return a.second < b.second;
        });
        vector<string> ans;
        for (auto& [coef, vars] : res) {
            if (coef == 0) continue;
            string s = to_string(coef);
            for (string& v : vars) s += "*" + v;
            ans.push_back(s);
        }
        return ans;
    }
    vector<Term> parse(string expr) {
        vector<string> tokens = tokenize(expr);
        int i = 0;
        return toTerms(parseExpr(tokens, i));
    }
    vector<string> tokenize(string& expr) {
        vector<string> tokens;
        int n = expr.size(), j = 0;
        while (j < n) {
            if (expr[j] == ' ') { ++j; continue; }
            if (isdigit(expr[j])) {
                int k = j;
                while (k < n && isdigit(expr[k])) ++k;
                tokens.push_back(expr.substr(j, k-j));
                j = k;
            } else if (isalpha(expr[j])) {
                int k = j;
                while (k < n && isalpha(expr[k])) ++k;
                tokens.push_back(expr.substr(j, k-j));
                j = k;
            } else {
                tokens.push_back(expr.substr(j, 1));
                ++j;
            }
        }
        return tokens;
    }
    vector<Term> toTerms(const map<vector<string>, int>& mp) {
        vector<Term> res;
        for (auto& [vars, coef] : mp) {
            if (coef) res.push_back({coef, vars});
        }
        return res;
    }
    map<vector<string>, int> parseExpr(vector<string>& tokens, int& i) {
        auto res = parseTerm(tokens, i);
        while (i < tokens.size() && (tokens[i] == "+" || tokens[i] == "-")) {
            string op = tokens[i++];
            auto t = parseTerm(tokens, i);
            if (op == "+") add(res, t, 1);
            else add(res, t, -1);
        }
        return res;
    }
    map<vector<string>, int> parseTerm(vector<string>& tokens, int& i) {
        auto res = parseFactor(tokens, i);
        while (i < tokens.size() && tokens[i] == "*") {
            ++i;
            auto t = parseFactor(tokens, i);
            res = multiply(res, t);
        }
        return res;
    }
    map<vector<string>, int> parseFactor(vector<string>& tokens, int& i) {
        if (tokens[i] == "(") {
            ++i;
            auto res = parseExpr(tokens, i);
            ++i;
            return res;
        }
        if (isalpha(tokens[i][0])) {
            if (eval.count(tokens[i])) {
                int v = eval[tokens[i++]];
                map<vector<string>, int> res;
                res[{}] = v;
                return res;
            } else {
                map<vector<string>, int> res;
                res[{tokens[i++]}] = 1;
                return res;
            }
        }
        int v = stoi(tokens[i++]);
        map<vector<string>, int> res;
        res[{}] = v;
        return res;
    }
    void add(map<vector<string>, int>& a, map<vector<string>, int>& b, int sign) {
        for (auto& [vars, coef] : b) a[vars] += sign * coef;
    }
    map<vector<string>, int> multiply(map<vector<string>, int>& a, map<vector<string>, int>& b) {
        map<vector<string>, int> res;
        for (auto& [va, ca] : a) {
            for (auto& [vb, cb] : b) {
                vector<string> merged = va;
                merged.insert(merged.end(), vb.begin(), vb.end());
                sort(merged.begin(), merged.end());
                res[merged] += ca * cb;
            }
        }
        return res;
    }
};
