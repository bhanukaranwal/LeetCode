class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int n = machines.size();
        int total = accumulate(machines.begin(), machines.end(), 0);
        if (total % n != 0) return -1; // Impossible to balance

        int avg = total / n;
        int res = 0, curr = 0;
        for (int i = 0; i < n; ++i) {
            // curr: net dresses to be sent from left to right up to machine i
            curr += machines[i] - avg;
            // The answer is the max of:
            // 1. abs(curr): total number of dresses to be sent through i
            // 2. machines[i] - avg: dresses to be sent from i itself
            res = max(res, max(abs(curr), machines[i] - avg));
        }
        return res;
    }
};
