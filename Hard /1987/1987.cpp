#define ll long long
int mod = 1e9 + 7;

class Solution {
public:
    int numberOfUniqueGoodSubsequences(string s) {
        int n = s.length(), ans = 0, first = n, zero = 0;
        
        vector<vector<int>> dp(2,vector<int>(n+1, 0));    
        
        for(int i=n-1; i>=0; --i){
            if(s[i]=='0') {
                zero = 1;
                dp[0][i] = (1ll*dp[0][i+1] + 1ll + dp[1][i+1])%mod;
                dp[1][i] = dp[1][i+1];
            }
            else {
                dp[1][i] = (1ll*dp[0][i+1] + 1ll + dp[1][i+1])%mod;
                dp[0][i] = dp[0][i+1];
            }
        }
        
        return (dp[1][0] + zero)%mod;
                
    }
};
