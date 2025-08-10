class Solution {
    public int maxScoreWords(String[] words, char[] letters, int[] score) {
        int[] letterCount = new int[26];
        for (char c : letters) letterCount[c - 'a']++;
        return backtrack(words, letterCount, score, 0);
    }

    private int backtrack(String[] words, int[] letterCount, int[] score, int idx) {
        if (idx == words.length) return 0;
        // Option 1: skip this word
        int maxScore = backtrack(words, letterCount, score, idx + 1);

        // Option 2: use this word if possible
        String word = words[idx];
        int[] temp = letterCount.clone();
        int wordScore = 0;
        boolean canUse = true;
        for (char c : word.toCharArray()) {
            if (--temp[c - 'a'] < 0) {
                canUse = false;
                break;
            }
            wordScore += score[c - 'a'];
        }
        if (canUse) {
            maxScore = Math.max(maxScore, wordScore + backtrack(words, temp, score, idx + 1));
        }
        return maxScore;
    }
}
