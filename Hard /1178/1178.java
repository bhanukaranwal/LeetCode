import java.util.*;

class Solution {
    public List<Integer> findNumOfValidWords(String[] words, String[] puzzles) {
        Map<Integer, Integer> freq = new HashMap<>();
        // Precompute frequency of each word's bitmask
        for (String word : words) {
            int mask = 0;
            for (char c : word.toCharArray()) mask |= 1 << (c - 'a');
            // Only consider words with at most 7 unique letters (since puzzles have 7)
            if (Integer.bitCount(mask) <= 7)
                freq.put(mask, freq.getOrDefault(mask, 0) + 1);
        }

        List<Integer> res = new ArrayList<>();
        for (String puzzle : puzzles) {
            int total = 0;
            int mask = 0;
            for (char c : puzzle.toCharArray()) mask |= 1 << (c - 'a');
            int first = 1 << (puzzle.charAt(0) - 'a');
            // Enumerate all subsets of the puzzle (except 0)
            for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
                if ((sub & first) != 0) {
                    total += freq.getOrDefault(sub, 0);
                }
            }
            res.add(total);
        }
        return res;
    }
}
