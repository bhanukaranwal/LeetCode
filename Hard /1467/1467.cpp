#include <vector>
using namespace std;

class Solution {
public:
    double getProbability(vector<int>& balls) {
        int k = balls.size();
        int total = 0;
        for (int b : balls) total += b;
        int n = total / 2;
        vector<double> fact(total + 1, 1.0);
        for (int i = 1; i <= total; ++i) fact[i] = fact[i - 1] * i;
        double valid = 0, all = 0;
        vector<int> chosen(k, 0);
        dfs(balls, chosen, 0, 0, 0, 0, 0, n, fact, valid, all);
        return valid / all;
    }

    void dfs(const vector<int>& balls, vector<int>& chosen, int idx,
             int cnt1, int cnt2, int color1, int color2, int n,
             const vector<double>& fact, double& valid, double& all) {
        if (idx == balls.size()) {
            if (cnt1 != n || cnt2 != n) return;
            double ways = 1.0;
            for (int i = 0; i < balls.size(); ++i)
                ways *= fact[balls[i]] / (fact[chosen[i]] * fact[balls[i] - chosen[i]]);
            all += ways;
            if (color1 == color2) valid += ways;
            return;
        }
        for (int i = 0; i <= balls[idx]; ++i) {
            chosen[idx] = i;
            int nc1 = color1 + (i > 0);
            int nc2 = color2 + (balls[idx] - i > 0);
            if (cnt1 + i <= n && cnt2 + balls[idx] - i <= n)
                dfs(balls, chosen, idx + 1, cnt1 + i, cnt2 + balls[idx] - i, nc1, nc2, n, fact, valid, all);
        }
    }
};
