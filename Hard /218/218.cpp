#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int,int>> events;
        for(auto& b : buildings) {
            events.emplace_back(b[0], -b[2]);
            events.emplace_back(b[1], b[2]);
        }
        sort(events.begin(), events.end());
        multiset<int> heights = {0};
        int prev = 0;
        vector<vector<int>> result;
        for(auto& e : events) {
            if(e.second < 0) heights.insert(-e.second);
            else heights.erase(heights.find(e.second));
            int curr = *heights.rbegin();
            if(curr != prev) {
                result.push_back({e.first, curr});
                prev = curr;
            }
        }
        return result;
    }
};
