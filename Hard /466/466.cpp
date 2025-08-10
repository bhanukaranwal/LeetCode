#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        if (n1 == 0) return 0;
        int l1 = s1.size(), l2 = s2.size();
        // index2: current index in s2
        // count1: number of s1 blocks used
        // count2: number of s2 blocks matched
        int index2 = 0, count1 = 0, count2 = 0;
        // Map from index2 to {count1, count2}
        unordered_map<int, pair<int, int>> recall;

        while (count1 < n1) {
            for (int i = 0; i < l1; ++i) {
                if (s1[i] == s2[index2]) {
                    index2++;
                    if (index2 == l2) {
                        index2 = 0;
                        count2++;
                    }
                }
            }
            count1++;
            // If we have seen this index2 before, then a loop is detected
            if (recall.count(index2)) {
                auto [prev_count1, prev_count2] = recall[index2];
                // The loop length in s1 and s2
                int loop_s1 = count1 - prev_count1;
                int loop_s2 = count2 - prev_count2;
                int remain = n1 - count1;
                int times = remain / loop_s1;
                count1 += times * loop_s1;
                count2 += times * loop_s2;
            } else {
                recall[index2] = {count1, count2};
            }
        }
        return count2 / n2;
    }
};
