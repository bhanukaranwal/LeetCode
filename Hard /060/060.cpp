#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <climits>
#include <stdexcept>
#include <numeric>

// The "struct ListNode" is already defined by the LeetCode environment.
// Do not define it again in your code.

class Solution {
private:
    // Helper function for problem 124: Binary Tree Maximum Path Sum
    int maxGain(TreeNode* node, int& max_sum) {
        if (!node) return 0;
        int left_gain = std::max(0, maxGain(node->left, max_sum));
        int right_gain = std::max(0, maxGain(node->right, max_sum));
        int current_path_sum = node->val + left_gain + right_gain;
        max_sum = std::max(max_sum, current_path_sum);
        return node->val + std::max(left_gain, right_gain);
    }
    
    // Helper function for problem 5: Longest Palindromic Substring
    int expandAroundCenter(const std::string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }

public:
    // 1. Two Sum
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::map<int, int> num_map;
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            if (num_map.count(complement)) {
                return {num_map[complement], i};
            }
            num_map[nums[i]] = i;
        }
        return {};
    }

    // 2. Add Two Numbers
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int val1 = (l1 != nullptr) ? l1->val : 0;
            int val2 = (l2 != nullptr) ? l2->val : 0;
            int sum = val1 + val2 + carry;
            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        ListNode* resultHead = dummyHead->next;
        delete dummyHead;
        return resultHead;
    }

    // 5. Longest Palindromic Substring
    std::string longestPalindrome(std::string s) {
        if (s.length() < 1) return "";
        int start = 0, max_len = 1;
        for (int i = 0; i < s.length(); ++i) {
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i + 1);
            int current_max_len = std::max(len1, len2);
            if (current_max_len > max_len) {
                max_len = current_max_len;
                start = i - (max_len - 1) / 2;
            }
        }
        return s.substr(start, max_len);
    }

    // 6. Zigzag Conversion
    std::string convert(std::string s, int numRows) {
        if (numRows == 1) return s;
        std::vector<std::string> rows(numRows);
        int current_row = 0;
        bool going_down = false;
        for (char c : s) {
            rows[current_row] += c;
            if (current_row == 0 || current_row == numRows - 1) {
                going_down = !going_down;
            }
            current_row += going_down ? 1 : -1;
        }
        std::string result = "";
        for (const std::string& row_str : rows) {
            result += row_str;
        }
        return result;
    }
    
    // 7. Reverse Integer
    int reverse(int x) {
        int reversed_num = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;
            if (reversed_num > INT_MAX / 10 || (reversed_num == INT_MAX / 10 && pop > 7)) return 0;
            if (reversed_num < INT_MIN / 10 || (reversed_num == INT_MIN / 10 && pop < -8)) return 0;
            reversed_num = reversed_num * 10 + pop;
        }
        return reversed_num;
    }

    // 8. String to Integer (atoi)
    int myAtoi(std::string s) {
        int i = 0, sign = 1;
        long long result = 0;
        while (i < s.length() && s[i] == ' ') i++;
        if (i < s.length() && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        while (i < s.length() && isdigit(s[i])) {
            result = result * 10 + (s[i] - '0');
            if (result * sign > INT_MAX) return INT_MAX;
            if (result * sign < INT_MIN) return INT_MIN;
            i++;
        }
        return (int)(result * sign);
    }
    
    // 9. Palindrome Number
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        int reverted_half = 0;
        while (x > reverted_half) {
            reverted_half = reverted_half * 10 + x % 10;
            x /= 10;
        }
        return x == reverted_half || x == reverted_half / 10;
    }
    
    // 10. Regular Expression Matching
    bool isMatch(std::string s, std::string p) {
        int m = s.length(), n = p.length();
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] != '*') {
                    if (dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
                        dp[i][j] = true;
                    }
                } else {
                    if (dp[i][j - 2] || (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'))) {
                        dp[i][j] = true;
                    }
                }
            }
        }
        return dp[m][n];
    }
    
    // 12. Integer to Roman
    std::string intToRoman(int num) {
        const std::vector<std::pair<int, std::string>> value_symbols = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, 
            {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
        };
        std::string result = "";
        for (const auto& pair : value_symbols) {
            while (num >= pair.first) {
                result += pair.second;
                num -= pair.first;
            }
        }
        return result;
    }

    // 25. Reverse Nodes in k-Group
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* cursor = head;
        for (int i = 0; i < k; ++i) {
            if (cursor == nullptr) return head;
            cursor = cursor->next;
        }
        ListNode* prev = nullptr;
        ListNode* current = head;
        for (int i = 0; i < k; ++i) {
            ListNode* next_node = current->next;
            current->next = prev;
            prev = current;
            current = next_node;
        }
        head->next = reverseKGroup(current, k);
        return prev;
    }
    
    // 60. Permutation Sequence
    std::string getPermutation(int n, int k) {
        std::vector<int> factorials(n + 1);
        factorials[0] = 1;
        for (int i = 1; i <= n; ++i) {
            factorials[i] = factorials[i - 1] * i;
        }
        std::vector<int> numbers(n);
        std::iota(numbers.begin(), numbers.end(), 1);
        std::string result = "";
        k--;
        for (int i = n; i >= 1; --i) {
            int block_size = factorials[i - 1];
            int index = k / block_size;
            result += std::to_string(numbers[index]);
            numbers.erase(numbers.begin() + index);
            k %= block_size;
        }
        return result;
    }

    // 121. Best Time to Buy and Sell Stock
    int maxProfit(std::vector<int>& prices) {
        int min_price = INT_MAX;
        int max_profit = 0;
        for (int price : prices) {
            if (price < min_price) {
                min_price = price;
            } else if (price - min_price > max_profit) {
                max_profit = price - min_price;
            }
        }
        return max_profit;
    }
    
    // 122. Best Time to Buy and Sell Stock II
    int maxProfitII(std::vector<int>& prices) {
        int total_profit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1]) {
                total_profit += prices[i] - prices[i - 1];
            }
        }
        return total_profit;
    }

    // 123. Best Time to Buy and Sell Stock III
    int maxProfitIII(std::vector<int>& prices) {
        int buy1 = INT_MIN, sell1 = 0;
        int buy2 = INT_MIN, sell2 = 0;
        for (int price : prices) {
            sell2 = std::max(sell2, buy2 + price);
            buy2 = std::max(buy2, sell1 - price);
            sell1 = std::max(sell1, buy1 + price);
            buy1 = std::max(buy1, -price);
        }
        return sell2;
    }
    
    // 124. Binary Tree Maximum Path Sum
    int maxPathSum(TreeNode* root) {
        int max_sum = INT_MIN;
        maxGain(root, max_sum);
        return max_sum;
    }

    // 125. Valid Palindrome
    bool isPalindrome(std::string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            while (left < right && !std::isalnum(s[left])) left++;
            while (left < right && !std::isalnum(s[right])) right--;
            if (std::tolower(s[left]) != std::tolower(s[right])) return false;
            left++;
            right--;
        }
        return true;
    }

    // 859. Buddy Strings
    bool buddyStrings(std::string s, std::string goal) {
        if (s.length() != goal.length()) return false;
        if (s == goal) {
            std::set<char> unique_chars(s.begin(), s.end());
            return unique_chars.size() < s.length();
        }
        std::vector<int> diff_indices;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] != goal[i]) {
                diff_indices.push_back(i);
            }
        }
        return (diff_indices.size() == 2 && s[diff_indices[0]] == goal[diff_indices[1]] && s[diff_indices[1]] == goal[diff_indices[0]]);
    }
    
    // 2531. Make Number of Distinct Characters Equal
    bool isItPossible(std::string word1, std::string word2) {
        std::vector<int> freq1(26, 0);
        for (char c : word1) freq1[c - 'a']++;
        std::vector<int> freq2(26, 0);
        for (char c : word2) freq2[c - 'a']++;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (freq1[i] > 0 && freq2[j] > 0) {
                    freq1[i]--; freq2[i]++;
                    freq2[j]--; freq1[j]++;
                    int d1 = 0, d2 = 0;
                    for (int k = 0; k < 26; ++k) {
                        if (freq1[k] > 0) d1++;
                        if (freq2[k] > 0) d2++;
                    }
                    if (d1 == d2) return true;
                    freq1[i]++; freq2[i]--;
                    freq2[j]++; freq1[j]--;
                }
            }
        }
        return false;
    }
    
    // NOTE: The code below is for problems solved previously but not requested in this last exchange.
    // They are included for completeness based on the conversation history.

    // 4. Median of Two Sorted Arrays
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        if (nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        int m = nums1.size(), n = nums2.size();
        int low = 0, high = m;
        while (low <= high) {
            int pX = (low + high) / 2;
            int pY = (m + n + 1) / 2 - pX;
            int maxLeftX = (pX == 0) ? INT_MIN : nums1[pX - 1];
            int minRightX = (pX == m) ? INT_MAX : nums1[pX];
            int maxLeftY = (pY == 0) ? INT_MIN : nums2[pY - 1];
            int minRightY = (pY == n) ? INT_MAX : nums2[pY];
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((m + n) % 2 == 0)
                    return (double)(std::max(maxLeftX, maxLeftY) + std::min(minRightX, minRightY)) / 2.0;
                else
                    return (double)std::max(maxLeftX, maxLeftY);
            } else if (maxLeftX > minRightY) high = pX - 1;
            else low = pX + 1;
        }
        throw std::invalid_argument("Input arrays are not sorted.");
    }
    
    // 3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(std::string s) {
        std::vector<int> charIndex(128, -1);
        int maxLength = 0, left = 0;
        for (int right = 0; right < s.length(); ++right) {
            char currentChar = s[right];
            if (charIndex[currentChar] >= left) {
                left = charIndex[currentChar] + 1;
            }
            charIndex[currentChar] = right;
            maxLength = std::max(maxLength, right - left + 1);
        }
        return maxLength;
    }

}; // <-- This closing brace and semicolon fix the error.
