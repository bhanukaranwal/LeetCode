class StreamChecker {
    private static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        boolean isWord = false;
    }
    
    private final TrieNode root = new TrieNode();
    private final StringBuilder stream = new StringBuilder();
    private final int maxWordLen;

    public StreamChecker(String[] words) {
        int maxLen = 0;
        // Build a reversed Trie
        for (String word : words) {
            TrieNode node = root;
            maxLen = Math.max(maxLen, word.length());
            for (int i = word.length() - 1; i >= 0; i--) {
                int idx = word.charAt(i) - 'a';
                if (node.children[idx] == null) node.children[idx] = new TrieNode();
                node = node.children[idx];
            }
            node.isWord = true;
        }
        maxWordLen = maxLen;
    }
    
    public boolean query(char letter) {
        stream.append(letter);
        TrieNode node = root;
        // Only check up to the length of the longest word
        for (int i = stream.length() - 1, cnt = 0; i >= 0 && cnt < maxWordLen; i--, cnt++) {
            int idx = stream.charAt(i) - 'a';
            node = node.children[idx];
            if (node == null) return false;
            if (node.isWord) return true;
        }
        return false;
    }
}
