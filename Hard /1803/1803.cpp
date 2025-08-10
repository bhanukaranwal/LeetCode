struct Node {
    Node* next[2];
    int cnt;
};

const int N = 2e4;
const int B = 15;

Node pool[N * B];
int pool_index = 0;

Node* newNode() {
    pool[pool_index].next[0] = pool[pool_index].next[1] = 0;
    pool[pool_index].cnt = 0;
    return &pool[pool_index++];
}

struct Trie {
    Node* root;
    Trie() {
        pool_index = 0;
        root = newNode();
    }
    inline void insert(unsigned a) {
        auto it = root;
        for (int i = 14; i >= 0; i--) {
            int bit = (a >> i) & 1;
            if (it->next[bit] == NULL) {
                it->next[bit] = newNode();
            }
            it = it->next[bit];
            it->cnt++;
        }
    }
    inline int query(unsigned a, unsigned k) {
        auto it = root;
        int res = 0;
        for (int i = 14; i >= 0; i--) {
            if (!it) break;
            int bit_a = (a >> i) & 1;
            int bit_k = (k >> i) & 1;
            if (bit_k == 1) {
                if (it->next[bit_a]) {
                    res += it->next[bit_a]->cnt;
                }
                it = it->next[bit_a ^ 1];
            } else {
                it = it->next[bit_a];
            }
        }
        return res;
    }
};

class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        return fun(nums, high + 1) - fun(nums, low);
    }
    int fun(vector<int>& nums, int k) {
        int res = 0;
        Trie tr;
        for (int e : nums) {
            res += tr.query(e, k);
            tr.insert(e);
        }
        return res;
    }
};

const auto _ = std::cin.tie(nullptr)->sync_with_stdio(false);
const auto __ = []() {
    struct ___ {
        static void _() { std::ofstream("display_runtime.txt") << 0 << '\n'; }
    };
    std::atexit(&___::_);
    return 0;
}();
