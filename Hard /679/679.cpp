class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums;
        for (int c : cards) nums.push_back(c);
        return solve(nums);
    }
    bool solve(vector<double>& nums) {
        if (nums.size() == 1) return abs(nums[0] - 24) < 1e-6;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) continue;
                vector<double> next;
                for (int k = 0; k < nums.size(); ++k)
                    if (k != i && k != j) next.push_back(nums[k]);
                for (int op = 0; op < 4; ++op) {
                    if (op < 2 && i > j) continue;
                    double res;
                    if (op == 0) res = nums[i] + nums[j];
                    if (op == 1) res = nums[i] * nums[j];
                    if (op == 2) res = nums[i] - nums[j];
                    if (op == 3) {
                        if (abs(nums[j]) < 1e-6) continue;
                        res = nums[i] / nums[j];
                    }
                    next.push_back(res);
                    if (solve(next)) return true;
                    next.pop_back();
                }
            }
        }
        return false;
    }
};
