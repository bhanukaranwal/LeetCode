class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> tCount;
        for (char c : t) tCount[c]++;
        
        int required = tCount.size(), formed = 0;
        unordered_map<char, int> window;
        int left = 0, right = 0, minLen = INT_MAX, minLeft = 0;
        
        while (right < s.length()) {
            window[s[right]]++;
            if (tCount.find(s[right]) != tCount.end() && window[s[right]] == tCount[s[right]]) {
                formed++;
            }
            
            while (left <= right && formed == required) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }
                window[s[left]]--;
                if (tCount.find(s[left]) != tCount.end() && window[s[left]] < tCount[s[left]]) {
                    formed--;
                }
                left++;
            }
            right++;
        }
        
        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};
