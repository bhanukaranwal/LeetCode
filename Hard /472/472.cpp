#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string> dict(words.begin(), words.end());
        vector<string> result;
        unordered_map<string, bool> memo;

        for (const string& word : words) {
            if (word.empty()) continue;
            dict.erase(word); // Avoid using the word itself
            if (canForm(word, dict, memo)) result.push_back(word);
            dict.insert(word);
        }
        return result;
    }

    bool canForm(const string& word, unordered_set<string>& dict, unordered_map<string, bool>& memo) {
        if (memo.count(word)) return memo[word];
        for (int i = 1; i < word.size(); ++i) {
            string left = word.substr(0, i);
            string right = word.substr(i);
            if (dict.count(left) && (dict.count(right) || canForm(right, dict, memo))) {
                return memo[word] = true;
            }
        }
        return memo[word] = false;
    }
};
