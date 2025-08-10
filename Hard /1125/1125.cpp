class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        unordered_map<string, int> skill_index;
        for (int i = 0; i < n; ++i)
            skill_index[req_skills[i]] = i;

        int m = people.size();
        vector<int> person_skill(m, 0);
        for (int i = 0; i < m; ++i) {
            for (string& skill : people[i]) {
                if (skill_index.count(skill))
                    person_skill[i] |= (1 << skill_index[skill]);
            }
        }

        // dp[mask] = list of people indices covering mask
        unordered_map<int, vector<int>> dp;
        dp[0] = {};

        for (int i = 0; i < m; ++i) {
            auto curr_dp = dp; // snapshot to avoid concurrent modification
            for (auto& [mask, team] : curr_dp) {
                int new_mask = mask | person_skill[i];
                if (dp.find(new_mask) == dp.end() || dp[new_mask].size() > team.size() + 1) {
                    dp[new_mask] = team;
                    dp[new_mask].push_back(i);
                }
            }
        }
        return dp[(1 << n) - 1];
    }
};
