class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> graph(n);
        // Build adjacency: graph[i] contains j if nums[i] + nums[j] is a perfect square
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && isSquare(nums[i] + nums[j]))
                    graph[i].push_back(j);
            }
        }
        vector<vector<int>> memo(n, vector<int>(1 << n, -1));
        int res = 0;
        // Try each index as the start
        for (int i = 0; i < n; ++i) {
            // Skip duplicates at the first position
            if (i > 0 && nums[i] == nums[i-1]) continue;
            res += dfs(i, 1 << i, nums, graph, memo);
        }
        return res;
    }

    int dfs(int idx, int mask, vector<int>& nums, vector<vector<int>>& graph, vector<vector<int>>& memo) {
        int n = nums.size();
        if (mask == (1 << n) - 1) return 1;
        if (memo[idx][mask] != -1) return memo[idx][mask];
        int ans = 0;
        for (int j : graph[idx]) {
            // Skip duplicates: only use the first unused duplicate in each position
            if ((mask & (1 << j)) == 0) {
                if (j > 0 && nums[j] == nums[j-1] && !(mask & (1 << (j-1)))) continue;
                ans += dfs(j, mask | (1 << j), nums, graph, memo);
            }
        }
        return memo[idx][mask] = ans;
    }

    bool isSquare(int x) {
        int r = sqrt(x);
        return r * r == x;
    }
};
