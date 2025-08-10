#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
using namespace std;

class RandomizedCollection {
    vector<int> nums;
    unordered_map<int, unordered_set<int>> idxMap; // val -> set of indices in nums
public:
    RandomizedCollection() {}

    bool insert(int val) {
        bool notPresent = idxMap[val].empty();
        nums.push_back(val);
        idxMap[val].insert(nums.size() - 1);
        return notPresent;
    }

    bool remove(int val) {
        if (idxMap[val].empty()) return false;
        int idx = *idxMap[val].begin();
        idxMap[val].erase(idx);
        int lastVal = nums.back();
        nums[idx] = lastVal;
        if (idx != nums.size() - 1) {
            idxMap[lastVal].erase(nums.size() - 1);
            idxMap[lastVal].insert(idx);
        }
        nums.pop_back();
        return true;
    }

    int getRandom() {
        int i = rand() % nums.size();
        return nums[i];
    }
};
