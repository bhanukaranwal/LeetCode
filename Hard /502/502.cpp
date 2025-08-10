class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        // Min-heap for capital, max-heap for profits
        vector<pair<int, int>> projects;
        for (int i = 0; i < n; ++i)
            projects.emplace_back(capital[i], profits[i]);
        sort(projects.begin(), projects.end());

        priority_queue<int> maxProfit;
        int i = 0;
        while (k--) {
            // Push all projects that can be afforded with current capital
            while (i < n && projects[i].first <= w)
                maxProfit.push(projects[i++].second);
            if (maxProfit.empty()) break;
            w += maxProfit.top();
            maxProfit.pop();
        }
        return w;
    }
};
