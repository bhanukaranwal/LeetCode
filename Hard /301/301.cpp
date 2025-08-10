class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> res;
        queue<string> q;
        q.push(s);
        bool found = false;
        while (!q.empty()) {
            int n = q.size();
            unordered_set<string> visited;
            for (int i = 0; i < n; ++i) {
                string curr = q.front(); q.pop();
                if (isValid(curr)) {
                    res.insert(curr);
                    found = true;
                }
                if (found) continue;
                for (int j = 0; j < curr.size(); ++j) {
                    if (curr[j] != '(' && curr[j] != ')') continue;
                    string next = curr.substr(0, j) + curr.substr(j + 1);
                    if (!visited.count(next)) {
                        q.push(next);
                        visited.insert(next);
                    }
                }
            }
            if (found) break;
        }
        return vector<string>(res.begin(), res.end());
    }
    bool isValid(string s) {
        int cnt = 0;
        for (char c : s) {
            if (c == '(') ++cnt;
            if (c == ')') {
                --cnt;
                if (cnt < 0) return false;
            }
        }
        return cnt == 0;
    }
};

