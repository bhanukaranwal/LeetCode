class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> res(n, -1.0);
        stack<int> st;
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty()) {
                int j = st.top();
                if (cars[i][1] <= cars[j][1]) st.pop();
                else {
                    double t = (double)(cars[j][0] - cars[i][0]) / (cars[i][1] - cars[j][1]);
                    if (res[j] < 0 || t <= res[j]) {
                        res[i] = t;
                        break;
                    } else st.pop();
                }
            }
            st.push(i);
        }
        return res;
    }
};
