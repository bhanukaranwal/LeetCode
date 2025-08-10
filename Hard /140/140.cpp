#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Solution {
private:
    std::unordered_set<std::string> dict;
    std::unordered_map<int, std::vector<std::string>> memo;
    int N; 
    const std::string* S_ptr; 

public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict) {
        for (const std::string& word : wordDict) {
            dict.insert(word);
        }
        
        N = s.length();
        S_ptr = &s;

        std::vector<bool> dp_reachable(N + 1, false);
        dp_reachable[0] = true;
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp_reachable[j] && dict.count(S_ptr->substr(j, i - j))) {
                    dp_reachable[i] = true;
                    break;
                }
            }
        }
        if (!dp_reachable[N]) {
            return {}; 
        }

        return solve(0);
    }

private:
    std::vector<std::string> solve(int start_index) {
        if (start_index == N) {
            return {""};
        }

        if (memo.count(start_index)) {
            return memo[start_index];
        }

        std::vector<std::string> current_sentences;

        for (int i = start_index; i < N; ++i) {
            std::string word = S_ptr->substr(start_index, i - start_index + 1);
            if (dict.count(word)) {
                std::vector<std::string> next_sentences = solve(i + 1);
                for (const std::string& next_sentence : next_sentences) {
                    if (next_sentence.empty()) {
                        current_sentences.push_back(word);
                    } else {
                        current_sentences.push_back(word + " " + next_sentence);
                    }
                }
            }
        }

        memo[start_index] = current_sentences;
        return current_sentences;
    }
};
