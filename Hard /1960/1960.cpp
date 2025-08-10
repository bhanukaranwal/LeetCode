class Solution {
public:
    
    vector<int> helper(string str){
        string tmp = "#";
        for(auto& ch : str){
            tmp += ch;
            tmp += "#";
        }
        int n = tmp.size();
        vector<int> vec(n, 0);
        int center = 0, maxRight = 0;
        for(int i = 0; i < n; i++){
            if(i < maxRight){
                int mirror = 2 * center - i;
                vec[i] = min(vec[mirror], maxRight - i);
            }
            int l = i - (1 + vec[i]);
            int r = i + (1 + vec[i]);
            while(l >= 0 && r < n && tmp[l] == tmp[r]){
                vec[i]++;
                l--;
                r++;
            }
            if(i + vec[i] > maxRight){
                maxRight = i + vec[i];
                center = i;
            }
        }
        vector<int> rvec;
        for(int i = 1; i < n; i += 2) rvec.push_back(vec[i]);
        n = rvec.size();
        vector<int> left(n, 0);
        for(int i = 0; i < n; i++){
            int b = i + rvec[i] / 2;
            left[b] = max(left[b], rvec[i]);
        }
        for(int i = n - 2; i >= 0; i--) left[i] = max(left[i], left[i + 1] - 2);
        for(int i = 1; i < n; i++) left[i] = max(left[i], left[i - 1]);
        return left;
    }

    long long maxProduct(string str) {
        vector<int> left = helper(str);
        reverse(begin(str), end(str));
        vector<int> right = helper(str);
        reverse(begin(right), end(right));
        int n = left.size();
        long long res = 0;
        for(int i = 0; i < n - 1; i++) res = max(res, 1ll * left[i] * right[i + 1]);
        return res;
    }
};
