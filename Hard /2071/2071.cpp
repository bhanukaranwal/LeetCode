class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int left = 0, right = min((int)tasks.size(), (int)workers.size());

        auto canAssign = [&](int cnt) {
            multiset<int> ws(workers.end() - cnt, workers.end());
            int pillsLeft = pills;
            for (int i = cnt - 1; i >= 0; --i) {
                // Try to assign the hardest task[i]
                auto it = ws.lower_bound(tasks[i]);
                if (it != ws.end()) {
                    ws.erase(it);
                } else {
                    if (pillsLeft == 0) return false;
                    it = ws.lower_bound(tasks[i] - strength);
                    if (it == ws.end()) return false;
                    ws.erase(it);
                    --pillsLeft;
                }
            }
            return true;
        };

        int ans = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAssign(mid)) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    }
};
