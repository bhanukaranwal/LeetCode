#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
        std::vector<int> result_indices;

        if (s.empty() || words.empty() || words[0].empty()) {
            return result_indices;
        }

        int num_words = words.size();
        int word_len = words[0].length();
        int total_len = num_words * word_len; // Length of a concatenated substring

        // If the concatenated length is greater than the string s, no match possible
        if (total_len > s.length()) {
            return result_indices;
        }

        // 1. Store frequencies of all words in 'words' array
        std::unordered_map<std::string, int> word_counts;
        for (const std::string& word : words) {
            word_counts[word]++;
        }

        // Iterate through all possible starting offsets (0 to word_len - 1)
        // This ensures we cover all possible alignments of words in 's'.
        for (int start_offset = 0; start_offset < word_len; ++start_offset) {
            std::unordered_map<std::string, int> current_window_counts; // Frequencies in current window
            int words_found = 0; // Number of words matched in current window
            int left = start_offset; // Left boundary of the sliding window

            // The 'right' pointer iterates, marking the start of the next word to consider.
            // It advances by 'word_len' at each step.
            for (int right = start_offset; right <= (int)s.length() - word_len; right += word_len) {
                std::string current_word = s.substr(right, word_len);

                // If the current word is not one of the words we are looking for
                if (word_counts.find(current_word) == word_counts.end()) {
                    // Reset the window: clear counts, reset words_found, move left to after this word
                    current_window_counts.clear();
                    words_found = 0;
                    left = right + word_len;
                } else {
                    // The word is valid, add it to current window counts
                    current_window_counts[current_word]++;
                    words_found++;

                    // If the count of 'current_word' in the window exceeds its required count,
                    // shrink the window from the left until the count is valid.
                    while (current_window_counts[current_word] > word_counts[current_word]) {
                        std::string left_word = s.substr(left, word_len);
                        current_window_counts[left_word]--;
                        words_found--;
                        left += word_len;
                    }

                    // If we have found all the required words in the current window
                    if (words_found == num_words) {
                        // This means we found a valid concatenated substring
                        result_indices.push_back(left);

                        // To slide the window forward for the next potential match,
                        // remove the leftmost word from consideration and advance 'left'.
                        std::string leftmost_word = s.substr(left, word_len);
                        current_window_counts[leftmost_word]--;
                        words_found--;
                        left += word_len;
                    }
                }
            }
        }

        return result_indices;
    }
};
