#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
using namespace std;

class Solution {
    int bound;
    unordered_map<int, int> mapping;
public:
    Solution(int n, vector<int>& blacklist) {
        int bsize = blacklist.size();
        bound = n - bsize;
        unordered_set<int> black;
        for (int b : blacklist) if (b >= bound) black.insert(b);
        int w = bound;
        for (int b : blacklist) {
            if (b < bound) {
                while (black.count(w)) ++w;
                mapping[b] = w++;
            }
        }
    }
    
    int pick() {
        int x = rand() % bound;
        if (mapping.count(x)) return mapping[x];
        return x;
    }
};
