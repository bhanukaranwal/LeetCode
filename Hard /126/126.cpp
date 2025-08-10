class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return {};
        
        vector<vector<string>> result;
        unordered_map<string, vector<string>> adj;
        unordered_map<string, int> level;
        queue<string> q;
        q.push(beginWord);
        level[beginWord] = 0;
        
        bool found = false;
        while (!q.empty() && !found) {
            int size = q.size();
            unordered_set<string> toRemove;
            for (int i = 0; i < size; i++) {
                string curr = q.front();
                q.pop();
                string temp = curr;
                for (int j = 0; j < curr.size(); j++) {
                    char original = curr[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                        curr[j] = c;
                        if (dict.count(curr)) {
                            if (!level.count(curr)) {
                                q.push(curr);
                                level[curr] = level[temp] + 1;
                                toRemove.insert(curr);
                            }
                            if (level[curr] == level[temp] + 1) {
                                adj[curr].push_back(temp);
                            }
                            if (curr == endWord) found = true;
                        }
                    }
                    curr[j] = original;
                }
            }
            for (string s : toRemove) dict.erase(s);
        }
        
        if (!found) return {};
        vector<string> path = {endWord};
        dfs(endWord, beginWord, adj, level, path, result);
        return result;
    }
    
private:
    void dfs(string curr, string beginWord, unordered_map<string, vector<string>>& adj, 
             unordered_map<string, int>& level, vector<string>& path, vector<vector<string>>& result) {
        if (curr == beginWord) {
            result.push_back(vector<string>(path.rbegin(), path.rend()));
            return;
        }
        
        for (string& prev : adj[curr]) {
            if (level[prev] + 1 == level[curr]) {
                path.push_back(prev);
                dfs(prev, beginWord, adj, level, path, result);
                path.pop_back();
            }
        }
    }
};
