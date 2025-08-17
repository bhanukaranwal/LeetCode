class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> pos2(n);
        for (int i = 0; i < n; ++i) pos2[nums2[i]] = i;

        // Map nums1 to their positions in nums2
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = pos2[nums1[i]];

        // Count of elements less than arr[i] to the left
        vector<int> left(n, 0);
        FenwickTree bit(n);
        for (int i = 0; i < n; ++i) {
            left[i] = bit.query(arr[i]);
            bit.update(arr[i] + 1, 1);
        }

        // Count of elements greater than arr[i] to the right
        vector<int> right(n, 0);
        bit = FenwickTree(n); // Reset BIT
        for (int i = n - 1; i >= 0; --i) {
            right[i] = bit.query(n) - bit.query(arr[i] + 1);
            bit.update(arr[i] + 1, 1);
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i)
            ans += 1LL * left[i] * right[i];
        return ans;
    }

    // 1-based Fenwick Tree
    struct FenwickTree {
        vector<int> tree;
        int n;
        FenwickTree(int sz) : tree(sz + 2), n(sz + 2) {}
        void update(int i, int v) {
            while (i < n) {
                tree[i] += v;
                i += i & -i;
            }
        }
        int query(int i) {
            int res = 0;
            while (i > 0) {
                res += tree[i];
                i -= i & -i;
            }
            return res;
        }
    };
};
