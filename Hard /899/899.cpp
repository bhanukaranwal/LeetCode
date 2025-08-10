class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k == 1) {
            string res = s;
            for (int i = 1; i < s.size(); ++i) {
                string t = s.substr(i) + s.substr(0, i);
                if (t < res) res = t;
            }
            return res;
        }
        sort(s.begin(), s.end());
        return s;
    }
};
