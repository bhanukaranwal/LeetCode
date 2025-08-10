class Solution {
public:
    // Calculate exact matches between two words
    int match(string& a, string& b) {
        int matches = 0;
        for (int i = 0; i < 6; i++) {
            if (a[i] == b[i]) matches++;
        }
        return matches;
    }
    
    void findSecretWord(vector<string>& words, Master& master) {
        vector<string> candidates = words; // Current list of candidate words
        for (int i = 0; i < 30 && !candidates.empty(); i++) {
            // Pick the word that minimizes the maximum group size
            int minMaxGroup = INT_MAX;
            string bestGuess = candidates[0]; // Default to first candidate
            for (string& guess : candidates) {
                // Count remaining candidates for each possible match count
                vector<int> groups(7, 0); // groups[i] = count of words with i matches
                for (string& word : candidates) {
                    int m = match(guess, word);
                    groups[m]++;
                }
                // Find the size of the largest group
                int maxGroup = *max_element(groups.begin(), groups.end());
                if (maxGroup < minMaxGroup) {
                    minMaxGroup = maxGroup;
                    bestGuess = guess;
                }
            }
            
            // Make the guess
            int matches = master.guess(bestGuess);
            if (matches == 6) return; // Found the secret word
            
            // Filter candidates based on the number of matches
            vector<string> newCandidates;
            for (string& word : candidates) {
                if (match(bestGuess, word) == matches) {
                    newCandidates.push_back(word);
                }
            }
            candidates = newCandidates;
        }
    }
};
