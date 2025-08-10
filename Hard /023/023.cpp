#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <climits>
#include <stdexcept>

// The "struct ListNode" is already defined by LeetCode. Do not define it here.

class Solution {
private:
    // Helper for problem 5
    int expandAroundCenter(const std::string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }

public:
    // 23. Merge k Sorted Lists
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // Custom comparator for the priority queue, defined locally
        struct CompareNode {
            bool operator()(ListNode* a, ListNode* b) {
                return a->val > b->val;
            }
        };
        std::priority_queue<ListNode*, std::vector<ListNode*>, CompareNode> pq;

        for (ListNode* list : lists) {
            if (list) {
                pq.push(list);
            }
        }

        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;

        while (!pq.empty()) {
            ListNode* topNode = pq.top();
            pq.pop();
            
            current->next = topNode;
            current = current->next;

            if (topNode->next) {
                pq.push(topNode->next);
            }
        }
        
        ListNode* resultHead = dummyHead->next;
        delete dummyHead;
        return resultHead;
    }

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

    // 3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(std::string s) {
        std::vector<int> charIndex(128, -1);
        int maxLength = 0;
        int left = 0;
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

    // 4. Median of Two Sorted Arrays
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int m = nums1.size();
        int n = nums2.size();
        int low = 0, high = m;
        while (low <= high) {
            int partitionX = (low + high) / 2;
            int partitionY = (m + n + 1) / 2 - partitionX;
            int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
            int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((m + n) % 2 == 0) {
                    return (double)(std::max(maxLeftX, maxLeftY) + std::min(minRightX, minRightY)) / 2.0;
                } else {
                    return (double)std::max(maxLeftX, maxLeftY);
                }
            } else if (maxLeftX > minRightY) {
                high = partitionX - 1;
            } else {
                low = partitionX + 1;
            }
        }
        throw std::invalid_argument("Input arrays are not sorted.");
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
    
    // 1353. Maximum Number of Events That Can Be Attended
    int maxEvents(std::vector<std::vector<int>>& events) {
        std::sort(events.begin(), events.end());
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        int attended_count = 0, event_idx = 0, n = events.size();
        for (int d = 1; d <= 100000; ++d) {
            while (!pq.empty() && pq.top() < d) pq.pop();
            while (event_idx < n && events[event_idx][0] == d) {
                pq.push(events[event_idx][1]);
                event_idx++;
            }
            if (!pq.empty()) {
                pq.pop();
                attended_count++;
            }
        }
        return attended_count;
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
                    int distinct1 = 0, distinct2 = 0;
                    for (int k = 0; k < 26; ++k) {
                        if (freq1[k] > 0) distinct1++;
                        if (freq2[k] > 0) distinct2++;
                    }
                    if (distinct1 == distinct2) return true;
                    freq1[i]++; freq2[i]--;
                    freq2[j]++; freq1[j]--;
                }
            }
        }
        return false;
    }
    
    // 3445. Maximum Difference Between Even and Odd Frequency II
    int maxDifference(std::string s, int k) {
        int n = s.length();
        int max_diff = -1e9;
        for (char a_char = '0'; a_char <= '4'; ++a_char) {
            for (char b_char = '0'; b_char <= '4'; ++b_char) {
                if (a_char == b_char) continue;
                int a = a_char - '0', b = b_char - '0';
                std::vector<int> p_val(n + 1, 0), p_mask(n + 1, 0), p_b_count(n + 1, 0);
                for (int i = 0; i < n; ++i) {
                    int d = s[i] - '0';
                    p_val[i + 1] = p_val[i];
                    p_mask[i + 1] = p_mask[i] ^ (1 << d);
                    p_b_count[i + 1] = p_b_count[i];
                    if (d == a) p_val[i + 1]++;
                    if (d == b) {
                        p_val[i + 1]--;
                        p_b_count[i + 1]++;
                    }
                }
                std::map<int, std::vector<std::pair<int, int>>> min_vals;
                min_vals[0].push_back({0, 0});
                for (int j = k; j <= n; ++j) {
                    int p_idx = j - k;
                    int p_m = p_mask[p_idx], p_v = p_val[p_idx], p_bc = p_b_count[p_idx];
                    auto& list = min_vals[p_m];
                    if (list.size() < 2 || p_v < list.back().first) {
                        list.push_back({p_v, p_bc});
                        std::sort(list.begin(), list.end());
                        if (list.size() > 2) list.pop_back();
                    }
                    int c_m = p_mask[j], c_v = p_val[j], c_bc = p_b_count[j];
                    int bit_a = 1 << a, bit_b = 1 << b;
                    for (int diff_mask = 0; diff_mask < 32; ++diff_mask) {
                        if ((diff_mask & bit_a) && !(diff_mask & bit_b)) {
                            int start_mask = c_m ^ diff_mask;
                            if (min_vals.count(start_mask)) {
                                for (const auto& cand : min_vals[start_mask]) {
                                    if (cand.second != c_bc) {
                                        max_diff = std::max(max_diff, c_v - cand.first);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return max_diff;
    }
};
