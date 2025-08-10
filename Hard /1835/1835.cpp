class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int x1 = 0, x2 = 0;
        for (int a : arr1) x1 ^= a;
        for (int b : arr2) x2 ^= b;
        return x1 & x2;
    }
};
