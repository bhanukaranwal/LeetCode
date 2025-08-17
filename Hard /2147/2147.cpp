class Solution {
public:
    int numberOfWays(string corridor) {
        const int MOD = 1e9 + 7;
        vector<int> seats;
        for (int i = 0; i < corridor.size(); ++i)
            if (corridor[i] == 'S') seats.push_back(i);
        if (seats.size() == 0 || seats.size() % 2 != 0) return 0;
        if (seats.size() == 2) return 1;
        long long res = 1;
        for (int i = 2; i < seats.size(); i += 2)
            res = res * (seats[i] - seats[i-1]) % MOD;
        return res;
    }
};
