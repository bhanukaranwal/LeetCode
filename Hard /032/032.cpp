#include <string>
#include <algorithm> // For std::max

class Solution {
public:
    int longestValidParentheses(std::string s) {
        int max_len = 0;
        int open = 0;  // Count of opening parentheses
        int close = 0; // Count of closing parentheses

        // First pass: Left to Right
        // This pass handles cases where valid parentheses are balanced or
        // have an excess of closing parentheses (e.g., ")()()").
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                open++;
            } else { // s[i] == ')'
                close++;
            }

            if (open == close) {
                // If counts are equal, it's a valid balanced substring.
                max_len = std::max(max_len, 2 * open);
            } else if (close > open) {
                // If close count exceeds open count, the current sequence is invalid.
                // Reset counts to start looking for a new valid sequence.
                open = 0;
                close = 0;
            }
        }

        // Reset counts for the second pass
        open = 0;
        close = 0;

        // Second pass: Right to Left
        // This pass handles cases where valid parentheses might have an excess
        // of opening parentheses at the end (e.g., "(()(").
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] == '(') {
                open++;
            } else { // s[i] == ')'
                close++;
            }

            if (open == close) {
                // If counts are equal, it's a valid balanced substring.
                max_len = std::max(max_len, 2 * open);
            } else if (open > close) {
                // If open count exceeds close count, the current sequence is invalid.
                // Reset counts. (Important for cases like "(()")
                open = 0;
                close = 0;
            }
        }

        return max_len;
    }
};
