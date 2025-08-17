#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // Sort meetings by time
        sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        vector<bool> knows(n, false);
        knows[0] = true;
        knows[firstPerson] = true;
        
        int m = meetings.size();
        for (int i = 0; i < m; ) {
            int t = meetings[i][2];
            // Collect all people in this time group
            unordered_set<int> people;
            int j = i;
            while (j < m && meetings[j][2] == t) {
                people.insert(meetings[j][0]);
                people.insert(meetings[j][1]);
                ++j;
            }
            // Build DSU for this group
            unordered_map<int, int> parent;
            function<int(int)> find = [&](int x) {
                if (!parent.count(x)) parent[x] = x;
                if (parent[x] != x) parent[x] = find(parent[x]);
                return parent[x];
            };
            for (int k = i; k < j; ++k) {
                int u = meetings[k][0], v = meetings[k][1];
                parent[find(u)] = find(v);
            }
            // Find all groups with a secret knower
            unordered_map<int, bool> groupHasSecret;
            for (int p : people) {
                if (knows[p]) groupHasSecret[find(p)] = true;
            }
            // Update knowledge
            for (int p : people) {
                if (groupHasSecret[find(p)]) knows[p] = true;
            }
            i = j;
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) if (knows[i]) ans.push_back(i);
        return ans;
    }
};
