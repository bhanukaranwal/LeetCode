#include <vector>
#include <map>
#include <algorithm> // For std::max

class Solution {
public:
    int maxEqualFreq(std::vector<int>& nums) {
        // val_counts: Stores the frequency of each number in the current prefix.
        // Example: if prefix is [2,2,1,1,5], val_counts will be {2:2, 1:2, 5:1}
        std::map<int, int> val_counts; 
        
        // freq_counts: Stores the count of numbers that have a particular frequency.
        // Example for [2,2,1,1,5]: freq_counts will be {1:1, 2:2}
        // (1 number has frequency 1 (which is 5), 2 numbers have frequency 2 (which are 1 and 2))
        std::map<int, int> freq_counts; 

        int max_len = 0;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            int num = nums[i];

            // 1. Update freq_counts for old frequency of 'num'
            if (val_counts.count(num)) { // If num was already in val_counts
                int old_freq = val_counts[num];
                freq_counts[old_freq]--;
                if (freq_counts[old_freq] == 0) {
                    freq_counts.erase(old_freq);
                }
            }

            // 2. Update val_counts for 'num'
            val_counts[num]++;
            int new_freq = val_counts[num];

            // 3. Update freq_counts for new frequency of 'num'
            freq_counts[new_freq]++;

            // 4. Check if the current prefix nums[0...i] (length i+1) is "good"

            bool current_prefix_is_good = false;

            // Scenario 1: All numbers in the prefix have frequency 1.
            // Example: [1,2,3]. val_counts: {1:1, 2:1, 3:1}. freq_counts: {1:3}.
            // Removing any element leaves all others with frequency 1.
            if (freq_counts.size() == 1 && freq_counts.begin()->first == 1) {
                current_prefix_is_good = true;
            }
            // Scenario 2: Only one distinct number in the prefix.
            // Example: [7,7,7]. val_counts: {7:3}. freq_counts: {3:1}.
            // Removing one 7 leaves [7,7], vacuously "all equal" (only one distinct number).
            else if (freq_counts.size() == 1 && freq_counts.begin()->second == 1) {
                current_prefix_is_good = true;
            }
            // Scenario 3: Exactly two distinct frequencies are present.
            // This covers two sub-cases:
            // a) One number has frequency 1, all others have frequency X.
            //    Example: [1,1,2,2,3]. val_counts: {1:2, 2:2, 3:1}. freq_counts: {1:1, 2:2}.
            //    Remove '3' (frequency 1), then all are frequency 2.
            // b) One number has frequency X+1, all others have frequency X.
            //    Example: [1,1,1,2,2]. val_counts: {1:3, 2:2}. freq_counts: {2:1, 3:1}.
            //    Remove one '1' (from frequency 3), then all are frequency 2.
            else if (freq_counts.size() == 2) {
                auto it1 = freq_counts.begin();
                auto it2 = std::next(it1); // Get the second element

                int freq1 = it1->first;  // Smaller frequency
                int count1 = it1->second; // Count of numbers with freq1

                int freq2 = it2->first;  // Larger frequency
                int count2 = it2->second; // Count of numbers with freq2

                // Sub-case 3a: Smaller frequency is 1, and only one number has it.
                // Other numbers have 'freq2'. Remove the one with freq1.
                if (freq1 == 1 && count1 == 1) {
                    current_prefix_is_good = true;
                }
                // Sub-case 3b: Larger frequency is (smaller frequency + 1), and only one number has it.
                // Other numbers have 'freq1'. Remove one from the number with freq2.
                else if (freq2 == freq1 + 1 && count2 == 1) {
                    current_prefix_is_good = true;
                }
            }

            if (current_prefix_is_good) {
                max_len = i + 1;
            }
        }

        return max_len;
    }
};
